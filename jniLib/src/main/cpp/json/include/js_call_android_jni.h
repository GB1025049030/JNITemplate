//
// Created by guobin on 2022/2/28.
//

#ifndef ANNOTATIONJNI_JS_CALL_ANDROID_JNI_H
#define ANNOTATIONJNI_JS_CALL_ANDROID_JNI_H

#include <jni.h>

#include <map>
#include <nlohmann/json.hpp>
#include <set>

#include "javaapiheaders/jni_method_flag.h"
#include "jkit.h"
#include "jni_transform.h"
#include "jni_utils.h"
#include "json_util.h"
#include "singleton.h"

namespace OHOS {
namespace TEMPLATE {

class JSCallAndroidJni {
    JSCallAndroidJni();

    friend DelayedSingleton<JSCallAndroidJni>;

public:
    ~JSCallAndroidJni();

    void InitJavaVm(JavaVM *vm);

    void NativeInit(JNIEnv *env, const std::string &config);

    JNIEnv *GetJNIEnv();

    int GetJNIMethodInfo(int32_t methodID, JNIMethodInfo *methodInfo);

    int GetJNIFieldInfo(int32_t fieldID, JNIFieldInfo *fieldInfo);

    jclass GetModuleJClass(std::string name);

    jclass GetUtilJClass(std::string name);

    jmethodID GetUtilJMethodID(JavaUtilMethod id);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        uint8_t *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        int8_t *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        uint16_t *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        int16_t *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        int32_t *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        int64_t *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        float *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        double *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::vector<uint8_t> *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::vector<int8_t> *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::vector<uint16_t> *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::vector<int16_t> *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::vector<int32_t> *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::vector<int64_t> *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::vector<float> *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::vector<double> *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::string *result);

    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::vector<std::string> *result);

