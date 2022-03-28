package com.pandon.javaapi.processor;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Constants {
    public static class Format {
        public static final String NAME_SPACE = "namespace %s {\n";
        public static final String NAME_SPACE_TEMPLATE = "using namespace TEMPLATE;\n";

        public static final String MACRO_JSON_FILE = "#define JSON_FILE_%s \"%s.json\"\n";
        public static final String MACRO_JAVA_BEAN = "#define JAVA_BEAN_%s \"%s\"\n";

        public static final String FIELD_VECTOR_FORMAT = "std::vector<%s>";
        public static final String FIELD_MAP_FORMAT = "std::map<%s, %s>";

        public static final String TRANSFORM_CLASS_HEADER = "class Transform%s : public Transform<%s>";
        public static final String TRANSFORM_USING = "using Transform::Transform;\n";
        public static final String TRANSFORM_PUBLIC = "public:\n";
        public static final String TRANSFORM_METHOD_EXTRACT = "void Extract(jobject source, %s *target) override;\n";
        public static final String TRANSFORM_METHOD_CONVERT = "void Convert(jobject target, %s *source) override;\n";
        public static final String TRANSFORM_METHOD_CREATE_OBJECT = "jobject CreateObject(%s *source)\n";

        public static final String ENUM_CLASS_HEADER = "enum class %s_FIELD_CODE";

        public static final String METHOD_CODE_HEADER = "enum class MethodCode_%s {\n";
        public static final String METHOD_CODE_ANNOTATION = "" +
                "    /**\n" +
                "     * sign: %s\n" +
                "     * isStaticMethod: %b\n" +
                "     * isNonvirtualMethod: %b\n" +
                "     */\n";
        public static final String METHOD_CODE = "%s_%s_%d = %d,\n";
    }

    public static final String SYMBOL_END = ";";
    public static final String SYMBOL_L = "L";
    public static final String SYMBOL_COMMA = ".";
    public static final String SYMBOL_SLASH = "/";
    public static final String SYMBOL_UNDERSCORE = "_";
    public static final String SYMBOL_SQUARE_BRACKETS_LEFT = "[";
    public static final String SYMBOL_SQUARE_BRACKETS_BOTH = "[]";
    public static final String SYMBOL_BRACKETS_RIGHT = ")";
    public static final String SYMBOL_ANGLE_BRACKETS_LEFT = "<";
    public static final String SYMBOL_ANGLE_BRACKETS_RIGHT = ">";

    public static final String OBJECT_STRING = "java.lang.String";
    public static final String OBJECT_STRING2 = "java/lang/String";
    public static final String OBJECT_LIST = "java.util.List";
    public static final String OBJECT_LIST2 = "java/util/List";
    public static final String OBJECT_MAP = "java.util.Map";
    public static final String OBJECT_MAP2 = "java/util/Map";

    private static class JavaType {
        private static final String OBJECT_BOOLEAN = "java.lang.Boolean";
        private static final String OBJECT_BOOLEAN2 = "boolean";
        private static final String OBJECT_BYTE = "java.lang.Byte";
        private static final String OBJECT_BYTE2 = "byte";
        private static final String OBJECT_CHAR = "java.lang.Character";
        private static final String OBJECT_CHAR2 = "char";
        private static final String OBJECT_SHORT = "java.lang.Short";
        private static final String OBJECT_SHORT2 = "short";
        private static final String OBJECT_INTEGER = "java.lang.Integer";
        private static final String OBJECT_INTEGER2 = "int";
        private static final String OBJECT_LONG = "java.lang.Long";
        private static final String OBJECT_LONG2 = "long";
        private static final String OBJECT_FLOAT = "java.lang.Float";
        private static final String OBJECT_FLOAT2 = "float";
        private static final String OBJECT_DOUBLE = "java.lang.Double";
        private static final String OBJECT_DOUBLE2 = "double";
        private static final String OBJECT_STRING = "java.lang.String";
    }

    public static class JNIType {

        public static final Map<String, String> JNI_TYPES = new HashMap<>();

        static {
            JNI_TYPES.put(JavaType.OBJECT_BOOLEAN, "uint8_t");
            JNI_TYPES.put(JavaType.OBJECT_BOOLEAN2, "uint8_t");
            JNI_TYPES.put(JavaType.OBJECT_BYTE, "int8_t");
            JNI_TYPES.put(JavaType.OBJECT_BYTE2, "int8_t");
            JNI_TYPES.put(JavaType.OBJECT_CHAR, "uint16_t");
            JNI_TYPES.put(JavaType.OBJECT_CHAR2, "uint16_t");
            JNI_TYPES.put(JavaType.OBJECT_SHORT, "int16_t");
            JNI_TYPES.put(JavaType.OBJECT_SHORT2, "int16_t");
            JNI_TYPES.put(JavaType.OBJECT_INTEGER, "int32_t");
            JNI_TYPES.put(JavaType.OBJECT_INTEGER2, "int32_t");
            JNI_TYPES.put(JavaType.OBJECT_LONG, "int64_t");
            JNI_TYPES.put(JavaType.OBJECT_LONG2, "int64_t");
            JNI_TYPES.put(JavaType.OBJECT_FLOAT, "float");
            JNI_TYPES.put(JavaType.OBJECT_FLOAT2, "float");
            JNI_TYPES.put(JavaType.OBJECT_DOUBLE, "double");
            JNI_TYPES.put(JavaType.OBJECT_DOUBLE2, "double");
            JNI_TYPES.put(JavaType.OBJECT_STRING, "std::string");
        }
    }

    public static class JNISymbol {
        public static final ArrayList<String> JNI_SYMBOLS = new ArrayList<>();
        public static final Map<String, String> JNI_SYMBOLS_MAP = new HashMap<>();

        public static final char JNI_SYMBOLS_Z = 'Z'; // boolean
        public static final char JNI_SYMBOLS_B = 'B'; // Byte
        public static final char JNI_SYMBOLS_C = 'C'; // Char
        public static final char JNI_SYMBOLS_S = 'S'; // Short
        public static final char JNI_SYMBOLS_I = 'I'; // Integer
        public static final char JNI_SYMBOLS_J = 'J'; // Long
        public static final char JNI_SYMBOLS_F = 'F'; // Float
        public static final char JNI_SYMBOLS_D = 'D'; // Double
        public static final char JNI_SYMBOLS_V = 'V'; // Void
        public static final char JNI_SYMBOLS_L = 'L'; // Object
        public static final char JNI_SYMBOLS_ARR = '['; // Array

        static {
            JNI_SYMBOLS.add("Z"); // boolean
            JNI_SYMBOLS.add("B"); // Byte
            JNI_SYMBOLS.add("C"); // Char
            JNI_SYMBOLS.add("S"); // Short
            JNI_SYMBOLS.add("I"); // Integer
            JNI_SYMBOLS.add("J"); // Long
            JNI_SYMBOLS.add("F"); // Float
            JNI_SYMBOLS.add("D"); // Double
            JNI_SYMBOLS.add("V"); // Void
            JNI_SYMBOLS.add("L"); // Object
            JNI_SYMBOLS.add("["); // Array

            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_BOOLEAN, "Z");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_BOOLEAN2, "Z");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_BYTE, "B");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_BYTE2, "B");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_CHAR, "C");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_CHAR2, "C");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_SHORT, "S");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_SHORT2, "S");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_INTEGER, "I");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_INTEGER2, "I");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_LONG, "J");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_LONG2, "J");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_FLOAT, "F");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_FLOAT2, "F");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_DOUBLE, "D");
            JNI_SYMBOLS_MAP.put(JavaType.OBJECT_DOUBLE2, "D");
        }
    }

    public static class MethodFlag {
        public static final int FLAG_JNI_METHOD_IS_STATIC = 1;
        public static final int FLAG_JNI_METHOD_IS_NONVIRTUAL = 1 << 1;

        public static final int FLAG_JNI_METHOD_RETURN_VOID = 1 << 2;
        public static final int FLAG_JNI_METHOD_RETURN_BYTE = 1 << 3;
        public static final int FLAG_JNI_METHOD_RETURN_CHAR = 1 << 4;
        public static final int FLAG_JNI_METHOD_RETURN_SHORT = 1 << 5;
        public static final int FLAG_JNI_METHOD_RETURN_INT = 1 << 6;
        public static final int FLAG_JNI_METHOD_RETURN_LONG = 1 << 7;
        public static final int FLAG_JNI_METHOD_RETURN_FLOAT = 1 << 8;
        public static final int FLAG_JNI_METHOD_RETURN_DOUBLE = 1 << 9;
        public static final int FLAG_JNI_METHOD_RETURN_BOOLEAN = 1 << 10;
        public static final int FLAG_JNI_METHOD_RETURN_STRING = 1 << 11;
        public static final int FLAG_JNI_METHOD_RETURN_OBJECT = 1 << 12;
        public static final int FLAG_JNI_METHOD_RETURN_LIST = 1 << 13;
        public static final int FLAG_JNI_METHOD_RETURN_MAP = 1 << 14;
    }
}
