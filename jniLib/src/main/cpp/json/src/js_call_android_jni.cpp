//
// Created by guobin on 2022/2/28.
//

#include "js_call_android_jni.h"

#include "jni_log.h"

namespace OHOS {
namespace TEMPLATE {

JSCallAndroidJni::JSCallAndroidJni() {
    JNI_LOGI("instance is created");
    jniUtils = DelayedSingleton<JNIUtils>::GetInstance();
}

JSCallAndroidJni::~JSCallAndroidJni() { JNI_LOGI("instance is destroyed"); }

void JSCallAndroidJni::InitJavaVm(JavaVM *vm) {
    JNI_LOGI("InitJavaVm: begin");
    OHOS::Jkit::nativeInit(vm);
    JNI_LOGI("InitJavaVm: end");
}

void JSCallAndroidJni::NativeInit(JNIEnv *env, const std::string &config) {
    JNI_LOGI("NativeInit: begin");
    if (jniUtils->InitUtilJavaClass(env) != JNI_OK ||
        jniUtils->InitModuleJavaClass(env, config) != JNI_OK) {
        JNI_LOGE("NativeInit: init class failed");
    }
    JNI_LOGI("NativeInit: end");
}

JNIEnv *JSCallAndroidJni::GetJNIEnv() {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetJNIEnv: env is null.");
        return nullptr;
    }
    return jkit.operator->();
}

int JSCallAndroidJni::GetJNIMethodInfo(int32_t methodID,
                                       JNIMethodInfo *methodInfo) {
    return jniUtils->GetJNIMethodInfo(methodID, methodInfo);
}

int JSCallAndroidJni::GetJNIFieldInfo(int32_t fieldID,
                                      JNIFieldInfo *fieldInfo) {
    return jniUtils->GetJNIFieldInfo(fieldID, fieldInfo);
}

jclass JSCallAndroidJni::GetModuleJClass(std::string name) {
    return jniUtils->GetModuleJClass(name);
}

jclass JSCallAndroidJni::GetUtilJClass(std::string name) {
    return jniUtils->GetUtilJClass(name);
}

jmethodID JSCallAndroidJni::GetUtilJMethodID(JavaUtilMethod id) {
    return jniUtils->GetUtilJMethodID(id);
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param) {
    JNI_LOGI("CallJavaMethod(Void): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    int32_t returnType;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_VOID,
                                 &returnType)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Void): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->CallJavaVoidMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Void): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, uint8_t *result) {
    JNI_LOGI("CallJavaMethod(Boolean): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(Boolean): param error.");
        return;
    }
    int32_t returnType;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN,
                                 &returnType)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Boolean): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            jniUtils->CallJavaBooleanMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Boolean): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, int8_t *result) {
    JNI_LOGI("CallJavaMethod(Byte): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(Byte): param error.");
        return;
    }
    int32_t returnType;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE,
                                 &returnType)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Byte): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            jniUtils->CallJavaByteMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Byte): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, uint16_t *result) {
    JNI_LOGI("CallJavaMethod(Char): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(Char): param error.");
        return;
    }
    int32_t returnType;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR,
                                 &returnType)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Char): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            jniUtils->CallJavaCharMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Char): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, int16_t *result) {
    JNI_LOGI("CallJavaMethod(Short): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(Short): param error.");
        return;
    }
    int32_t returnType;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT,
                                 &returnType)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Short): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            jniUtils->CallJavaShortMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Short): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, int32_t *result) {
    JNI_LOGI("CallJavaMethod(Int): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(Int): param error.");
        return;
    }
    int32_t returnType;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_INT,
                                 &returnType)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Int): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            jniUtils->CallJavaIntMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Int): Type Err, current(arrayDimension: %" LOG_LIMIT
            "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, int64_t *result) {
    JNI_LOGI("CallJavaMethod(Long): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(Long): param error.");
        return;
    }
    int32_t returnType;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_LONG,
                                 &returnType)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Long): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            jniUtils->CallJavaLongMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Long): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, float *result) {
    JNI_LOGI("CallJavaMethod(Float): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(Float): param error.");
        return;
    }
    int32_t returnType;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT,
                                 &returnType)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Float): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            jniUtils->CallJavaFloatMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Float): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, double *result) {
    JNI_LOGI("CallJavaMethod(Double): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(Double): param error.");
        return;
    }
    int32_t returnType;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE,
                                 &returnType)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Double): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            jniUtils->CallJavaDoubleMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Double): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, std::string *result) {
    JNI_LOGI("CallJavaMethod(String): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(String): param error.");
        return;
    }
    int32_t returnType;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_STRING,
                                 &returnType)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(String): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->CallJavaStringMethod(env, &methodInfo, object, param, result);
    } else {
        JNI_LOGE(
            "CallJavaMethod(String): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param,
                                      std::vector<uint8_t> *result) {
    JNI_LOGI("CallJavaMethod(BooleanArray): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(BooleanArray): param error.");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("CallJavaMethod(BooleanArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(methodInfo.returnObject.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN,
                                     &returnType)) {
        jniUtils->CallJavaBooleanArrayMethod(env, &methodInfo, object, param,
                                             result);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(methodInfo.returnObject.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN, &returnType)) {
        TransformBoolean transformBoolean(JAVA_LANG_BOOLEAN);
        jniUtils->CallJavaListMethod(env, &methodInfo, object, param, result,
                                     &transformBoolean);
    } else {
        JNI_LOGE(
            "CallJavaMethod(BooleanArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension,
            (int32_t)returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param,
                                      std::vector<int8_t> *result) {
    JNI_LOGI("CallJavaMethod(ByteArray): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(ByteArray): param error.");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("CallJavaMethod(ByteArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(methodInfo.returnObject.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE,
                                     &returnType)) {
        jniUtils->CallJavaByteArrayMethod(env, &methodInfo, object, param,
                                          result);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(methodInfo.returnObject.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE, &returnType)) {
        TransformByte transformByte(JAVA_LANG_BYTE);
        jniUtils->CallJavaListMethod(env, &methodInfo, object, param, result,
                                     &transformByte);
    } else {
        JNI_LOGE(
            "CallJavaMethod(ByteArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param,
                                      std::vector<uint16_t> *result) {
    JNI_LOGI("CallJavaMethod(CharArray): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(CharArray): param error.");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("CallJavaMethod(CharArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(methodInfo.returnObject.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR,
                                     &returnType)) {
        jniUtils->CallJavaCharArrayMethod(env, &methodInfo, object, param,
                                          result);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(methodInfo.returnObject.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR, &returnType)) {
        TransformChar transformChar(JAVA_LANG_CHARACTER);
        jniUtils->CallJavaListMethod(env, &methodInfo, object, param, result,
                                     &transformChar);
    } else {
        JNI_LOGE(
            "CallJavaMethod(CharArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param,
                                      std::vector<int16_t> *result) {
    JNI_LOGI("CallJavaMethod(ShortArray): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(ShortArray): param error.");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("CallJavaMethod(ShortArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(methodInfo.returnObject.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT,
                                     &returnType)) {
        jniUtils->CallJavaShortArrayMethod(env, &methodInfo, object, param,
                                           result);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(methodInfo.returnObject.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT, &returnType)) {
        TransformShort transformShort(JAVA_LANG_SHORT);
        jniUtils->CallJavaListMethod(env, &methodInfo, object, param, result,
                                     &transformShort);
    } else {
        JNI_LOGE(
            "CallJavaMethod(ShortArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param,
                                      std::vector<int32_t> *result) {
    JNI_LOGI("CallJavaMethod(IntArray): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(IntArray): param error.");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("CallJavaMethod(IntArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(methodInfo.returnObject.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_INT,
                                     &returnType)) {
        jniUtils->CallJavaIntArrayMethod(env, &methodInfo, object, param,
                                         result);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(methodInfo.returnObject.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_INT, &returnType)) {
        TransformInt transformInt(JAVA_LANG_INTEGER);
        jniUtils->CallJavaListMethod(env, &methodInfo, object, param, result,
                                     &transformInt);
    } else {
        JNI_LOGE(
            "CallJavaMethod(IntArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param,
                                      std::vector<int64_t> *result) {
    JNI_LOGI("CallJavaMethod(LongArray): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(LongArray): param error.");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("CallJavaMethod(LongArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(methodInfo.returnObject.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_LONG,
                                     &returnType)) {
        jniUtils->CallJavaLongArrayMethod(env, &methodInfo, object, param,
                                          result);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(methodInfo.returnObject.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_LONG, &returnType)) {
        TransformLong transformLong(JAVA_LANG_LONG);
        jniUtils->CallJavaListMethod(env, &methodInfo, object, param, result,
                                     &transformLong);
    } else {
        JNI_LOGE(
            "CallJavaMethod(LongArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param,
                                      std::vector<float> *result) {
    JNI_LOGI("CallJavaMethod(FloatArray): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(FloatArray): param error.");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("CallJavaMethod(FloatArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(methodInfo.returnObject.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT,
                                     &returnType)) {
        jniUtils->CallJavaFloatArrayMethod(env, &methodInfo, object, param,
                                           result);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(methodInfo.returnObject.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT, &returnType)) {
        TransformFloat transformFloat(JAVA_LANG_FLOAT);
        jniUtils->CallJavaListMethod(env, &methodInfo, object, param, result,
                                     &transformFloat);
    } else {
        JNI_LOGE(
            "CallJavaMethod(FloatArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param,
                                      std::vector<double> *result) {
    JNI_LOGI("CallJavaMethod(DoubleArray): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(DoubleArray): param error.");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("CallJavaMethod(DoubleArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(methodInfo.returnObject.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE,
                                     &returnType)) {
        jniUtils->CallJavaDoubleArrayMethod(env, &methodInfo, object, param,
                                            result);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(methodInfo.returnObject.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE, &returnType)) {
        TransformDouble transformDouble(JAVA_LANG_DOUBLE);
        jniUtils->CallJavaListMethod(env, &methodInfo, object, param, result,
                                     &transformDouble);
    } else {
        JNI_LOGE(
            "CallJavaMethod(DoubleArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param,
                                      std::vector<std::string> *result) {
    JNI_LOGI("CallJavaMethod(StringArray): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!result) {
        JNI_LOGE("CallJavaMethod(StringArray): param error.");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("CallJavaMethod(StringArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(methodInfo.returnObject.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_STRING,
                                     &returnType)) {
        jniUtils->CallJavaStringArrayMethod(env, &methodInfo, object, param,
                                            result);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(methodInfo.returnObject.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_STRING, &returnType)) {
        TransformString transformString(JAVA_LANG_STRING);
        jniUtils->CallJavaListMethod(env, &methodInfo, object, param, result,
                                     &transformString);
    } else {
        JNI_LOGE(
            "CallJavaMethod(StringArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, returnType);
    }
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     uint8_t *target) {
    JNI_LOGI("GetFieldValue(boolean): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(boolean) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(boolean): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = jniUtils->GetBooleanField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(boolean): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, type);
    }
    JNI_LOGI("GetFieldValue(boolean): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     int8_t *target) {
    JNI_LOGI("GetFieldValue(byte): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(byte) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(byte): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = jniUtils->GetByteField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(byte): Type Err, current(arrayDimension: %" LOG_LIMIT
            "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, type);
    }
    JNI_LOGI("GetFieldValue(byte): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     uint16_t *target) {
    JNI_LOGI("GetFieldValue(char): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(char) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(char): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = jniUtils->GetCharField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(char): Type Err, current(arrayDimension: %" LOG_LIMIT
            "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, type);
    }
    JNI_LOGI("GetFieldValue(char): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     int16_t *target) {
    JNI_LOGI("GetFieldValue(short): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(short) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(short): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = jniUtils->GetShortField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(short): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, type);
    }
    JNI_LOGI("GetFieldValue(short): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     int32_t *target) {
    JNI_LOGI("GetFieldValue(int): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(int) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_INT,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(int): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = jniUtils->GetIntField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(int): Type Err, current(arrayDimension: %" LOG_LIMIT
            "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, type);
    }
    JNI_LOGI("GetFieldValue(int): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     int64_t *target) {
    JNI_LOGI("GetFieldValue(long): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(long) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_LONG,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(long): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = jniUtils->GetLongField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(long): Type Err, current(arrayDimension: %" LOG_LIMIT
            "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, type);
    }
    JNI_LOGI("GetFieldValue(long): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     float *target) {
    JNI_LOGI("GetFieldValue(float): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(float) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(float): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = jniUtils->GetFloatField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(float): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, type);
    }
    JNI_LOGI("GetFieldValue(float): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     double *target) {
    JNI_LOGI("GetFieldValue(double): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(double) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(double): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = jniUtils->GetDoubleField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(double): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, type);
    }
    JNI_LOGI("GetFieldValue(double): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::string *target) {
    JNI_LOGI("GetFieldValue(String): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(String) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_STRING,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(String): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->GetStringField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(String): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, type);
    }
    JNI_LOGI("GetFieldValue(String): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<uint8_t> *target) {
    JNI_LOGI("GetFieldValue(BooleanArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(BooleanArray) : param error");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue(BooleanArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN,
                                     &returnType)) {
        TransformBoolean transformBoolean(JAVA_LANG_BOOLEAN);
        jniUtils->GetListField(env, object, &info, target, &transformBoolean);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN, &returnType)) {
        jniUtils->GetBooleanArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(BooleanArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, returnType);
    }
    JNI_LOGI("GetFieldValue(BooleanArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int8_t> *target) {
    JNI_LOGI("GetFieldValue(ByteArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(ByteArray) : param error");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue(ByteArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE,
                                     &returnType)) {
        TransformByte transformByte(JAVA_LANG_BYTE);
        jniUtils->GetListField(env, object, &info, target, &transformByte);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE, &returnType)) {
        jniUtils->GetByteArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(ByteArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, returnType);
    }
    JNI_LOGI("GetFieldValue(ByteArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<uint16_t> *target) {
    JNI_LOGI("GetFieldValue(CharArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(CharArray) : param error");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue(CharArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR,
                                     &returnType)) {
        TransformChar transformChar(JAVA_LANG_CHARACTER);
        jniUtils->GetListField(env, object, &info, target, &transformChar);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR, &returnType)) {
        jniUtils->GetCharArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(CharArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, returnType);
    }
    JNI_LOGI("GetFieldValue(CharArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int16_t> *target) {
    JNI_LOGI("GetFieldValue(ShortArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(ShortArray) : param error");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue(ShortArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT,
                                     &returnType)) {
        TransformShort transformShort(JAVA_LANG_SHORT);
        jniUtils->GetListField(env, object, &info, target, &transformShort);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT, &returnType)) {
        jniUtils->GetShortArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(ShortArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, returnType);
    }
    JNI_LOGI("GetFieldValue(ShortArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int32_t> *target) {
    JNI_LOGI("GetFieldValue(IntArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(IntArray) : param error");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue(IntArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_INT,
                                     &returnType)) {
        TransformInt transformInt(JAVA_LANG_INTEGER);
        jniUtils->GetListField(env, object, &info, target, &transformInt);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_INT, &returnType)) {
        jniUtils->GetIntArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(IntArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, returnType);
    }
    JNI_LOGI("GetFieldValue(IntArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int64_t> *target) {
    JNI_LOGI("GetFieldValue(LongArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(LongArray) : param error");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue(LongArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_LONG,
                                     &returnType)) {
        TransformLong transformLong(JAVA_LANG_LONG);
        jniUtils->GetListField(env, object, &info, target, &transformLong);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_LONG, &returnType)) {
        jniUtils->GetLongArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(LongArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, returnType);
    }
    JNI_LOGI("GetFieldValue(LongArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<float> *target) {
    JNI_LOGI("GetFieldValue(FloatArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(FloatArray) : param error");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue(FloatArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT,
                                     &returnType)) {
        TransformFloat transformFloat(JAVA_LANG_FLOAT);
        jniUtils->GetListField(env, object, &info, target, &transformFloat);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT, &returnType)) {
        jniUtils->GetFloatArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(FloatArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, returnType);
    }
    JNI_LOGI("GetFieldValue(FloatArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<double> *target) {
    JNI_LOGI("GetFieldValue(DoubleArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(DoubleArray) : param error");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue(DoubleArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE,
                                     &returnType)) {
        TransformDouble transformDouble(JAVA_LANG_DOUBLE);
        jniUtils->GetListField(env, object, &info, target, &transformDouble);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE, &returnType)) {
        jniUtils->GetDoubleArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(DoubleArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, returnType);
    }
    JNI_LOGI("GetFieldValue(DoubleArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<std::string> *target) {
    JNI_LOGI("GetFieldValue(StringArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(StringArray) : param error");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue(StringArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t returnType;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_STRING,
                                     &returnType)) {
        TransformString transformString(JAVA_LANG_STRING);
        jniUtils->GetListField(env, object, &info, target, &transformString);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_STRING, &returnType)) {
        jniUtils->GetStringArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(StringArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, returnType);
    }
    JNI_LOGI("GetFieldValue(StringArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     uint8_t *source) {
    JNI_LOGI("SetFieldValue(boolean): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(boolean) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(boolean): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->SetBooleanField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(boolean): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(boolean): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     int8_t *source) {
    JNI_LOGI("SetFieldValue(byte): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(byte) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(byte): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->SetByteField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(byte): Type Err, current(arrayDimension: %" LOG_LIMIT
            "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(byte): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     uint16_t *source) {
    JNI_LOGI("SetFieldValue(char): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(char) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(char): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->SetCharField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(char): Type Err, current(arrayDimension: %" LOG_LIMIT
            "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(char): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     int16_t *source) {
    JNI_LOGI("SetFieldValue(short): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(short) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(short): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->SetShortField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(short): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(short): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     int32_t *source) {
    JNI_LOGI("SetFieldValue(int): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(int) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_INT,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(int): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->SetIntField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(int): Type Err, current(arrayDimension: %" LOG_LIMIT
            "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(int): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     int64_t *source) {
    JNI_LOGI("SetFieldValue(long): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(long) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_LONG,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(long): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->SetLongField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(long): Type Err, current(arrayDimension: %" LOG_LIMIT
            "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(long): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     float *source) {
    JNI_LOGI("SetFieldValue(float): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(float) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(float): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->SetFloatField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(float): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(float): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     double *source) {
    JNI_LOGI("SetFieldValue(double): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(double) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(double): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->SetDoubleField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(double): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(double): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::string *source) {
    JNI_LOGI("SetFieldValue(String): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(String) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_STRING,
                                 &type)) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(String): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jniUtils->SetStringField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(String): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(String): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<uint8_t> *source) {
    JNI_LOGI("SetFieldValue(BooleanArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(BooleanArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(BooleanArray) : source is empty");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("SetFieldValue(BooleanArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t type;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN,
                                     &type)) {
        TransformBoolean transformBoolean(JAVA_LANG_BOOLEAN);
        jniUtils->SetListField(env, object, &info, source, &transformBoolean);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN, &type)) {
        jniUtils->SetBooleanArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(BooleanArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(BooleanArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int8_t> *source) {
    JNI_LOGI("SetFieldValue(ByteArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(ByteArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(ByteArray) : source is empty");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("SetFieldValue(ByteArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t type;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE,
                                     &type)) {
        TransformByte transformByte(JAVA_LANG_BYTE);
        jniUtils->SetListField(env, object, &info, source, &transformByte);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE, &type)) {
        jniUtils->SetByteArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(ByteArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(ByteArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<uint16_t> *source) {
    JNI_LOGI("SetFieldValue(CharArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(CharArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(CharArray) : source is empty");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("SetFieldValue(CharArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t type;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR,
                                     &type)) {
        TransformChar transformChar(JAVA_LANG_CHARACTER);
        jniUtils->SetListField(env, object, &info, source, &transformChar);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR, &type)) {
        jniUtils->SetCharArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(CharArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(CharArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int16_t> *source) {
    JNI_LOGI("SetFieldValue(ShortArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(ShortArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(ShortArray) : source is empty");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("SetFieldValue(ShortArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t type;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT,
                                     &type)) {
        TransformShort transformShort(JAVA_LANG_SHORT);
        jniUtils->SetListField(env, object, &info, source, &transformShort);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT, &type)) {
        jniUtils->SetShortArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(ShortArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(ShortArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int32_t> *source) {
    JNI_LOGI("SetFieldValue(IntArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(IntArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(IntArray) : source is empty");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("SetFieldValue(IntArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t type;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_INT,
                                     &type)) {
        TransformInt transformInt(JAVA_LANG_INTEGER);
        jniUtils->SetListField(env, object, &info, source, &transformInt);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_INT, &type)) {
        jniUtils->SetIntArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(IntArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(IntArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int64_t> *source) {
    JNI_LOGI("SetFieldValue(LongArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(LongArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(LongArray) : source is empty");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("SetFieldValue(LongArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t type;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_LONG,
                                     &type)) {
        TransformLong transformLong(JAVA_LANG_LONG);
        jniUtils->SetListField(env, object, &info, source, &transformLong);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_LONG, &type)) {
        jniUtils->SetLongArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(LongArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(LongArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<float> *source) {
    JNI_LOGI("SetFieldValue(FloatArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(FloatArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(FloatArray) : source is empty");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("SetFieldValue(FloatArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t type;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT,
                                     &type)) {
        TransformFloat transformFloat(JAVA_LANG_FLOAT);
        jniUtils->SetListField(env, object, &info, source, &transformFloat);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT, &type)) {
        jniUtils->SetFloatArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(FloatArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(FloatArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<double> *source) {
    JNI_LOGI("SetFieldValue(DoubleArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(DoubleArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(DoubleArray) : source is empty");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("SetFieldValue(DoubleArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t type;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE,
                                     &type)) {
        TransformDouble transformDouble(JAVA_LANG_DOUBLE);
        jniUtils->SetListField(env, object, &info, source, &transformDouble);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE, &type)) {
        jniUtils->SetDoubleArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(DoubleArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(DoubleArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<std::string> *source) {
    JNI_LOGI("SetFieldValue(StringArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(StringArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(StringArray) : source is empty");
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("SetFieldValue(StringArray): env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    int32_t type;
    if (JNIInfoUtil::CheckIsTypeList(&(info.fieldInfo.baseType),
                                     MethodFlag::FLAG_JNI_METHOD_RETURN_STRING,
                                     &type)) {
        TransformString transformString(JAVA_LANG_STRING);
        jniUtils->SetListField(env, object, &info, source, &transformString);
    } else if (JNIInfoUtil::CheckIsTypeArray(
                   &(info.fieldInfo.baseType),
                   MethodFlag::FLAG_JNI_METHOD_RETURN_STRING, &type)) {
        jniUtils->SetStringArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(StringArray): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(StringArray): end");
}

jstring JSCallAndroidJni::NewStringUTF(const char *string) {
    jstring result = nullptr;
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("NewStringUTF: env is null.");
        return result;
    }
    JNIEnv *env = jkit.operator->();
    if (env) {
        jstring ret = env->NewStringUTF(string);
        if (ret) {
            result = static_cast<jstring>(env->NewGlobalRef(ret));
        }
    }
    return result;
}

void JSCallAndroidJni::DeleteGlobalRef(jobject object) {
    if (!object) {
        return;
    }
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("DeleteGlobalRef: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    if (env) {
        env->DeleteGlobalRef(object);
    }
}

void JSCallAndroidJni::ExtractJavaBoolArray(jbooleanArray source,
                                            std::vector<uint8_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaBoolArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ExtractJavaBoolArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaByteArray(jbyteArray source,
                                            std::vector<int8_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaByteArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ExtractJavaByteArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaCharArray(jcharArray source,
                                            std::vector<uint16_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaCharArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ExtractJavaCharArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaShortArray(jshortArray source,
                                             std::vector<int16_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaShortArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ExtractJavaShortArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaIntArray(jintArray source,
                                           std::vector<int32_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaIntArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ExtractJavaIntArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaLongArray(jlongArray source,
                                            std::vector<int64_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaLongArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ExtractJavaLongArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaFloatArray(jfloatArray source,
                                             std::vector<float> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaFloatArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ExtractJavaFloatArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaDoubleArray(jdoubleArray source,
                                              std::vector<double> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaDoubleArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ExtractJavaDoubleArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaString(jstring source, std::string *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaString: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ExtractJavaString(env, source, result);
}

void JSCallAndroidJni::ExtractJavaString(jstring source, char **result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaString: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ExtractJavaString(env, source, result);
}

void JSCallAndroidJni::ExtractJavaStringArray(
    jobjectArray source, std::vector<std::string> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaStringArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ExtractJavaStringArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaBoolArray(std::vector<uint8_t> *source,
                                            jbooleanArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaBoolArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaBoolArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaByteArray(std::vector<int8_t> *source,
                                            jbyteArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaByteArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaByteArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaCharArray(std::vector<uint16_t> *source,
                                            jcharArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaCharArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaCharArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaShortArray(std::vector<int16_t> *source,
                                             jshortArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaShortArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaShortArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaIntArray(std::vector<int32_t> *source,
                                           jintArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaIntArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaIntArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaLongArray(std::vector<int64_t> *source,
                                            jlongArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaLongArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaLongArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaFloatArray(std::vector<float> *source,
                                             jfloatArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaFloatArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaFloatArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaDoubleArray(std::vector<double> *source,
                                              jdoubleArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaDoubleArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaDoubleArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaString(std::string *source, jstring *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaString: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaString(env, source, result);
}

void JSCallAndroidJni::ConvertJavaString(std::string const *source,
                                         jstring *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaString: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaString(env, source, result);
}

void JSCallAndroidJni::ConvertJavaString(const char *source, jstring *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaString: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaString(env, source, result);
}

void JSCallAndroidJni::ConvertJavaStringArray(std::vector<std::string> *source,
                                              jobjectArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaStringArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    jniUtils->ConvertJavaStringArray(env, source, result);
}

jobject JSCallAndroidJni::NewObject(std::string className) {
    jobject result = nullptr;
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("NewObject: env is null.");
        return result;
    }
    JNIEnv *env = jkit.operator->();
    if (env) {
        jobject ret = jniUtils->NewObject(env, &className);
        if (ret) {
            result = env->NewGlobalRef(ret);
        }
    }
    return result;
}

void TransformBoolean::Extract(jobject source, jboolean *target) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    (*target) = env->CallBooleanMethod(
        source,
        instance->GetUtilJMethodID(JavaUtilMethod::Boolean_booleanValue));
}

jobject TransformBoolean::CreateObject(jboolean *source) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return nullptr;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    jobject jBoolean =
        env->NewObject(instance->GetUtilJClass(GetClassName()),
                       instance->GetUtilJMethodID(JavaUtilMethod::BooleanInit));
    return jBoolean;
}

void TransformByte::Extract(jobject source, jbyte *target) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    (*target) = env->CallByteMethod(
        source, instance->GetUtilJMethodID(JavaUtilMethod::Byte_byteValue));
}

jobject TransformByte::CreateObject(jbyte *source) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return nullptr;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    jobject jByte = env->NewObject(
        instance->GetUtilJClass(GetClassName()),
        instance->GetUtilJMethodID(JavaUtilMethod::ByteInit), *source);
    return jByte;
}

void TransformChar::Extract(jobject source, jchar *target) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    (*target) = env->CallCharMethod(
        source,
        instance->GetUtilJMethodID(JavaUtilMethod::Character_charValue));
}

jobject TransformChar::CreateObject(jchar *source) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return nullptr;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    jobject jChar = env->NewObject(
        instance->GetUtilJClass(GetClassName()),
        instance->GetUtilJMethodID(JavaUtilMethod::CharacterInit), *source);
    return jChar;
}

void TransformShort::Extract(jobject source, jshort *target) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    (*target) = env->CallShortMethod(
        source, instance->GetUtilJMethodID(JavaUtilMethod::Short_shortValue));
}

jobject TransformShort::CreateObject(jshort *source) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return nullptr;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    jobject jShort = env->NewObject(
        instance->GetUtilJClass(GetClassName()),
        instance->GetUtilJMethodID(JavaUtilMethod::ShortInit), *source);
    return jShort;
}

void TransformInt::Extract(jobject source, jint *target) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    (*target) = env->CallIntMethod(
        source, instance->GetUtilJMethodID(JavaUtilMethod::Integer_intValue));
}

jobject TransformInt::CreateObject(jint *source) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return nullptr;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    jobject jInt = env->NewObject(
        instance->GetUtilJClass(GetClassName()),
        instance->GetUtilJMethodID(JavaUtilMethod::IntegerInit), *source);
    return jInt;
}

void TransformLong::Extract(jobject source, jlong *target) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    (*target) = env->CallLongMethod(
        source, instance->GetUtilJMethodID(JavaUtilMethod::Long_longValue));
}

jobject TransformLong::CreateObject(jlong *source) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return nullptr;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    jobject jLong = env->NewObject(
        instance->GetUtilJClass(GetClassName()),
        instance->GetUtilJMethodID(JavaUtilMethod::LongInit), *source);
    return jLong;
}

void TransformFloat::Extract(jobject source, jfloat *target) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    (*target) = env->CallFloatMethod(
        source, instance->GetUtilJMethodID(JavaUtilMethod::Float_floatValue));
}

jobject TransformFloat::CreateObject(jfloat *source) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return nullptr;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    jobject jFloat = env->NewObject(
        instance->GetUtilJClass(GetClassName()),
        instance->GetUtilJMethodID(JavaUtilMethod::FloatInit), *source);
    return jFloat;
}

void TransformDouble::Extract(jobject source, jdouble *target) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    (*target) = env->CallDoubleMethod(
        source, instance->GetUtilJMethodID(JavaUtilMethod::Double_doubleValue));
}

jobject TransformDouble::CreateObject(jdouble *source) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return nullptr;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    jobject jDouble = env->NewObject(
        instance->GetUtilJClass(GetClassName()),
        instance->GetUtilJMethodID(JavaUtilMethod::DoubleInit), *source);
    return jDouble;
}

void TransformString::Extract(jobject source, std::string *target) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        return;
    }
    JNIEnv *env = jkit.operator->();
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    instance->ExtractJavaString((jstring)source, target);
}

jobject TransformString::CreateObject(std::string *source) {
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    jstring result;
    instance->ConvertJavaString(source, &result);
    return result;
}
}  // namespace TEMPLATE
}  // namespace OHOS