    template <typename T>
    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        T *result, Transform<T> *transform);

    template <typename T>
    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::vector<T> *result, Transform<T> *transform);

    template <typename K, typename V>
    void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                        std::map<K, V> *result, Transform<K> *keyTransform,
                        Transform<V> *valueTransform);

    void GetFieldValue(jobject object, int32_t fieldID, uint8_t *target);

    void GetFieldValue(jobject object, int32_t fieldID, int8_t *target);

    void GetFieldValue(jobject object, int32_t fieldID, uint16_t *target);

    void GetFieldValue(jobject object, int32_t fieldID, int16_t *target);

    void GetFieldValue(jobject object, int32_t fieldID, int32_t *target);

    void GetFieldValue(jobject object, int32_t fieldID, int64_t *target);

    void GetFieldValue(jobject object, int32_t fieldID, float *target);

    void GetFieldValue(jobject object, int32_t fieldID, double *target);

    void GetFieldValue(jobject object, int32_t fieldID, std::string *target);

    void GetFieldValue(jobject object, int32_t fieldID,
                       std::vector<uint8_t> *target);

    void GetFieldValue(jobject object, int32_t fieldID,
                       std::vector<int8_t> *target);

    void GetFieldValue(jobject object, int32_t fieldID,
                       std::vector<uint16_t> *target);

    void GetFieldValue(jobject object, int32_t fieldID,
                       std::vector<int16_t> *target);

    void GetFieldValue(jobject object, int32_t fieldID,
                       std::vector<int32_t> *target);

    void GetFieldValue(jobject object, int32_t fieldID,
                       std::vector<int64_t> *target);

    void GetFieldValue(jobject object, int32_t fieldID,
                       std::vector<float> *target);

    void GetFieldValue(jobject object, int32_t fieldID,
                       std::vector<double> *target);

    void GetFieldValue(jobject object, int32_t fieldID,
                       std::vector<std::string> *target);

    template <typename T>
    void GetFieldValue(jobject object, int32_t fieldID, T *result,
                       Transform<T> *transform);

    template <typename T>
    void GetFieldValue(jobject object, int32_t fieldID, std::vector<T> *result,
                       Transform<T> *transform);

    template <typename K, typename V>
    void GetFieldValue(jobject object, int32_t fieldID, std::map<K, V> *result,
                       Transform<K> *keyTransform,
                       Transform<V> *valueTransform);

    void SetFieldValue(jobject object, int32_t fieldID, uint8_t *source);

    void SetFieldValue(jobject object, int32_t fieldID, int8_t *source);

    void SetFieldValue(jobject object, int32_t fieldID, uint16_t *source);

    void SetFieldValue(jobject object, int32_t fieldID, int16_t *source);

    void SetFieldValue(jobject object, int32_t fieldID, int32_t *source);

    void SetFieldValue(jobject object, int32_t fieldID, int64_t *source);

    void SetFieldValue(jobject object, int32_t fieldID, float *source);

    void SetFieldValue(jobject object, int32_t fieldID, double *source);

    void SetFieldValue(jobject object, int32_t fieldID, std::string *source);

    void SetFieldValue(jobject object, int32_t fieldID,
                       std::vector<uint8_t> *source);

    void SetFieldValue(jobject object, int32_t fieldID,
                       std::vector<int8_t> *source);

    void SetFieldValue(jobject object, int32_t fieldID,
                       std::vector<uint16_t> *source);

    void SetFieldValue(jobject object, int32_t fieldID,
                       std::vector<int16_t> *source);

    void SetFieldValue(jobject object, int32_t fieldID,
                       std::vector<int32_t> *source);

    void SetFieldValue(jobject object, int32_t fieldID,
                       std::vector<int64_t> *source);

    void SetFieldValue(jobject object, int32_t fieldID,
                       std::vector<float> *source);

    void SetFieldValue(jobject object, int32_t fieldID,
                       std::vector<double> *source);

    void SetFieldValue(jobject object, int32_t fieldID,
                       std::vector<std::string> *source);

    template <typename T>
    void SetFieldValue(jobject object, int32_t fieldID, T *source,
                       Transform<T> *transform);

    template <typename T>
    void SetFieldValue(jobject object, int32_t fieldID, std::vector<T> *source,
                       Transform<T> *transform);

    template <typename K, typename V>
    void SetFieldValue(jobject object, int32_t fieldID, std::map<K, V> *source,
                       Transform<K> *keyTransform,
                       Transform<V> *valueTransform);

    jstring NewStringUTF(const char *string);

    void DeleteGlobalRef(jobject object);

    void ExtractJavaBoolArray(jbooleanArray source,
                              std::vector<uint8_t> *result);

    void ExtractJavaByteArray(jbyteArray source, std::vector<int8_t> *result);

    void ExtractJavaCharArray(jcharArray source, std::vector<uint16_t> *result);

    void ExtractJavaShortArray(jshortArray source,
                               std::vector<int16_t> *result);

    void ExtractJavaIntArray(jintArray source, std::vector<int32_t> *result);

    void ExtractJavaLongArray(jlongArray source, std::vector<int64_t> *result);

    void ExtractJavaFloatArray(jfloatArray source, std::vector<float> *result);

    void ExtractJavaDoubleArray(jdoubleArray source,
                                std::vector<double> *result);

    void ExtractJavaString(jstring source, std::string *result);

    void ExtractJavaString(jstring source, char **result);

    void ExtractJavaStringArray(jobjectArray source,
                                std::vector<std::string> *result);

    template <typename T>
    void ExtractJavaObject(jobject source, T *result, Transform<T> *transform);

    template <typename T>
    void ExtractJavaObjectArray(jobjectArray source, std::vector<T> *result,
                                Transform<T> *transform);

    template <typename K, typename V>
    void ExtractJavaMap(jobject source, std::map<K, V> *result,
                        Transform<K> *keyTransform,
                        Transform<V> *valueTransform);

    template <typename T>
    void ExtractJavaList(jobject source, std::vector<T> *result,
                         Transform<T> *transform);

    void ConvertJavaBoolArray(std::vector<uint8_t> *source,
                              jbooleanArray *result);

    void ConvertJavaByteArray(std::vector<int8_t> *source, jbyteArray *result);

    void ConvertJavaCharArray(std::vector<uint16_t> *source,
                              jcharArray *result);

    void ConvertJavaShortArray(std::vector<int16_t> *source,
                               jshortArray *result);

    void ConvertJavaIntArray(std::vector<int32_t> *source, jintArray *result);

    void ConvertJavaLongArray(std::vector<int64_t> *source, jlongArray *result);

    void ConvertJavaFloatArray(std::vector<float> *source, jfloatArray *result);

    void ConvertJavaDoubleArray(std::vector<double> *source,
                                jdoubleArray *result);

    void ConvertJavaString(std::string *source, jstring *result);

    void ConvertJavaString(std::string const *source, jstring *result);

    void ConvertJavaString(const char *source, jstring *result);

    void ConvertJavaStringArray(std::vector<std::string> *source,
                                jobjectArray *result);

    template <typename T>
    void ConvertJavaObject(T *source, jobject *result, Transform<T> *transform);

    template <typename T>
    void ConvertJavaObjectArray(std::vector<T> *source, jobjectArray *result,
                                Transform<T> *transform);

    template <typename K, typename V>
    void ConvertJavaMap(std::map<K, V> *source, jobject *result,
                        Transform<K> *keyTransform,
                        Transform<V> *valueTransform);

    template <typename T>
    void ConvertJavaList(std::vector<T> *source, jobject *result,
                         Transform<T> *transform);

    jobject NewObject(std::string className);

