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
        final Set<String> preDefined = new HashSet<>();

        public void addClassInfo(ClassInfo info) {
            classes.add(info);
        }

        public void addInclude(String fileName) {
            includes.add(fileName);
        }

        public void addInclude(Set<String> list) {
            includes.addAll(list);
        }

        public void addPreDefined(String fileName) {
            preDefined.add(fileName);
        }

        public void addPreDefined(ArrayList<String> list) {
            preDefined.addAll(list);
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
            String clsName = pkgName + Constants.SYMBOL_COMMA + simpleName;

            this.pkgName = pkgName.replace(Constants.SYMBOL_COMMA, Constants.SYMBOL_SLASH);
            this.className = clsName.replace(Constants.SYMBOL_COMMA, Constants.SYMBOL_SLASH);
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

        boolean isStaticMethod;
        boolean isNonvirtualMethod;

        public MethodInfo(String name, String sign, int flag, int overloadSN, String methodType) {
            this.overloadSN = overloadSN;
            this.name = name;
            this.sign = sign;
            this.isStaticMethod = (flag & MethodFlag.FLAG_JNI_METHOD_IS_STATIC)
                    == MethodFlag.FLAG_JNI_METHOD_IS_STATIC;
            this.isNonvirtualMethod = (flag & MethodFlag.FLAG_JNI_METHOD_IS_NONVIRTUAL)
                    == MethodFlag.FLAG_JNI_METHOD_IS_NONVIRTUAL;

            int index = sign.lastIndexOf(Constants.SYMBOL_BRACKETS_RIGHT);
            int _index = methodType.lastIndexOf(Constants.SYMBOL_BRACKETS_RIGHT);
            if (index == -1 || _index == -1) {
                return;
            }

            parseReturnObject(flag, sign.substring(index + 1), methodType.substring(_index + 1));

            parseArgumentSign(sign.substring(1, index));
            parseArgumentType(methodType.substring(1, _index));
        }

        private void addArgument(Argument info) {
            args.add(info);
        }

        void setMethodId(int id) {
            this.id = id;
        }

        private void parseReturnObject(int baseFlag, String sign, String type) {
            System.out.println("parseReturnObject: baseFlag = " + baseFlag
                    + ", sign = " + sign + ", type = " + type);
            returnObject = new ReturnObject(sign, baseFlag);
            parseMethodType(returnObject.baseType, type);
        }

        private void parseArgumentSign(String sign) {
            int order = 0;
            for (int i = 0, len = sign.length(); i < len; i++) {
                char symbol = sign.charAt(i);
                if (!Constants.JNISymbol.JNI_SYMBOLS.contains(String.valueOf(symbol))) {
                    throw new IllegalArgumentException("The symbol(" + symbol + ") is illegal");
                }
                int _argFlag = 0;
                if (symbol == Constants.JNISymbol.JNI_SYMBOLS_ARR) {
                    int _arrayDimension = 1;
                    char _symbol_;
                    for (int j = i + 1; j < len; j++) {
                        _symbol_ = sign.charAt(i);
                        if (_symbol_ == Constants.JNISymbol.JNI_SYMBOLS_ARR) {
                            _arrayDimension++;
                            i = j + 1;
                        } else {
                            break;
                        }
                    }
                    symbol = sign.charAt(i);
                    if (symbol == Constants.JNISymbol.JNI_SYMBOLS_L) {
                        int _index2 = sign.indexOf(Constants.SYMBOL_END, i);
                        if (_index2 == -1) {
                            throw new IllegalArgumentException("The sign('" + this.sign + "') error");
                        }
                        String _argStr = sign.substring(i, _index2);
                        if (_argStr.contains(Constants.OBJECT_STRING2)) {
                            _argFlag |= MethodFlag.FLAG_JNI_METHOD_RETURN_STRING;
                        } else {
                            _argFlag |= MethodFlag.FLAG_JNI_METHOD_RETURN_OBJECT;
                        }
                        addArgument(new Argument(_argStr, sign.substring(i, _index2 + 1),
                                _argFlag, _arrayDimension, ++order));
                        i = _index2;
                    } else {
                        int _flag = parseBasicType(symbol);
                        if (_flag <= MethodFlag.FLAG_JNI_METHOD_RETURN_VOID) {
                            throw new IllegalArgumentException("The sign('" + this.sign + "') error");
                        }
                        _argFlag |= _flag;
                        String _clsName = String.valueOf(symbol);
                        addArgument(new Argument(_clsName, _clsName,
                                _argFlag, _arrayDimension, ++order));
                    }
                } else if (symbol == Constants.JNISymbol.JNI_SYMBOLS_L) {
                    int _index = sign.indexOf(Constants.SYMBOL_END, i);
                    if (_index != -1) {
                        String _argStr = sign.substring(i + 1, _index);
                        if (_argStr.contains(Constants.OBJECT_STRING2)) {
                            _argFlag |= MethodFlag.FLAG_JNI_METHOD_RETURN_STRING;
                        } else if (sign.contains(Constants.OBJECT_LIST2)) {
                            _argFlag |= MethodFlag.FLAG_JNI_METHOD_RETURN_LIST;
                        } else if (sign.contains(Constants.OBJECT_MAP2)) {
                            _argFlag |= MethodFlag.FLAG_JNI_METHOD_RETURN_MAP;
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

        private void parseArgumentType(String type) {
            int argsSize = args.size();
            System.out.println("parseArgumentType: type = " + type
                    + ", args.size = " + argsSize);
            if (argsSize < 1) {
                return;
            }
            if (argsSize == 1) {
                parseMethodType(args.get(0).baseType, type);
            } else {
                args.sort((a1, a2) -> {
                    if (a1 == null || a2 == null) {
                        return 1;
                    }
                    return a1.order - a2.order;
                });
                System.out.println("parseArgumentType: args = " + args);
                int argIndex = 0;
                String temp = type;
                boolean loop = true;
                do {
                    int index = getSplitIndex(temp);
                    System.out.println("parseArgumentType: index = " + index);
                    String _type;
                    if (index != -1) {
                        _type = temp.substring(0, index);
                        if (index + 1 < temp.length()) {
                            temp = temp.substring(index + 1);
                        } else {
                            temp = "";
                            loop = false;
                        }
                    } else {
                        loop = false;
                        _type = temp;
                    }
                    System.out.println("parseArgumentType: _type = " + _type);
                    System.out.println("parseArgumentType: temp = " + temp);
                    System.out.println("parseArgumentType: loop = " + loop);
                    if (_type.startsWith(Constants.OBJECT_LIST)
                            || _type.startsWith(Constants.OBJECT_MAP)) {
                        Argument argument = null;
                        if (argIndex >= 0 && argIndex < args.size()) {
                            argument = args.get(argIndex);
                        }
                        if (argument == null) {
                            break;
                        }
                        parseMethodType(argument.baseType, _type);
                    }
                    argIndex++;
                } while (loop);
            }
        }
    }

    private static String createObjectSign(String objStr) {
        return Constants.SYMBOL_L + objStr + Constants.SYMBOL_END;
    }

    private static int parseBasicType(char symbol) {
        int flag = 0;
        switch (symbol) {
            case Constants.JNISymbol.JNI_SYMBOLS_V:
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_VOID;
                break;
            case Constants.JNISymbol.JNI_SYMBOLS_B:
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_BYTE;
                break;
            case Constants.JNISymbol.JNI_SYMBOLS_C:
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_CHAR;
                break;
            case Constants.JNISymbol.JNI_SYMBOLS_S:
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_SHORT;
                break;
            case Constants.JNISymbol.JNI_SYMBOLS_I:
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_INT;
                break;
            case Constants.JNISymbol.JNI_SYMBOLS_J:
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_LONG;
                break;
            case Constants.JNISymbol.JNI_SYMBOLS_F:
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_FLOAT;
                break;
            case Constants.JNISymbol.JNI_SYMBOLS_D:
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_DOUBLE;
                break;
            case Constants.JNISymbol.JNI_SYMBOLS_Z:
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

    private static void parseMethodType(BaseType baseType, String type) {
        if (baseType == null || type == null || type.length() == 0) {
            return;
        }
        if (type.startsWith(Constants.OBJECT_LIST)) {
            String additional = getContentInAngleBrackets(type);
            baseType.additionalValue = parseMethodType(additional);
        } else if (type.startsWith(Constants.OBJECT_MAP)) {
            String additional = getContentInAngleBrackets(type);
            String[] kv = getKeyAndValue(additional);
            if (kv != null && kv.length == 2) {
                baseType.additionalKey = parseMethodType(kv[0]);
                baseType.additionalValue = parseMethodType(kv[1]);
            }
        }
    }

    private static BaseType parseMethodType(String additional) {
        if (additional == null) {
            return null;
        }
        if (additional.startsWith(Constants.OBJECT_LIST)) {
            String clsName = Constants.OBJECT_LIST.replace(Constants.SYMBOL_COMMA, Constants.SYMBOL_SLASH);
            String sign = createObjectSign(clsName);
            int flag = MethodFlag.FLAG_JNI_METHOD_RETURN_LIST;
            String _additional = getContentInAngleBrackets(additional);
            BaseType bt = new BaseType(clsName, sign, flag, 0);
            bt.additionalValue = parseMethodType(_additional);
            return bt;
        } else if (additional.startsWith(Constants.OBJECT_MAP)) {
            String clsName = Constants.OBJECT_LIST.replace(Constants.SYMBOL_COMMA, Constants.SYMBOL_SLASH);
            String sign = createObjectSign(clsName);
            int flag = MethodFlag.FLAG_JNI_METHOD_RETURN_MAP;
            String _additional = getContentInAngleBrackets(additional);
            BaseType bt = new BaseType(clsName, sign, flag, 0);
            String[] kv = getKeyAndValue(_additional);
            if (kv != null && kv.length == 2) {
                bt.additionalKey = parseMethodType(kv[0]);
                bt.additionalValue = parseMethodType(kv[1]);
            }
            return bt;
        } else if (additional.endsWith(Constants.SYMBOL_SQUARE_BRACKETS_BOTH)) {
            String _additional = additional;
            int arrayDimension = 0;
            do {
                arrayDimension++;
                _additional = _additional.substring(0, _additional.length() - 2);
            } while (_additional.endsWith(Constants.SYMBOL_SQUARE_BRACKETS_BOTH));
            String sign;
            int flag;
            if (Constants.JNISymbol.JNI_SYMBOLS_MAP.containsKey(additional)) {
                sign = Constants.JNISymbol.JNI_SYMBOLS_MAP.get(additional);
                flag = parseBasicType(sign.charAt(0));
            } else {
                sign = createObjectSign(_additional);
                if (_additional.equals(Constants.OBJECT_STRING2)) {
                    flag = MethodFlag.FLAG_JNI_METHOD_RETURN_STRING;
                } else {
                    flag = MethodFlag.FLAG_JNI_METHOD_RETURN_OBJECT;
                }
            }
            return new BaseType(_additional.replace(Constants.SYMBOL_COMMA, Constants.SYMBOL_SLASH),
                    sign, flag, arrayDimension);
        } else if (Constants.JNISymbol.JNI_SYMBOLS_MAP.containsKey(additional)) {
            String sign = Constants.JNISymbol.JNI_SYMBOLS_MAP.get(additional);
            return new BaseType(additional.replace(Constants.SYMBOL_COMMA, Constants.SYMBOL_SLASH),
                    sign, parseBasicType(sign.charAt(0)), 0);
        } else {
            String _additional = additional.replace(Constants.SYMBOL_COMMA, Constants.SYMBOL_SLASH);
            int flag = MethodFlag.FLAG_JNI_METHOD_RETURN_OBJECT;
            if (_additional.equals(Constants.OBJECT_STRING2)) {
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_STRING;
            }
            String sign = createObjectSign(_additional);
            return new BaseType(_additional, sign, flag, 0);
        }
    }

    private static String getContentInAngleBrackets(String text) {
        int start = text.indexOf(Constants.SYMBOL_ANGLE_BRACKETS_LEFT);
        int end = text.lastIndexOf(Constants.SYMBOL_ANGLE_BRACKETS_RIGHT);
        String _text = text;
        if (start != -1 && end != -1 && start < end) {
            _text = text.substring(start + 1, end);
        }
        return _text;
    }

    private static String[] getKeyAndValue(String text) {
        int index = getSplitIndex(text);
        if (index != -1) {
            String key = text.substring(0, index);
            String value = text.substring(index + 1);
            System.out.println("getKeyAndValue: key = " + key + ", value = " + value);
            return new String[]{key, value};
        }
        System.out.println("getKeyAndValue: return null");
        return null;
    }

    private static int getSplitIndex(String text) {
        System.out.println("getSplitIndex: text = " + text);
        if (!text.startsWith(Constants.OBJECT_LIST)
                && !text.startsWith(Constants.OBJECT_MAP)) {
            int index = text.indexOf(",");
            System.out.println("getSplitIndex: index = " + index);
            return index;
        }

        int leftCount = 0;
        int rightCount = 0;
        int start = 0;
        do {
            int leftIndex = text.indexOf(Constants.SYMBOL_ANGLE_BRACKETS_LEFT, start);
            if (leftIndex == -1 && leftCount == 0) {
                break;
            }
            int rightIndex = text.indexOf(Constants.SYMBOL_ANGLE_BRACKETS_RIGHT, start);
            if (leftIndex != -1) {
                if (leftIndex < rightIndex) {
                    start = leftIndex + 1;
                    leftCount++;
                } else {
                    start = rightIndex + 1;
                    rightCount++;
                }
            } else if (rightIndex != -1) {
                start = rightIndex + 1;
                rightCount++;
            }
        } while (leftCount != rightCount);

        System.out.println("getSplitIndex: index = " + start);
        return start;
    }

    public static class FieldInfo {
        public int id;
        public String name;
        public BaseType baseType;

        String pkgName;
        String type;
        Set<String> includes = new HashSet<>();
        ArrayList<String> preDefined = new ArrayList<>();

        public FieldInfo(String pkgName, String fieldName, String fieldSign, String type) {
            this.baseType = new BaseType(fieldSign);

            this.pkgName = pkgName;
            this.name = fieldName;
            this.type = createFieldType(createFieldHelperFromType(type));

            includes.add("#include <jni.h>\n");
            includes.add("#include \"jni_transform.h\"\n");

            baseType.parseFieldSign();
            parseMethodType(baseType, type);
        }

        void setFieldId(int id) {
            this.id = id;
        }

        private FieldHelper createFieldHelperFromType(String tempType) {
            FieldHelper helper = new FieldHelper();
            if (tempType.startsWith(Constants.OBJECT_LIST)) {
                includes.add("#include <vector>\n");
                tempType = getContentInAngleBrackets(tempType);
                helper.type = FieldHelper.TYPE_VECTOR;
                helper.value = createFieldHelperFromType(tempType);
            } else if (tempType.startsWith(Constants.OBJECT_MAP)) {
                includes.add("#include <map>\n");
                tempType = getContentInAngleBrackets(tempType);
                helper.type = FieldHelper.TYPE_MAP;
                String[] kv = getKeyAndValue(tempType);
                if (kv != null && kv.length == 2) {
                    helper.key = createFieldHelperFromType(kv[0]);
                    helper.value = createFieldHelperFromType(kv[1]);
                }
            } else if (tempType.endsWith(Constants.SYMBOL_SQUARE_BRACKETS_BOTH)) {
                includes.add("#include <vector>\n");
                tempType = tempType.substring(0, tempType.length() - 2);
                helper.type = FieldHelper.TYPE_VECTOR;
                helper.value = createFieldHelperFromType(tempType);
            } else if (Constants.JNIType.JNI_TYPES.containsKey(tempType)) {
                includes.add("#include <string>\n");
                helper.type = Constants.JNIType.JNI_TYPES.get(tempType);
            } else {
                int index = tempType.lastIndexOf(Constants.SYMBOL_COMMA);
                if (index != -1) {
                    String _pkgName = tempType.substring(0, index);
                    String _type = tempType.substring(index + 1);
                    helper.type = _type;
                    if (!pkgName.equals(_pkgName)) {
                        String _include = _pkgName.replace(Constants.SYMBOL_COMMA,
                                Constants.SYMBOL_UNDERSCORE) + ".h";
                        includes.add("#include \"" + _include + "\"\n");
                    } else {
                        preDefined.add("struct " + _type + ";\n");
                    }
                } else {
                    helper.type = tempType;
                }
            }
            return helper;
        }

        private String createFieldType(FieldHelper helper) {
            if (FieldHelper.TYPE_MAP.equals(helper.type)) {
                return String.format(Constants.Format.FIELD_MAP_FORMAT,
                        createFieldType(helper.key),
                        createFieldType(helper.value));
            } else if (FieldHelper.TYPE_VECTOR.equals(helper.type)) {
                return String.format(Constants.Format.FIELD_VECTOR_FORMAT,
                        createFieldType(helper.value));
            }
            return helper.type;
        }

        private static class FieldHelper {
            private static final String TYPE_VECTOR = "_VECTOR_";
            private static final String TYPE_MAP = "_MAP_";
            String type;
            FieldHelper key;
            FieldHelper value;
        }
    }

    public static class ReturnObject {
        public BaseType baseType;

        public ReturnObject(String sign, int flag) {
            this.baseType = new BaseType(sign);
            baseType.parseFieldSign(flag);
        }
    }

    public static class Argument {
        public int order;
        public BaseType baseType;

        public Argument(String clsName, String sign, int flag, int arrayDimension, int order) {
            this.order = order;
            this.baseType = new BaseType(clsName, sign, flag, arrayDimension);
        }

        @Override
        public String toString() {
            return "Argument{" +
                    "clsName='" + baseType.clsName + '\'' +
                    ", sign='" + baseType.sign + '\'' +
                    ", flag=" + baseType.flag +
                    ", arrayDimension=" + baseType.arrayDimension +
                    ", additionalKey=" + baseType.additionalKey +
                    ", additionalValue=" + baseType.additionalValue +
                    ", order=" + order +
                    '}';
        }
    }
}
