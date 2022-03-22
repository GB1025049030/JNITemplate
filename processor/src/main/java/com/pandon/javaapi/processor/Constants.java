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

        public static final String FIELD_ARRAY_FORMAT = "std::vector<%s>";

        public static final String TRANSFORM_CLASS_HEADER = "class Transform%s : public Transform<%s>";
        public static final String TRANSFORM_USING = "using Transform::Transform;\n";
        public static final String TRANSFORM_PUBLIC = "public:\n";
        public static final String TRANSFORM_METHOD_EXTRACT = "void Extract(jobject source, %s *target) override;\n";
        public static final String TRANSFORM_METHOD_CONVERT = "void Convert(jobject target, %s *source) override;\n";

        public static final String ENUM_CLASS_HEADER = "enum class %s_FIELD_CODE";

        public static final String METHOD_CODE_HEADER = "enum class MethodCode_%s {\n";
        public static final String METHOD_CODE_ANNOTATION = "// sign: %s\n";
        public static final String METHOD_CODE = "%s_%s_%d = %d,\n";
    }


    public static final String SYMBOL_END = ";";
    public static final String SYMBOL_L = "L";
    public static final String SYMBOL_SQUARE_BRACKETS_LEFT = "[";
    public static final String SYMBOL_SQUARE_BRACKETS_BOTH = "[]";
    public static final String SYMBOL_BRACKETS_RIGHT = ")";

    public static final String OBJECT_STRING = "java/lang/String";

    public static class JNIType {
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

        public static final Map<String, String> JNI_TYPES = new HashMap<>();

        static {
            JNI_TYPES.put(OBJECT_BOOLEAN, "uint8_t");
            JNI_TYPES.put(OBJECT_BOOLEAN2, "uint8_t");
            JNI_TYPES.put(OBJECT_BYTE, "int8_t");
            JNI_TYPES.put(OBJECT_BYTE2, "int8_t");
            JNI_TYPES.put(OBJECT_CHAR, "uint16_t");
            JNI_TYPES.put(OBJECT_CHAR2, "uint16_t");
            JNI_TYPES.put(OBJECT_SHORT, "int16_t");
            JNI_TYPES.put(OBJECT_SHORT2, "int16_t");
            JNI_TYPES.put(OBJECT_INTEGER, "int32_t");
            JNI_TYPES.put(OBJECT_INTEGER2, "int32_t");
            JNI_TYPES.put(OBJECT_LONG, "int64_t");
            JNI_TYPES.put(OBJECT_LONG2, "int64_t");
            JNI_TYPES.put(OBJECT_FLOAT, "float");
            JNI_TYPES.put(OBJECT_FLOAT2, "float");
            JNI_TYPES.put(OBJECT_DOUBLE, "double");
            JNI_TYPES.put(OBJECT_DOUBLE2, "double");
            JNI_TYPES.put(OBJECT_STRING, "std::string");
        }
    }

    public static class JNISymbol {
        public static final ArrayList<String> SYMBOLS = new ArrayList<>();

        static {
            SYMBOLS.add("Z"); // boolean
            SYMBOLS.add("B"); // Byte
            SYMBOLS.add("C"); // Char
            SYMBOLS.add("S"); // Short
            SYMBOLS.add("I"); // Integer
            SYMBOLS.add("J"); // Long
            SYMBOLS.add("F"); // Float
            SYMBOLS.add("D"); // Double
            SYMBOLS.add("V"); // Void
            SYMBOLS.add("L"); // Object
            SYMBOLS.add("["); // Array
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
    }
}