private:
    std::shared_ptr<JNIUtils> jniUtils = nullptr;
};

template <class T>
void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, T *result,
                                     Transform<T> *transform) {
    JNI_LOGI("GetFieldValue(Object): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !result || !transform) {
        JNI_LOGE("GetFieldValue(Object) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT,
                                 &type)) {
        JNIEnv *env = GetJNIEnv();
        if (env) {
            jniUtils->template GetObjectField(env, object, &info, result,
                                              transform);
        }
    } else {
        JNI_LOGE(
            "GetFieldValue(Object): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(Object): end");
}

template <class T>
void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<T> *result,
                                     Transform<T> *transform) {
    JNI_LOGI("GetFieldValue(ObjectArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !result || !transform) {
        JNI_LOGE("GetFieldValue(ObjectArray) : param error");
        return;
    }
    JNIEnv *env = GetJNIEnv();
    if (env) {
        int32_t type;
        if (JNIInfoUtil::CheckIsTypeList(
                &(info.fieldInfo.baseType),
                MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT, &type)) {
            jniUtils->template GetListField(env, object, &info, result,
                                            transform);
        } else if (JNIInfoUtil::CheckIsTypeArray(
                       &(info.fieldInfo.baseType),
                       MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT, &type)) {
            jniUtils->template GetObjectArrayField(env, object, &info, result,
                                                   transform);
        } else {
            JNI_LOGE(
                "GetFieldValue(ObjectArray): Type Err, current(arrayDimension: "
                "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
                info.fieldInfo.baseType.arrayDimension, (int32_t)type);
        }
    }
    JNI_LOGI("GetFieldValue(ObjectArray): end");
}

