//
// Created by guobin on 2022/2/28.
//

#ifndef ANNOTATIONJNI_JS_CALL_ANDROID_JNI_H
#define ANNOTATIONJNI_JS_CALL_ANDROID_JNI_H

#include <jni.h>
#include <set>
#include <map>
#include <nlohmann/json.hpp>
#include "jkit.h"
#include "jni_utils.h"
#include "jni_transform.h"
#include "json_util.h"
#include "javaapiheaders/jni_method_flag.h"
#include "singleton.h"

namespace OHOS {
    class JSCallAndroidJni {
        JSCallAndroidJni();

        friend DelayedSingleton<JSCallAndroidJni>;

    public:
        ~JSCallAndroidJni();

        void InitJavaVm(JavaVM *vm);

        void NativeInit(JNIEnv *env, std::string config);

        void CallJavaMethod(int32_t methodID, jobject object, jvalue *param, uint8_t *result);

        void CallJavaMethod(int32_t methodID, jobject object, jvalue *param, int8_t *result);

        void CallJavaMethod(int32_t methodID, jobject object, jvalue *param, uint16_t *result);

        void CallJavaMethod(int32_t methodID, jobject object, jvalue *param, int16_t *result);

        void CallJavaMethod(int32_t methodID, jobject object, jvalue *param, int32_t *result);

        void CallJavaMethod(int32_t methodID, jobject object, jvalue *param, int64_t *result);

        void CallJavaMethod(int32_t methodID, jobject object, jvalue *param, float *result);

        void CallJavaMethod(int32_t methodID, jobject object, jvalue *param, double *result);

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

        void
        CallJavaMethod(int32_t methodID, jobject object, jvalue *param, std::vector<float> *result);

        void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                            std::vector<double> *result);

        void CallJavaMethod(int32_t methodID, jobject object, jvalue *param, std::string *result);

        void CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                            std::vector<std::string> *result);

        void
        CallJavaMethod(int32_t methodID, jobject object, jvalue *param, JavaMethodResult *result);

        template<typename T>
        void
        CallJavaMethod(int32_t methodID, jobject object, jvalue *param, Transform<T> *transform);

        void GetJNIFieldInfo(int32_t id, JNIFieldInfo *jniFieldInfo);

        void GetFieldValue(jobject object, int32_t fieldID, uint8_t *target);

        void GetFieldValue(jobject object, int32_t fieldID, int8_t *target);

        void GetFieldValue(jobject object, int32_t fieldID, uint16_t *target);

        void GetFieldValue(jobject object, int32_t fieldID, int16_t *target);

        void GetFieldValue(jobject object, int32_t fieldID, int32_t *target);

        void GetFieldValue(jobject object, int32_t fieldID, int64_t *target);

        void GetFieldValue(jobject object, int32_t fieldID, float *target);

        void GetFieldValue(jobject object, int32_t fieldID, double *target);

        void GetFieldValue(jobject object, int32_t fieldID, std::string *target);

        void GetFieldValue(jobject object, int32_t fieldID, std::vector<uint8_t> *target);

        void GetFieldValue(jobject object, int32_t fieldID, std::vector<int8_t> *target);

        void GetFieldValue(jobject object, int32_t fieldID, std::vector<uint16_t> *target);

        void GetFieldValue(jobject object, int32_t fieldID, std::vector<int16_t> *target);

        void GetFieldValue(jobject object, int32_t fieldID, std::vector<int32_t> *target);

        void GetFieldValue(jobject object, int32_t fieldID, std::vector<int64_t> *target);

        void GetFieldValue(jobject object, int32_t fieldID, std::vector<float> *target);

        void GetFieldValue(jobject object, int32_t fieldID, std::vector<double> *target);

        void GetFieldValue(jobject object, int32_t fieldID, std::vector<std::string> *target);

        template<class T>
        void GetFieldValue(jobject object, int32_t fieldID, Transform<T> *transform);

        void SetFieldValue(jobject object, int32_t fieldID, uint8_t *source);

        void SetFieldValue(jobject object, int32_t fieldID, int8_t *source);

        void SetFieldValue(jobject object, int32_t fieldID, uint16_t *source);

        void SetFieldValue(jobject object, int32_t fieldID, int16_t *source);

        void SetFieldValue(jobject object, int32_t fieldID, int32_t *source);

        void SetFieldValue(jobject object, int32_t fieldID, int64_t *source);

        void SetFieldValue(jobject object, int32_t fieldID, float *source);

        void SetFieldValue(jobject object, int32_t fieldID, double *source);

        void SetFieldValue(jobject object, int32_t fieldID, std::string *source);

        void SetFieldValue(jobject object, int32_t fieldID, std::vector<uint8_t> *source);

        void SetFieldValue(jobject object, int32_t fieldID, std::vector<int8_t> *source);

        void SetFieldValue(jobject object, int32_t fieldID, std::vector<uint16_t> *source);

        void SetFieldValue(jobject object, int32_t fieldID, std::vector<int16_t> *source);

        void SetFieldValue(jobject object, int32_t fieldID, std::vector<int32_t> *source);

        void SetFieldValue(jobject object, int32_t fieldID, std::vector<int64_t> *source);

        void SetFieldValue(jobject object, int32_t fieldID, std::vector<float> *source);

        void SetFieldValue(jobject object, int32_t fieldID, std::vector<double> *source);

        void SetFieldValue(jobject object, int32_t fieldID, std::vector<std::string> *source);

        template<class T>
        void SetFieldValue(jobject object, int32_t fieldID, Transform<T> *transform);

    private:
        JNIInfo jniInfo;
        std::map<std::string, jclass> jclassIDs;
        std::map<int32_t, JNIMethodInfo> jniMethodInfos;
        std::map<int32_t, JNIFieldInfo> jniFieldInfos;
    };

    template<class T>
    void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, Transform<T> *transform) {
        if (!transform) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("GetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        if (!info.classID || !info.fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info.fieldInfo.flag);
        if (info.fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT) {
            jobject source = JNIUtils::GetObjectField(env, object, &info);
            transform->Extract(source, transform->t);
        }
    }

    template<class T>
    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, Transform<T> *transform) {
        if (!transform) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("GetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        if (!info.classID || !info.fieldId) {
            JNI_LOGE("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info.fieldInfo.flag);
        if (info.fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT) {
            if (jclassIDs.count(info.fieldInfo.clsName) < 1) {
                JNI_LOGE("GetFieldValue : classID is not init");
            }
            jclass targetClass = jclassIDs.at(info.fieldInfo.clsName);
            jmethodID init = env->GetMethodID(targetClass, "<init>", "()V");
            jobject target = env->NewObject(targetClass, init);
            transform->Convert(target, transform->t);
            env->SetObjectField(object, info.fieldId, target);
        }
    }

    template<typename T>
    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          Transform<T> *transform) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (methodInfo.returnObject.arrayDimension == 0 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT) {
            jobject source = JNIUtils::CallJavaObjectMethod(env, &methodInfo, object, param);
            transform->Extract(source, transform->t);
        }
    }
}
#endif //ANNOTATIONJNI_JS_CALL_ANDROID_JNI_H
