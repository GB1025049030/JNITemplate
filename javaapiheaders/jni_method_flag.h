#ifndef JNI_METHOD_FLAG_H
#define JNI_METHOD_FLAG_H

enum class MethodFlag {
    FLAG_JNI_METHOD_IS_STATIC = 1,
    FLAG_JNI_METHOD_IS_NONVIRTUAL = 2,
    FLAG_JNI_METHOD_RETURN_VOID = 4,
    FLAG_JNI_METHOD_RETURN_BYTE = 8,
    FLAG_JNI_METHOD_RETURN_CHAR = 16,
    FLAG_JNI_METHOD_RETURN_SHORT = 32,
    FLAG_JNI_METHOD_RETURN_INT = 64,
    FLAG_JNI_METHOD_RETURN_LONG = 128,
    FLAG_JNI_METHOD_RETURN_FLOAT = 256,
    FLAG_JNI_METHOD_RETURN_DOUBLE = 512,
    FLAG_JNI_METHOD_RETURN_BOOLEAN = 1024,
    FLAG_JNI_METHOD_RETURN_STRING = 2048,
    FLAG_JNI_METHOD_RETURN_OBJECT = 4096,
    FLAG_JNI_METHOD_RETURN_LIST = 8192,
    FLAG_JNI_METHOD_RETURN_MAP = 16384,
};

#endif //JNI_METHOD_FLAG_H