template <typename K, typename V>
void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::map<K, V> *result,
                                     Transform<K> *keyTransform,
                                     Transform<V> *valueTransform) {
    JNI_LOGI("GetFieldValue(Map): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !result) {
        JNI_LOGE("GetFieldValue(Map) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_MAP,
                                 &type)) {
        JNIEnv *env = GetJNIEnv();
        if (env) {
            jniUtils->template GetMapField(env, object, &info, result,
                                           keyTransform, valueTransform);
        }
    } else {
        JNI_LOGE(
            "GetFieldValue(Map): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, type);
    }
    JNI_LOGI("GetFieldValue(Map): end");
}

template <class T>
void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, T *source,
                                     Transform<T> *transform) {
    JNI_LOGI("SetFieldValue(Object): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source || !transform) {
        JNI_LOGE("SetFieldValue(Object) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT,
                                 &type)) {
        JNIEnv *env = GetJNIEnv();
        if (env) {
            jniUtils->template SetObjectField(env, object, &info, source,
                                              transform);
        }
    } else {
        JNI_LOGE(
            "SetFieldValue(Object): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(Object): end");
}

template <class T>
void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<T> *source,
                                     Transform<T> *transform) {
    JNI_LOGI("SetFieldValue(ObjectArray): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source || !transform) {
        JNI_LOGE("SetFieldValue(ObjectArray) : param error");
        return;
    }
    JNIEnv *env = GetJNIEnv();
    if (env) {
        int32_t type;
        if (JNIInfoUtil::CheckIsTypeList(
                &(info.fieldInfo.baseType),
                MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT, &type)) {
            jniUtils->template SetListField(env, object, &info, source,
                                            transform);
        } else if (JNIInfoUtil::CheckIsTypeArray(
                       &(info.fieldInfo.baseType),
                       MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT, &type)) {
            jniUtils->template SetObjectArrayField(env, object, &info, source,
                                                   transform);
        } else {
            JNI_LOGE(
                "SetFieldValue(ObjectArray): Type Err, current(arrayDimension: "
                "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
                info.fieldInfo.baseType.arrayDimension, (int32_t)type);
        }
    }
    JNI_LOGI("SetFieldValue(ObjectArray): end");
}

template <typename K, typename V>
void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::map<K, V> *source,
                                     Transform<K> *keyTransform,
                                     Transform<V> *valueTransform) {
    JNI_LOGI("SetFieldValue(Map): begin(%" LOG_LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!object || !source) {
        JNI_LOGE("SetFieldValue(Map) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(info.fieldInfo.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_MAP,
                                 &type)) {
        JNIEnv *env = GetJNIEnv();
        if (env) {
            jniUtils->template SetMapField(env, object, &info, source,
                                           keyTransform, valueTransform);
        }
    } else {
        JNI_LOGE(
            "SetFieldValue(Map): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            info.fieldInfo.baseType.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(Map): end");
}

template <typename T>
void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, T *result,
                                      Transform<T> *transform) {
    JNI_LOGI("CallJavaMethod(Object): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    int32_t returnType;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT,
                                 &returnType)) {
        JNIEnv *env = GetJNIEnv();
        if (env) {
            jniUtils->template CallJavaObjectMethod(env, &methodInfo, object,
                                                    param, result, transform);
        }
    } else {
        JNI_LOGE(
            "CallJavaMethod(Object): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension,
            (int32_t)returnType);
    }
}

template <typename T>
void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, std::vector<T> *result,
                                      Transform<T> *transform) {
    JNI_LOGI("CallJavaMethod(ObjectArray): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    JNIEnv *env = GetJNIEnv();
    if (env) {
        int32_t type;
        if (JNIInfoUtil::CheckIsTypeList(
                &(methodInfo.returnObject.baseType),
                MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT, &type)) {
            jniUtils->template CallJavaListMethod(env, &methodInfo, object,
                                                  param, result, transform);
        } else if (JNIInfoUtil::CheckIsTypeArray(
                       &(methodInfo.returnObject.baseType),
                       MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT, &type)) {
            jniUtils->template CallJavaObjectArrayMethod(
                env, &methodInfo, object, param, result, transform);
        } else {
            JNI_LOGE(
                "CallJavaMethod(ObjectArray): Type Err, "
                "current(arrayDimension: "
                "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
                methodInfo.returnObject.baseType.arrayDimension, (int32_t)type);
        }
    }
    JNI_LOGI("CallJavaMethod(ObjectArray): end.");
}

template <typename K, typename V>
void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, std::map<K, V> *result,
                                      Transform<K> *keyTransform,
                                      Transform<V> *valueTransform) {
    JNI_LOGI("CallJavaMethod(Map): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    if (!object || !result || !keyTransform || !valueTransform) {
        JNI_LOGE("CallJavaMethod(Map) : param error");
        return;
    }
    int32_t type;
    if (JNIInfoUtil::CheckIsType(&(methodInfo.returnObject.baseType),
                                 MethodFlag::FLAG_JNI_METHOD_RETURN_MAP,
                                 &type)) {
        JNIEnv *env = GetJNIEnv();
        if (env) {
            jniUtils->template CallJavaMapMethod(env, &methodInfo, object,
                                                 param, result, keyTransform,
                                                 valueTransform);
        }
    } else {
        JNI_LOGE(
            "CallJavaMethod(Map): Type Err, current(arrayDimension: "
            "%" LOG_LIMIT "d, type: %" LOG_LIMIT "d)",
            methodInfo.returnObject.baseType.arrayDimension, type);
    }
    JNI_LOGI("CallJavaMethod(Map): end");
}

