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
    void NativeInit(JNIEnv *env, const std::string& config);
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
    template <class T>
    void GetFieldValue(jobject object, int32_t fieldID, T *result,
                       Transform<T> *transform);
    template <class T>
    void GetFieldValue(jobject object, int32_t fieldID, std::vector<T> *result,
                       Transform<T> *transform);
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

    template <class T>
    void SetFieldValue(jobject object, int32_t fieldID, T *source,
                       Transform<T> *transform);
    template <class T>
    void SetFieldValue(jobject object, int32_t fieldID, std::vector<T> *source,
                       Transform<T> *transform);
    jstring NewStringUTF(const char *string);
    jobject NewObject(std::string className);
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
    template <class T>
    void ExtractJavaObject(jobject source, T *result, Transform<T> *transform);
    template <class T>
    void ExtractJavaObjectArray(jobjectArray source, std::vector<T> *result,
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
    template <class T>
    void ConvertJavaObject(T *source, jobject *result, Transform<T> *transform);
    template <class T>
    void ConvertJavaObjectArray(std::vector<T> *source, jobjectArray *result,
                                Transform<T> *transform);

private:
    jobject NewObject(JNIEnv *env, std::string *className);

private:
    JNIInfo jniInfo;
    std::map<std::string, jclass> jclassIDs;
    std::map<int32_t, JNIMethodInfo> jniMethodInfos;
    std::map<int32_t, JNIFieldInfo> jniFieldInfos;
};

