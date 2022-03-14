//
// Created by guobin on 2022/3/10.
//

#include "jni_log.h"
#include "jni_transform.h"
#include "javaapiheaders/jni_method_flag.h"

namespace OHOS {
//    cvalue GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info) {
//        cvalue result;
//        if (!object || !info->classID || !info->fieldId) {
//            JNI_LOGE("CallJavaMethod: param error.");
//            return result;
//        }
//        MethodFlag type = GetReturnType(info->fieldInfo.flag);
//        if (info->fieldInfo.arrayDimension == 0) {
//            switch (type) {
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN:
//                    result.z = env->GetBooleanField(object, info->fieldId);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE:
//                    result.b = env->GetByteField(object, info->fieldId);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR:
//                    result.c = env->GetCharField(object, info->fieldId);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT:
//                    result.s = env->GetShortField(object, info->fieldId);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_INT:
//                    result.i = env->GetIntField(object, info->fieldId);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_LONG:
//                    result.j = env->GetLongField(object, info->fieldId);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT:
//                    result.f = env->GetFloatField(object, info->fieldId);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE:
//                    result.d = env->GetDoubleField(object, info->fieldId);
//                    break;
//                default:
//                    JNI_LOGE(
//                            "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
//                            static_cast<int32_t>(type),
//                            info->fieldInfo.arrayDimension);
//                    break;
//            }
//            result->push_back(ret);
//        } else if (info->fieldInfo.arrayDimension == 1) {
//            jobject jObjectResult = env->GetStat
//            if (!jObjectResult) {
//                JNI_LOGE("jObjectResult is null");
//                return;
//            }
//            switch (type) {
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN:
//                    ExtractJavaBoolArray(env, (jbooleanArray) jObjectResult, result);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE:
//                    ExtractJavaByteArray(env, (jbyteArray) jObjectResult, result);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR:
//                    ExtractJavaCharArray(env, (jcharArray) jObjectResult, result);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT:
//                    ExtractJavaShortArray(env, (jshortArray) jObjectResult, result);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_INT:
//                    ExtractJavaIntArray(env, (jintArray) jObjectResult, result);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_LONG:
//                    ExtractJavaLongArray(env, (jlongArray) jObjectResult, result);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT:
//                    ExtractJavaFloatArray(env, (jfloatArray) jObjectResult, result);
//                    break;
//                case MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE:
//                    ExtractJavaDoubleArray(env, (jdoubleArray) jObjectResult, result);
//                    break;
//                default:
//                    JNI_LOGE(
//                            "JNIMethodInfo is not match CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
//                            static_cast<int32_t>(returnType),
//                            methodInfo.returnObject.arrayDimension);
//                    break;
//            }
//            env->DeleteLocalRef(jObjectResult);
//        } else {
//            JNI_LOGE(
//                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
//                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
//        }
//        return result;
//    }

//    cvalue GetBooleanField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
//
//    }
//    cvalue GetByteField(JNIEnv *env, jobject object, JNIFieldInfo *info);
//    cvalue GetCharField(JNIEnv *env, jobject object, JNIFieldInfo *info);
//    cvalue GetShortField(JNIEnv *env, jobject object, JNIFieldInfo *info);
//    cvalue GetIntField(JNIEnv *env, jobject object, JNIFieldInfo *info);
//    cvalue GetLongField(JNIEnv *env, jobject object, JNIFieldInfo *info);
//    cvalue GetFloatField(JNIEnv *env, jobject object, JNIFieldInfo *info);
//    cvalue GetDoubleField(JNIEnv *env, jobject object, JNIFieldInfo *info);
}