template <class T>
void JSCallAndroidJni::ConvertJavaObject(T *source, jobject *result,
                                         Transform<T> *transform) {
    JNI_LOGI("ConvertJavaObject: begin.");
    if (!source || !transform) {
        JNI_LOGE("ConvertJavaObject: params is null");
        return;
    }
    JNIEnv *env = GetJNIEnv();
    if (env) {
        jniUtils->template ConvertJavaObject(env, source, result, transform);
    }
    JNI_LOGI("ConvertJavaObject: end.");
}

template <typename K, typename V>
void JSCallAndroidJni::ConvertJavaMap(std::map<K, V> *source, jobject *result,
                                      Transform<K> *keyTransform,
                                      Transform<V> *valueTransform) {
    JNI_LOGI("ConvertJavaMap: begin.");
    if (!source || !keyTransform || !valueTransform) {
        JNI_LOGE("ConvertJavaMap: params is null");
        return;
    }
    JNIEnv *env = GetJNIEnv();
    if (env) {
        jniUtils->ConvertJavaMap(env, source, result, keyTransform,
                                 valueTransform);
    }
    JNI_LOGI("ConvertJavaMap: end.");
}

template <class T>
void JSCallAndroidJni::ConvertJavaObjectArray(std::vector<T> *source,
                                              jobjectArray *result,
                                              Transform<T> *transform) {
    JNI_LOGI("ConvertJavaObjectArray: begin.");
    if (!source || !transform) {
        JNI_LOGE("ConvertJavaObjectArray: params is null");
        return;
    }
    JNIEnv *env = GetJNIEnv();
    if (env) {
        jniUtils->template ConvertJavaObjectArray(env, source, result,
                                                  transform);
    }
    JNI_LOGI("ConvertJavaObjectArray: end.");
}

template <class T>
void JSCallAndroidJni::ConvertJavaList(std::vector<T> *source, jobject *result,
                                       Transform<T> *transform) {
    JNI_LOGI("ConvertJavaList: begin.");
    if (!source || !transform) {
        JNI_LOGE("ConvertJavaList: params is null");
        return;
    }
    JNIEnv *env = GetJNIEnv();
    if (env) {
        jniUtils->ConvertJavaList(env, source, result, transform);
    }
    JNI_LOGI("ConvertJavaList: end.");
}

template <class T>
void JSCallAndroidJni::ExtractJavaObject(jobject source, T *result,
                                         Transform<T> *transform) {
    JNI_LOGI("ExtractJavaObject: begin.");
    if (!source || !transform) {
        JNI_LOGE("ExtractJavaObject: params is null");
        return;
    }
    JNIEnv *env = GetJNIEnv();
    if (env) {
        jniUtils->ExtractJavaObject(env, source, result, transform);
    }
    JNI_LOGI("ExtractJavaObject: end.");
}