template <class T>
void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, T *result,
                                     Transform<T> *transform) {
    JNI_LOGI("GetFieldValue(Object): begin(%" LIMIT "d)", fieldID);
    if (jniFieldInfos.empty() || jniFieldInfos.count(fieldID) < 1) {
        JNI_LOGE("GetFieldValue(Object): fieldID is not init");
        return;
    }
    JNIFieldInfo info = jniFieldInfos.at(fieldID);
    if (!info.classID || !info.fieldId || !object || !result || !transform) {
        JNI_LOGE("GetFieldValue(Object) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(Object): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jobject source = JNIUtils::GetObjectField(env, object, &info);
        transform->Extract(source, result);
        env->DeleteLocalRef(source);
    } else {
        JNI_LOGE(
            "GetFieldValue(Object): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(Object): end");
}

template <class T>
void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<T> *result,
                                     Transform<T> *transform) {
    JNI_LOGI("GetFieldValue(ObjectArray): begin(%" LIMIT "d)", fieldID);
    if (jniFieldInfos.empty() || jniFieldInfos.count(fieldID) < 1) {
        JNI_LOGE("GetFieldValue(ObjectArray): fieldID is not init");
        return;
    }
    JNIFieldInfo info = jniFieldInfos.at(fieldID);
    if (!info.classID || !info.fieldId || !object || !result || !transform) {
        JNI_LOGE("GetFieldValue(ObjectArray) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(ObjectArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jobjectArray source =
            (jobjectArray)JNIUtils::GetObjectField(env, object, &info);
        ExtractJavaObjectArray(source, result, transform);
        env->DeleteLocalRef(source);
    } else {
        JNI_LOGE(
            "GetFieldValue(ObjectArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(ObjectArray): end");
}

template <class T>
void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, T *source,
                                     Transform<T> *transform) {
    JNI_LOGI("SetFieldValue(Object): begin(%" LIMIT "d)", fieldID);
    if (jniFieldInfos.empty() || jniFieldInfos.count(fieldID) < 1) {
        JNI_LOGE("SetFieldValue(Object): fieldID is not init");
        return;
    }
    JNIFieldInfo info = jniFieldInfos.at(fieldID);
    if (!info.classID || !info.fieldId || !object || !source || !transform) {
        JNI_LOGE("SetFieldValue(Object) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(Object): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jobject target = NewObject(env, &(info.fieldInfo.clsName));
        if (target) {
            transform->Convert(target, source);
            env->SetObjectField(object, info.fieldId, target);
        }
    } else {
        JNI_LOGE(
            "SetFieldValue(Object): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(Object): end");
}

template <class T>
void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<T> *source,
                                     Transform<T> *transform) {
    JNI_LOGI("SetFieldValue(ObjectArray): begin(%" LIMIT "d)", fieldID);
    if (jniFieldInfos.empty() || jniFieldInfos.count(fieldID) < 1) {
        JNI_LOGE("SetFieldValue(ObjectArray): fieldID is not init");
        return;
    }
    JNIFieldInfo info = jniFieldInfos.at(fieldID);
    if (!info.classID || !info.fieldId || !object || !source || !transform) {
        JNI_LOGE("SetFieldValue(ObjectArray) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(ObjectArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jobjectArray target;
        ConvertJavaObjectArray(source, &target, transform);
        env->SetObjectField(object, info.fieldId, target);
    } else {
        JNI_LOGE(
            "SetFieldValue(ObjectArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(ObjectArray): end");
}

template <typename T>
void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, T *result,
                                      Transform<T> *transform) {
    JNI_LOGI("CallJavaMethod(Object): begin.");
    if (jniMethodInfos.empty() || jniMethodInfos.count(methodID) < 1) {
        JNI_LOGE("CallJavaMethod(Object): fieldID is not init");
        return;
    }
    JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
    if (!methodInfo.classID || !methodInfo.methodID || !result) {
        JNI_LOGE("CallJavaMethod(Object): param error.");
        return;
    }
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(Object): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 0 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Object): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jobject source =
            JNIUtils::CallJavaObjectMethod(env, &methodInfo, object, param);
        transform->Extract(source, result);
        env->DeleteLocalRef(source);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Object): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
    }
}

template <typename T>
void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param, std::vector<T> *result,
                                      Transform<T> *transform) {
    JNI_LOGI("CallJavaMethod(ObjectArray): begin.");
    if (jniMethodInfos.empty() || jniMethodInfos.count(methodID) < 1) {
        JNI_LOGE("CallJavaMethod(ObjectArray): fieldID is not init");
        return;
    }
    JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
    if (!methodInfo.classID || !methodInfo.methodID || !result) {
        JNI_LOGE("CallJavaMethod(ObjectArray): param error.");
        return;
    }
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(ObjectArray): returnType: %" LIMIT "d",
             returnType);
    if (methodInfo.returnObject.arrayDimension == 1 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(ObjectArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        jobjectArray source = (jobjectArray)JNIUtils::CallJavaObjectMethod(
            env, &methodInfo, object, param);
        ExtractJavaObjectArray(source, result, transform);
        env->DeleteLocalRef(source);
    } else {
        JNI_LOGE(
            "CallJavaMethod(ObjectArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
    }
}

template <class T>
void JSCallAndroidJni::ConvertJavaObject(T *source, jobject *result,
                                         Transform<T> *transform) {
    JNI_LOGI("ConvertJavaObject: begin.");
    if (!source || !transform) {
        JNI_LOGE("ConvertJavaObject: params is null");
        return;
    }
    auto object = NewObject(transform->GetClassName());
    if (object) {
        transform->Convert(object, source);
        (*result) = object;
    } else {
        JNI_LOGE("ConvertJavaObject: NewObject failed.");
    }
    JNI_LOGI("ConvertJavaObject: end.");
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
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ConvertJavaObjectArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    if (env) {
        int size = source->size();
        std::string className = transform->GetClassName();
        if (size > 0 && jclassIDs.count(className) > 0) {
            jclass targetClass = jclassIDs.at(className);
            auto array = env->NewObjectArray(size, targetClass, NULL);
            (*result) = static_cast<jobjectArray>(env->NewGlobalRef(array));
            for (int i = 0; i < size; ++i) {
                // TODO: arrayȫ�ֺ�, item�Ƿ���Ҫȫ��
                jobject formInfo = NewObject(env, &className);
                transform->Convert(formInfo, &(source->at(i)));
                env->SetObjectArrayElement(*result, i, formInfo);
            }
        }
    }
    JNI_LOGI("ConvertJavaObjectArray: end.");
}

template <class T>
void JSCallAndroidJni::ExtractJavaObject(jobject source, T *result,
                                         Transform<T> *transform) {
    JNI_LOGI("ExtractJavaObject: begin.");
    if (!source || !transform) {
        JNI_LOGE("ExtractJavaObject: params is null");
        return;
    }
    transform->Extract(source, result);
    JNI_LOGI("ExtractJavaObject: end.");
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
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("ExtractJavaObjectArray: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    if (env) {
        int length = env->GetArrayLength(source);
        for (int i = 0; i < length; i++) {
            auto object = env->GetObjectArrayElement(source, i);
            if (object) {
                T resultItem;
                transform->Extract(object, &resultItem);
                result->push_back(resultItem);
                env->DeleteLocalRef(object);
            }
        }
    }

    JNI_LOGI("ExtractJavaObjectArray: end.");
}
}  // namespace TEMPLATE
}  // namespace OHOS
#endif  // ANNOTATIONJNI_JS_CALL_ANDROID_JNI_H
