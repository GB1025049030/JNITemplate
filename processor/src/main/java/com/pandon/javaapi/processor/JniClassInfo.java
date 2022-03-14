package com.pandon.javaapi.processor;

import com.pandon.javaapi.processor.Constants.MethodFlag;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class JniClassInfo {
    public final Map<String, PackInfo> mPkgInfos = new HashMap<>();

    public static class PackInfo {
        public final ArrayList<ClassInfo> classes = new ArrayList<>();
        final Set<String> includes = new HashSet<>();

        public void addClassInfo(ClassInfo info) {
            classes.add(info);
        }

        public void addInclude(String fileName) {
            includes.add(fileName);
        }

        public void addIncludes(ArrayList<String> list) {
            includes.addAll(list);
        }
    }

    public static class ClassInfo {
        final String simpleName;

        public final String pkgName;
        public String className;
        public ArrayList<MethodInfo> methods = new ArrayList<>();
        public ArrayList<FieldInfo> fields = new ArrayList<>();

        /**
         * Used to ensure that overloaded methods have unique serial numbers
         */
        private final Map<String, Integer> overloadMethodMap = new HashMap<>();

        public ClassInfo(String pkgName, String simpleName) {
            this.simpleName = simpleName;
            String clsName = pkgName + "." + simpleName;

            this.pkgName = pkgName.replace(".", "/");
            this.className = clsName.replace(".", "/");
        }

        boolean addMethodInfo(MethodInfo info) {
            Integer serialNumber = overloadMethodMap.get(info.name);
            if (serialNumber != null && serialNumber == info.overloadSN) {
                return false;
            }
            methods.add(info);
            overloadMethodMap.put(info.name, info.overloadSN);
            return true;
        }

        void addFieldInfo(FieldInfo info) {
            fields.add(info);
        }
    }

    public static class MethodInfo {
        public int id;
        public String name;
        public String sign;
        public ArrayList<Argument> args = new ArrayList<>();
        public ReturnObject returnObject;
        /**
         * Overloaded method internal serial number
         */
        public int overloadSN;

        public MethodInfo(String name, String sign, int flag, int overloadSN) {
            this.overloadSN = overloadSN;
            this.name = name;
            this.sign = sign;

            parseSign(flag);
        }

        private void addArgument(Argument info) {
            args.add(info);
        }

        void setMethodId(int id) {
            this.id = id;
        }

        private int parseBasicType(char symbol) {
            int flag = 0;
            switch (symbol) {
                case 'V':
                    flag = MethodFlag.FLAG_JNI_METHOD_RETURN_VOID;
                    break;
                case 'B':
                    flag = MethodFlag.FLAG_JNI_METHOD_RETURN_BYTE;
                    break;
                case 'C':
                    flag = MethodFlag.FLAG_JNI_METHOD_RETURN_CHAR;
                    break;
                case 'S':
                    flag = MethodFlag.FLAG_JNI_METHOD_RETURN_SHORT;
                    break;
                case 'I':
                    flag = MethodFlag.FLAG_JNI_METHOD_RETURN_INT;
                    break;
                case 'J':
                    flag = MethodFlag.FLAG_JNI_METHOD_RETURN_LONG;
                    break;
                case 'F':
                    flag = MethodFlag.FLAG_JNI_METHOD_RETURN_FLOAT;
                    break;
                case 'D':
                    flag = MethodFlag.FLAG_JNI_METHOD_RETURN_DOUBLE;
                    break;
                case 'Z':
                    flag = MethodFlag.FLAG_JNI_METHOD_RETURN_BOOLEAN;
                    break;
                case ';':
                    break;
                default:
                    flag = -1;
                    break;
            }
            return flag;
        }

        private void parseSign(int baseFlag) {
            int index = sign.lastIndexOf(Constants.SYMBOL_BRACKETS_RIGHT);
            if (index != -1) {
                // method return type
                String returnStr = sign.substring(index + 1);
                returnObject = new ReturnObject(returnStr, baseFlag);

                // method args
                String argStr = sign.substring(1, index);
                parseArgumentSign(argStr);
            }
        }

        private void parseArgumentSign(String sign) {
            int order = 0;
            for (int i = 0, len = sign.length(); i < len; i++) {
                char symbol = sign.charAt(i);
                if (!Constants.JNISymbol.SYMBOLS.contains(String.valueOf(symbol))) {
                    throw new IllegalArgumentException("The symbol(" + symbol + ") is illegal");
                }
                int _argFlag = 0;
                if (symbol == '[') {
                    int _arrayDimension = 0;
                    String descStr = Constants.SYMBOL_SQUARE_BRACKETS_LEFT + Constants.SYMBOL_L;
                    int _index = sign.indexOf(descStr, i);
                    if (_index != -1) {
                        int _index2 = sign.indexOf(Constants.SYMBOL_END, _index);
                        if (_index2 == -1) {
                            throw new IllegalArgumentException("The sign('" + this.sign + "') error");
                        }
                        _arrayDimension = _index - i + 1;
                        String _argStr = sign.substring(_index + 2, _index2);
                        if (_argStr.contains(Constants.OBJECT_STRING)) {
                            _argFlag |= MethodFlag.FLAG_JNI_METHOD_RETURN_STRING;
                        } else {
                            _argFlag |= MethodFlag.FLAG_JNI_METHOD_RETURN_OBJECT;
                        }
                        addArgument(new Argument(_argStr, sign.substring(i, _index2 + 1),
                                _argFlag, _arrayDimension, ++order));
                        i = _index2;
                    } else {
                        int _flag = -1;
                        char _symbol = '0';
                        for (int j = i + 1; j < len; j++) {
                            _symbol = sign.charAt(j);
                            _flag = parseBasicType(_symbol);
                            if (_flag > MethodFlag.FLAG_JNI_METHOD_RETURN_VOID) {
                                _arrayDimension = j - i + 1;
                                i = j;
                                break;
                            }
                            _flag = -1;
                        }
                        if (_flag != -1) {
                            _argFlag |= _flag;
                            String _clsName = String.valueOf(_symbol);
                            addArgument(new Argument(_clsName, _clsName,
                                    _argFlag, _arrayDimension, ++order));
                        } else {
                            throw new IllegalArgumentException("The sign('" + this.sign + "') error");
                        }
                    }
                } else if (symbol == 'L') {
                    int _index = sign.indexOf(Constants.SYMBOL_END, i);
                    if (_index != -1) {
                        String _argStr = sign.substring(i + 1, _index);
                        if (_argStr.contains(Constants.OBJECT_STRING)) {
                            _argFlag |= MethodFlag.FLAG_JNI_METHOD_RETURN_STRING;
                        } else {
                            _argFlag |= MethodFlag.FLAG_JNI_METHOD_RETURN_OBJECT;
                        }
                        addArgument(new Argument(_argStr, sign.substring(i, _index + 1),
                                _argFlag, 0, ++order));
                        i = _index;
                    } else {
                        throw new IllegalArgumentException("The sign('" + this.sign + "') error");
                    }
                } else {
                    int _flag = parseBasicType(symbol);
                    if (_flag > MethodFlag.FLAG_JNI_METHOD_RETURN_VOID) {
                        String _clsName = String.valueOf(symbol);
                        addArgument(new Argument(_clsName, _clsName,
                                _flag, 0, ++order));
                    } else {
                        throw new IllegalArgumentException("The sign('" + this.sign + "') error");
                    }
                }
            }
        }
    }

    public static class FieldInfo extends ArgumentBase {
        public int id;
        public String name;
        String type;
        ArrayList<String> includes = new ArrayList<>();

        public FieldInfo(String fieldName, String fieldSign, String type) {
            super(fieldSign);

            this.name = fieldName;

            parseFieldSign();
            parseType(type);
        }

        void setFieldId(int id) {
            this.id = id;
        }

        private void parseType(String type) {
            includes.add("#include <jni.h>");
            int arrayDimension = getArrayDimension(type, 0);
            if (arrayDimension > 0) {
                int len = arrayDimension * 2;
                type = type.substring(0, type.length() - len);
                includes.add("#include <vector>");
            }
            String _type;
            if (Constants.JNIType.JNI_TYPES.containsKey(type)) {
                _type = Constants.JNIType.JNI_TYPES.get(type);
                includes.add("#include <string>");
            } else {
                int index = type.lastIndexOf(".");
                if (index != -1) {
                    String _include = type.substring(0, index)
                            .replace(".", "_") + ".h";
                    includes.add("#include \"" + _include + "\"");
                    _type = type.substring(index + 1);
                } else {
                    _type = type;
                }
            }
            for (int i = 0; i < arrayDimension; i++) {
                _type = createArrayType(_type);
            }
            this.type = _type;
        }

        private int getArrayDimension(String type, int count) {
            if (type.endsWith(Constants.SYMBOL_SQUARE_BRACKETS_BOTH)) {
                count++;
                return getArrayDimension(type.substring(0, type.length() - 2), count);
            }
            return count;
        }

        private String createArrayType(String type) {
            return String.format(Constants.OBJECT_ARRAY_FORMAT, type);
        }
    }

    public static class ReturnObject extends ArgumentBase {
        public ReturnObject(String sign, int flag) {
            super(sign);
            parseFieldSign(flag);
        }
    }

    public static class Argument extends ArgumentBase {
        public int order;

        public Argument(String clsName, String sign, int flag, int arrayDimension, int order) {
            super(clsName, sign, flag, arrayDimension);
            this.order = order;
        }
    }
}