template <typename K, typename V>
void JSCallAndroidJni::ExtractJavaMap(jobject source, std::map<K, V> *result,
                                      Transform<K> *keyTransform,
                                      Transform<V> *valueTransform) {
    JNI_LOGI("ExtractJavaMap: begin.");
    if (!source) {
        JNI_LOGE("ExtractJavaMap: params is null");
        return;
    }
    JNIEnv *env = GetJNIEnv();
    if (env) {
        jniUtils->ExtractJavaMap(env, source, result, keyTransform,
                                 valueTransform);
    }
    JNI_LOGI("ExtractJavaMap: end.");
}

template <class T>
void JSCallAndroidJni::ExtractJavaObjectArray(jobjectArray source,
                                              std::vector<T> *result,
                                              Transform<T> *transform) {
    JNI_LOGI("ExtractJavaObjectArray: begin.");
    if (!source || !transform) {
        JNI_LOGE("ExtractJavaObjectArray: params is null");
        return;
    }
    JNIEnv *env = GetJNIEnv();
    if (env) {
        jniUtils->ExtractJavaObjectArray(env, source, result, transform);
    }
    JNI_LOGI("ExtractJavaObjectArray: end.");
}

template <class T>
void JSCallAndroidJni::ExtractJavaList(jobject source, std::vector<T> *result,
                                       Transform<T> *transform) {
    JNI_LOGI("ExtractJavaList: begin.");
    if (!source || !transform) {
        JNI_LOGE("ExtractJavaList: params is null");
        return;
    }
    JNIEnv *env = GetJNIEnv();
    if (env) {
        jniUtils->ExtractJavaList(env, source, result, transform);
    }
    JNI_LOGI("ExtractJavaList: end.");
}

class TransformBoolean : public Transform<jboolean> {
    using Transform::Transform;

public:
    void Extract(jobject source, jboolean *target) override;

    void Convert(jobject target, jboolean *source) override{};

    jobject CreateObject(jboolean *source) override;
};

class TransformByte : public Transform<jbyte> {
    using Transform::Transform;

public:
    void Extract(jobject source, jbyte *target) override;

    void Convert(jobject target, jbyte *source) override{};

    jobject CreateObject(jbyte *source) override;
};

class TransformChar : public Transform<jchar> {
    using Transform::Transform;

public:
    void Extract(jobject source, jchar *target) override;

    void Convert(jobject target, jchar *source) override{};

    jobject CreateObject(jchar *source) override;
};

class TransformShort : public Transform<jshort> {
    using Transform::Transform;

public:
    void Extract(jobject source, jshort *target) override;

    void Convert(jobject target, jshort *source) override{};

    jobject CreateObject(jshort *source) override;
};

class TransformInt : public Transform<jint> {
    using Transform::Transform;

public:
    void Extract(jobject source, jint *target) override;

    void Convert(jobject target, jint *source) override{};

    jobject CreateObject(jint *source) override;
};

class TransformLong : public Transform<jlong> {
    using Transform::Transform;

public:
    void Extract(jobject source, jlong *target) override;

    void Convert(jobject target, jlong *source) override{};

    jobject CreateObject(jlong *source) override;
};

class TransformFloat : public Transform<jfloat> {
    using Transform::Transform;

public:
    void Extract(jobject source, jfloat *target) override;

    void Convert(jobject target, jfloat *source) override{};

    jobject CreateObject(jfloat *source) override;
};

class TransformDouble : public Transform<jdouble> {
    using Transform::Transform;

public:
    void Extract(jobject source, jdouble *target) override;

    void Convert(jobject target, jdouble *source) override{};

    jobject CreateObject(jdouble *source) override;
};

class TransformString : public Transform<std::string> {
    using Transform::Transform;

public:
    void Extract(jobject source, std::string *target) override;

    void Convert(jobject target, std::string *source) override{};

    jobject CreateObject(std::string *source) override;
};
}  // namespace TEMPLATE
}  // namespace OHOS
#endif  // ANNOTATIONJNI_JS_CALL_ANDROID_JNI_H
