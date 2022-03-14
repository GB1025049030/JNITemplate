//
// Created by guobin on 2022/3/10.
//

#include "jni_utils.h"
#include "jni_log.h"
#include "jkit.h"

namespace OHOS {
    void JNIUtils::ClearException(JNIEnv *env) {
        if (env->ExceptionCheck()) {
            JNI_LOGE("exception occurred");
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
    }

    jboolean JNIUtils::GetBooleanField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
        jboolean result = JNI_FALSE;
        if (IsStatic(info->fieldInfo.flag)) {
            result = env->GetStaticBooleanField(info->classID, info->fieldId);
        } else {
            if (!object) {
                JNI_LOGD("GetBooleanField : object is null");
                return result;
            }
            result = env->GetBooleanField(object, info->fieldId);
        }
        ClearException(env);
        return result;
    }

    void
    JNIUtils::SetBooleanField(JNIEnv *env, jobject object, JNIFieldInfo *info, jboolean value) {
        if (IsStatic(info->fieldInfo.flag)) {
            env->SetStaticBooleanField(info->classID, info->fieldId, value);
        } else {
            if (!object) {
                JNI_LOGD("SetBooleanField : object is null");
                return;
            }
            env->SetBooleanField(object, info->fieldId, value);
        }
        ClearException(env);
    }

    jbyte JNIUtils::GetByteField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
        jbyte result = 0;
        if (IsStatic(info->fieldInfo.flag)) {
            result = env->GetStaticByteField(info->classID, info->fieldId);
        } else {
            if (!object) {
                JNI_LOGD("GetByteField : object is null");
                return result;
            }
            result = env->GetByteField(object, info->fieldId);
        }
        ClearException(env);
        return result;
    }

    void
    JNIUtils::SetByteField(JNIEnv *env, jobject object, JNIFieldInfo *info, jbyte value) {
        if (IsStatic(info->fieldInfo.flag)) {
            env->SetStaticByteField(info->classID, info->fieldId, value);
        } else {
            if (!object) {
                JNI_LOGD("SetByteField : object is null");
                return;
            }
            env->SetByteField(object, info->fieldId, value);
        }
        ClearException(env);
    }

    jchar JNIUtils::GetCharField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
        jchar result = 0;
        if (IsStatic(info->fieldInfo.flag)) {
            result = env->GetStaticCharField(info->classID, info->fieldId);
        } else {
            if (!object) {
                JNI_LOGD("GetCharField : object is null");
                return result;
            }
            result = env->GetCharField(object, info->fieldId);
        }
        ClearException(env);
        return result;
    }

    void
    JNIUtils::SetCharField(JNIEnv *env, jobject object, JNIFieldInfo *info, jchar value) {
        if (IsStatic(info->fieldInfo.flag)) {
            env->SetStaticCharField(info->classID, info->fieldId, value);
        } else {
            if (!object) {
                JNI_LOGD("SetCharField : object is null");
                return;
            }
            env->SetCharField(object, info->fieldId, value);
        }
        ClearException(env);
    }

    jshort JNIUtils::GetShortField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
        jshort result = 0;
        if (IsStatic(info->fieldInfo.flag)) {
            result = env->GetStaticShortField(info->classID, info->fieldId);
        } else {
            if (!object) {
                JNI_LOGD("GetShortField : object is null");
                return result;
            }
            result = env->GetShortField(object, info->fieldId);
        }
        ClearException(env);
        return result;
    }

    void
    JNIUtils::SetShortField(JNIEnv *env, jobject object, JNIFieldInfo *info, jshort value) {
        if (IsStatic(info->fieldInfo.flag)) {
            env->SetStaticShortField(info->classID, info->fieldId, value);
        } else {
            if (!object) {
                JNI_LOGD("SetShortField : object is null");
                return;
            }
            env->SetShortField(object, info->fieldId, value);
        }
        ClearException(env);
    }

    jint JNIUtils::GetIntField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
        jint result = 0;
        if (IsStatic(info->fieldInfo.flag)) {
            result = env->GetStaticIntField(info->classID, info->fieldId);
        } else {
            if (!object) {
                JNI_LOGD("GetIntField : object is null");
                return result;
            }
            result = env->GetIntField(object, info->fieldId);
        }
        ClearException(env);
        return result;
    }

    void
    JNIUtils::SetIntField(JNIEnv *env, jobject object, JNIFieldInfo *info, jint value) {
        if (IsStatic(info->fieldInfo.flag)) {
            env->SetStaticIntField(info->classID, info->fieldId, value);
        } else {
            if (!object) {
                JNI_LOGD("SetIntField : object is null");
                return;
            }
            env->SetIntField(object, info->fieldId, value);
        }
        ClearException(env);
    }

    jlong JNIUtils::GetLongField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
        jlong result = 0;
        if (IsStatic(info->fieldInfo.flag)) {
            result = env->GetStaticLongField(info->classID, info->fieldId);
        } else {
            if (!object) {
                JNI_LOGD("GetLongField : object is null");
                return result;
            }
            result = env->GetLongField(object, info->fieldId);
        }
        ClearException(env);
        return result;
    }

    void
    JNIUtils::SetLongField(JNIEnv *env, jobject object, JNIFieldInfo *info, jlong value) {
        if (IsStatic(info->fieldInfo.flag)) {
            env->SetStaticLongField(info->classID, info->fieldId, value);
        } else {
            if (!object) {
                JNI_LOGD("SetLongField : object is null");
                return;
            }
            env->SetLongField(object, info->fieldId, value);
        }
        ClearException(env);
    }

    jfloat JNIUtils::GetFloatField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
        jfloat result = 0;
        if (IsStatic(info->fieldInfo.flag)) {
            result = env->GetStaticFloatField(info->classID, info->fieldId);
        } else {
            if (!object) {
                JNI_LOGD("GetFloatField : object is null");
                return result;
            }
            result = env->GetFloatField(object, info->fieldId);
        }
        ClearException(env);
        return result;
    }

    void
    JNIUtils::SetFloatField(JNIEnv *env, jobject object, JNIFieldInfo *info, jfloat value) {
        if (IsStatic(info->fieldInfo.flag)) {
            env->SetStaticFloatField(info->classID, info->fieldId, value);
        } else {
            if (!object) {
                JNI_LOGD("SetFloatField : object is null");
                return;
            }
            env->SetFloatField(object, info->fieldId, value);
        }
        ClearException(env);
    }

    jdouble JNIUtils::GetDoubleField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
        jdouble result = 0;
        if (IsStatic(info->fieldInfo.flag)) {
            result = env->GetStaticDoubleField(info->classID, info->fieldId);
        } else {
            if (!object) {
                JNI_LOGD("GetDoubleField : object is null");
                return result;
            }
            result = env->GetDoubleField(object, info->fieldId);
        }
        ClearException(env);
        return result;
    }

    void
    JNIUtils::SetDoubleField(JNIEnv *env, jobject object, JNIFieldInfo *info, jdouble value) {
        if (IsStatic(info->fieldInfo.flag)) {
            env->SetStaticDoubleField(info->classID, info->fieldId, value);
        } else {
            if (!object) {
                JNI_LOGD("SetDoubleField : object is null");
                return;
            }
            env->SetDoubleField(object, info->fieldId, value);
        }
        ClearException(env);
    }

    jobject JNIUtils::GetObjectField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
        jobject result = nullptr;
        if (IsStatic(info->fieldInfo.flag)) {
            result = env->GetStaticObjectField(info->classID, info->fieldId);
        } else {
            if (!object) {
                JNI_LOGD("GetObjectField : object is null");
                return result;
            }
            result = env->GetObjectField(object, info->fieldId);
        }
        ClearException(env);
        return result;
    }

    void
    JNIUtils::SetObjectField(JNIEnv *env, jobject object, JNIFieldInfo *info, jobject value) {
        if (IsStatic(info->fieldInfo.flag)) {
            env->SetStaticObjectField(info->classID, info->fieldId, value);
        } else {
            if (!object) {
                JNI_LOGD("SetObjectField : object is null");
                return;
            }
            env->SetObjectField(object, info->fieldId, value);
        }
        ClearException(env);
    }

    void
    JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, uint8_t *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN) {
            (*result) = GetBooleanField(env, object, info);
        } else {
            JNI_LOGE("GetFieldValue : GetBooleanField : JNIFieldInfo is not jboolean type");
        }
    }

    void
    JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int8_t *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
            (*result) = GetByteField(env, object, info);
        } else {
            JNI_LOGE("GetFieldValue : GetByteField : JNIFieldInfo is not jbyte type");
        }
    }


    void
    JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, uint16_t *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
            (*result) = GetCharField(env, object, info);
        } else {
            JNI_LOGE("GetFieldValue : GetCharField : JNIFieldInfo is not jchar type");
        }
    }

    void
    JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int16_t *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT) {
            (*result) = GetShortField(env, object, info);
        } else {
            JNI_LOGE("GetFieldValue : GetShortField : JNIFieldInfo is not jshort type");
        }
    }

    void
    JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int32_t *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 && type == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
            (*result) = GetIntField(env, object, info);
        } else {
            JNI_LOGE("GetFieldValue : GetIntField : JNIFieldInfo is not jint type");
        }
    }

    void
    JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int64_t *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_LONG) {
            (*result) = GetLongField(env, object, info);
        } else {
            JNI_LOGE("GetFieldValue : GetLongField : JNIFieldInfo is not jlong type");
        }
    }

    void
    JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, float *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
            (*result) = GetFloatField(env, object, info);
        } else {
            JNI_LOGE("GetFieldValue : GetFloatField : JNIFieldInfo is not jfloat type");
        }
    }

    void
    JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, double *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE) {
            (*result) = GetDoubleField(env, object, info);
        } else {
            JNI_LOGE("GetFieldValue : GetDoubleField : JNIFieldInfo is not jdouble type");
        }
    }

    void JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<uint8_t> *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
            jbooleanArray source = static_cast<jbooleanArray>(GetObjectField(env, object, info));
            ExtractJavaBoolArray(env, source, result);
            env->DeleteLocalRef(source);
        } else {
            JNI_LOGE(
                    "GetFieldValue : JNIFieldInfo is not jbooleanArray type");
        }
    }

    void JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<int8_t> *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
            jbyteArray source = static_cast<jbyteArray>(GetObjectField(env, object, info));
            ExtractJavaByteArray(env, source, result);
            env->DeleteLocalRef(source);
        } else {
            JNI_LOGE("GetFieldValue : JNIFieldInfo is not jbyteArray type");
        }
    }

    void JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<uint16_t> *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
            jcharArray source = static_cast<jcharArray>(GetObjectField(env, object, info));
            ExtractJavaCharArray(env, source, result);
            env->DeleteLocalRef(source);
        } else {
            JNI_LOGE("GetFieldValue : JNIFieldInfo is not jcharArray type");
        }
    }

    void JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<int16_t> *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
            jshortArray source = static_cast<jshortArray>(GetObjectField(env, object, info));
            ExtractJavaShortArray(env, source, result);
            env->DeleteLocalRef(source);
        } else {
            JNI_LOGE("GetFieldValue : JNIFieldInfo is not jshortArray type");
        }
    }

    void JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<int32_t> *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
            jintArray source = static_cast<jintArray>(GetObjectField(env, object, info));
            ExtractJavaIntArray(env, source, result);
            env->DeleteLocalRef(source);
        } else {
            JNI_LOGE("GetFieldValue : JNIFieldInfo is not jintArray type");
        }
    }

    void JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<int64_t> *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
            jlongArray source = static_cast<jlongArray>(GetObjectField(env, object, info));
            ExtractJavaLongArray(env, source, result);
            env->DeleteLocalRef(source);
        } else {
            JNI_LOGE("GetFieldValue : JNIFieldInfo is not jlongArray type");
        }
    }

    void JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<float> *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
            jfloatArray source = static_cast<jfloatArray>(GetObjectField(env, object, info));
            ExtractJavaFloatArray(env, source, result);
            env->DeleteLocalRef(source);
        } else {
            JNI_LOGE("GetFieldValue : JNIFieldInfo is not jfloatArray type");
        }
    }

    void JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<double> *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
            jdoubleArray source = static_cast<jdoubleArray>(GetObjectField(env, object, info));
            ExtractJavaDoubleArray(env, source, result);
            env->DeleteLocalRef(source);
        } else {
            JNI_LOGE("GetFieldValue : JNIFieldInfo is not jdoubleArray type");
        }
    }

    void JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::string *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING) {
            jstring source = static_cast<jstring>(GetObjectField(env, object, info));
            ExtractJavaString(env, source, result);
            env->DeleteLocalRef(source);
        } else {
            JNI_LOGE("GetFieldValue : JNIFieldInfo is not jdoubleArray type");
        }
    }

    void JNIUtils::GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<std::string> *result) {
        if (!env || !info || !result) {
            JNI_LOGD("GetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("GetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING) {
            jobjectArray source = static_cast<jobjectArray>(GetObjectField(env, object, info));
            ExtractJavaStringArray(env, source, result);
            env->DeleteLocalRef(source);
        } else {
            JNI_LOGE("GetFieldValue : JNIFieldInfo is not jdoubleArray type");
        }
    }

    void
    JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, uint8_t source) {
        if (!env || !info) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN) {
            SetBooleanField(env, object, info, source);
        } else {
            JNI_LOGE("SetFieldValue : SetBooleanField : JNIFieldInfo is not jboolean type");
        }
    }

    void
    JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int8_t source) {
        if (!env || !info) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
            SetByteField(env, object, info, source);
        } else {
            JNI_LOGE("SetFieldValue : SetByteField : JNIFieldInfo is not jbyte type");
        }
    }

    void
    JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, uint16_t source) {
        if (!env || !info) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
            SetCharField(env, object, info, source);
        } else {
            JNI_LOGE("SetFieldValue : SetCharField : JNIFieldInfo is not jchar type");
        }
    }

    void
    JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int16_t source) {
        if (!env || !info) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT) {
            SetShortField(env, object, info, source);
        } else {
            JNI_LOGE("SetFieldValue : SetShortField : JNIFieldInfo is not jshort type");
        }
    }

    void
    JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int32_t source) {
        if (!env || !info) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
            SetIntField(env, object, info, source);
        } else {
            JNI_LOGE("SetFieldValue : SetIntField : JNIFieldInfo is not jint type");
        }
    }

    void
    JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int64_t source) {
        if (!env || !info) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_LONG) {
            SetLongField(env, object, info, source);
        } else {
            JNI_LOGE("SetFieldValue : SetLongField : JNIFieldInfo is not jlong type");
        }
    }

    void
    JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, float source) {
        if (!env || !info) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
            SetFloatField(env, object, info, source);
        } else {
            JNI_LOGE("SetFieldValue : SetFloatField : JNIFieldInfo is not jfloat type");
        }
    }

    void
    JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, double source) {
        if (!env || !info) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE) {
            SetDoubleField(env, object, info, source);
        } else {
            JNI_LOGE("SetFieldValue : SetDoubleField : JNIFieldInfo is not jdouble type");
        }
    }

    void JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<uint8_t> *source) {
        if (!env || !info || !source) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN) {
            jbooleanArray arr = env->NewBooleanArray(source->size());
            ConvertJavaBoolArray(env, source, &arr);
            SetObjectField(env, object, info, arr);
            ClearException(env);
        } else {
            JNI_LOGE("SetFieldValue : JNIFieldInfo is not jbooleanArray type");
        }
    }

    void JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<int8_t> *source) {
        if (!env || !info || !source) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
            jbyteArray arr = env->NewByteArray(source->size());
            ConvertJavaByteArray(env, source, &arr);
            SetObjectField(env, object, info, arr);
            ClearException(env);
        } else {
            JNI_LOGE("SetFieldValue : JNIFieldInfo is not jbyteArray type");
        }
    }

    void JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<uint16_t> *source) {
        if (!env || !info || !source) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
            jcharArray arr = env->NewCharArray(source->size());
            ConvertJavaCharArray(env, source, &arr);
            SetObjectField(env, object, info, arr);
            ClearException(env);
        } else {
            JNI_LOGE("SetFieldValue : JNIFieldInfo is not jbyteArray type");
        }
    }

    void JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<int16_t> *source) {
        if (!env || !info || !source) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT) {
            jshortArray arr = env->NewShortArray(source->size());
            ConvertJavaShortArray(env, source, &arr);
            SetObjectField(env, object, info, arr);
            ClearException(env);
        } else {
            JNI_LOGE("SetFieldValue : JNIFieldInfo is not jshortArray type");
        }
    }

    void JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<int32_t> *source) {
        if (!env || !info || !source) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
            jintArray arr = env->NewIntArray(source->size());
            ConvertJavaIntArray(env, source, &arr);
            SetObjectField(env, object, info, arr);
            ClearException(env);
        } else {
            JNI_LOGE("SetFieldValue : JNIFieldInfo is not jintArray type");
        }
    }

    void JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<int64_t> *source) {
        if (!env || !info || !source) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_LONG) {
            jlongArray arr = env->NewLongArray(source->size());
            ConvertJavaLongArray(env, source, &arr);
            SetObjectField(env, object, info, arr);
            ClearException(env);
        } else {
            JNI_LOGE("SetFieldValue : JNIFieldInfo is not jlongArray type");
        }
    }

    void JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<float> *source) {
        if (!env || !info || !source) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
            jfloatArray arr = env->NewFloatArray(source->size());
            ConvertJavaFloatArray(env, source, &arr);
            SetObjectField(env, object, info, arr);
            ClearException(env);
        } else {
            JNI_LOGE("SetFieldValue : JNIFieldInfo is not jfloatArray type");
        }
    }

    void JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<double> *source) {
        if (!env || !info || !source) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
            jdoubleArray arr = env->NewDoubleArray(source->size());
            ConvertJavaDoubleArray(env, source, &arr);
            SetObjectField(env, object, info, arr);
            ClearException(env);
        } else {
            JNI_LOGE("SetFieldValue : JNIFieldInfo is not jdoubleArray type");
        }
    }

    void JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::string *source) {
        if (!env || !info || !source) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 0 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING) {
            if (!source->empty()) {
                jstring str;
                ConvertJavaString(env, source, &str);
                SetObjectField(env, object, info, str);
                ClearException(env);
            }
        } else {
            JNI_LOGE("SetFieldValue : JNIFieldInfo is not jstring type");
        }
    }

    void JNIUtils::SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                 std::vector<std::string> *source) {
        if (!env || !info || !source) {
            JNI_LOGD("SetFieldValue : param error");
            return;
        }
        if (!info->classID || !info->fieldId) {
            JNI_LOGD("SetFieldValue : classID || fieldId error");
            return;
        }
        MethodFlag type = GetReturnType(info->fieldInfo.flag);
        if (info->fieldInfo.arrayDimension == 1 &&
            type == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING) {
            jclass jstringClass = env->FindClass("java/lang/String");
            size_t size = source->size();
            if (size > 0) {
                jobjectArray strArr = env->NewObjectArray(size, jstringClass, NULL);
                for (size_t i = 0; i < size; ++i) {
                    jstring str;
                    ConvertJavaString(env, &(source->at(i)), &str);
                    env->SetObjectArrayElement(strArr, i, str);
                }
                env->SetObjectField(object, info->fieldId, strArr);
            }
        } else {
            JNI_LOGE("SetFieldValue : JNIFieldInfo is not jstringArray type");
        }
    }

    void
    JNIUtils::ExtractJavaBoolArray(JNIEnv *env, jbooleanArray source,
                                   std::vector<uint8_t> *result) {
        if (!env || !source || !result) {
            return;
        }
        jsize length = env->GetArrayLength(source);
        if (length < 1) {
            return;
        }
        jboolean isCopy = JNI_TRUE;
        jboolean *zArr = env->GetBooleanArrayElements(source, &isCopy);
        if (!zArr) {
            return;
        }
        for (int i = 0; i < length; i++) {
            result->push_back(*(zArr + i));
        }
        env->ReleaseBooleanArrayElements(source, zArr, 0);
    }

    void
    JNIUtils::ExtractJavaByteArray(JNIEnv *env, jbyteArray source, std::vector<int8_t> *result) {
        if (!env || !source) {
            return;
        }
        jsize length = env->GetArrayLength(source);
        if (length < 1) {
            return;
        }
        jboolean isCopy = JNI_TRUE;
        jbyte *bArr = env->GetByteArrayElements(source, &isCopy);
        if (!bArr) {
            return;
        }
        for (int i = 0; i < length; i++) {
            result->push_back(*(bArr + i));
        }
        env->ReleaseByteArrayElements(source, bArr, 0);
    }

    void
    JNIUtils::ExtractJavaCharArray(JNIEnv *env, jcharArray source, std::vector<uint16_t> *result) {
        if (!env || !source) {
            return;
        }
        jsize length = env->GetArrayLength(source);
        if (length < 1) {
            return;
        }
        jboolean isCopy = JNI_TRUE;
        jchar *cArr = env->GetCharArrayElements(source, &isCopy);
        if (!cArr) {
            return;
        }
        for (int i = 0; i < length; i++) {
            result->push_back(*(cArr + i));
        }
        env->ReleaseCharArrayElements(source, cArr, 0);
    }

    void
    JNIUtils::ExtractJavaShortArray(JNIEnv *env, jshortArray source, std::vector<int16_t> *result) {
        if (!env || !source || !result) {
            return;
        }
        jsize length = env->GetArrayLength(source);
        if (length < 1) {
            return;
        }
        jboolean isCopy = JNI_TRUE;
        jshort *sArr = env->GetShortArrayElements(source, &isCopy);
        if (!sArr) {
            return;
        }
        for (int i = 0; i < length; i++) {
            result->push_back(*(sArr + i));
        }
        env->ReleaseShortArrayElements(source, sArr, 0);
    }

    void
    JNIUtils::ExtractJavaIntArray(JNIEnv *env, jintArray source, std::vector<int32_t> *result) {
        if (!env || !source || !result) {
            return;
        }
        jsize length = env->GetArrayLength(source);
        if (length < 1) {
            return;
        }
        jboolean isCopy = JNI_TRUE;
        jint *iArr = env->GetIntArrayElements(source, &isCopy);
        if (!iArr) {
            return;
        }
        for (int i = 0; i < length; i++) {
            result->push_back(*(iArr + i));
        }
        env->ReleaseIntArrayElements(source, iArr, 0);
    }

    void
    JNIUtils::ExtractJavaLongArray(JNIEnv *env, jlongArray source, std::vector<int64_t> *result) {
        if (!env || !source || !result) {
            return;
        }
        jsize length = env->GetArrayLength(source);
        if (length < 1) {
            return;
        }
        jboolean isCopy = JNI_TRUE;
        jlong *jArr = env->GetLongArrayElements(source, &isCopy);
        if (!jArr) {
            return;
        }
        for (int i = 0; i < length; i++) {
            result->push_back(*(jArr + i));
        }
        env->ReleaseLongArrayElements(source, jArr, 0);
    }

    void
    JNIUtils::ExtractJavaFloatArray(JNIEnv *env, jfloatArray source, std::vector<float> *result) {
        if (!env || !source || !result) {
            return;
        }
        jsize length = env->GetArrayLength(source);
        if (length < 1) {
            return;
        }
        jboolean isCopy = JNI_TRUE;
        jfloat *fArr = env->GetFloatArrayElements(source, &isCopy);
        if (!fArr) {
            return;
        }
        for (int i = 0; i < length; i++) {
            result->push_back(*(fArr + i));
        }
        env->ReleaseFloatArrayElements(source, fArr, 0);
    }

    void JNIUtils::ExtractJavaDoubleArray(JNIEnv *env, jdoubleArray source,
                                          std::vector<double> *result) {
        if (!env || !source || !result) {
            return;
        }
        jsize length = env->GetArrayLength(source);
        if (length < 1) {
            return;
        }
        jboolean isCopy = JNI_TRUE;
        jdouble *dArr = env->GetDoubleArrayElements(source, &isCopy);
        if (!dArr) {
            return;
        }
        for (int i = 0; i < length; i++) {
            result->push_back(*(dArr + i));
        }
        env->ReleaseDoubleArrayElements(source, dArr, 0);
    }

    void
    JNIUtils::ExtractJavaString(JNIEnv *env, jstring source, std::string *result) {
        if (!env || !source || !result) {
            return;
        }

//        const char *str = env->GetStringUTFChars(source, JNI_FALSE);
//        result->operator=(str);
//        env->ReleaseStringUTFChars(source, str);

        const char *str = env->GetStringUTFChars(source, JNI_FALSE);
        if (str) {
            size_t length = std::strlen(str);
            char *tmp = new char[length + 1];
            memcpy(tmp, str, length);
            tmp[length] = 0;
            (*result) = tmp;
            delete[] tmp;
        }
        env->ReleaseStringUTFChars(source, str);
    }

    void JNIUtils::ExtractJavaString(JNIEnv *env, jstring source, char **result) {
        if (!env || !source || !result) {
            return;
        }
        const char *str = env->GetStringUTFChars(source, JNI_FALSE);
        if (str) {
            size_t length = std::strlen(str);
            (*result) = new char[length + 1];
            memcpy(*result, str, length);
            (*result)[length] = 0;
        }
        env->ReleaseStringUTFChars(source, str);
    }

    void JNIUtils::ExtractJavaStringArray(JNIEnv *env, jobjectArray source,
                                          std::vector<std::string> *result) {
        if (!env || !source || !result) {
            return;
        }
        int length = env->GetArrayLength(source);
        if (length < 1) {
            return;
        }
        for (int i = 0; i < length; i++) {
            auto j_str = (jstring) env->GetObjectArrayElement(source, i);
            if (j_str) {
                char *c_str = nullptr;
                ExtractJavaString(env, j_str, &c_str);
                result->emplace_back(c_str);
                env->DeleteLocalRef(j_str);
            }
        }
    }

    void JNIUtils::ConvertJavaBoolArray(JNIEnv *env, std::vector<uint8_t> *source,
                                        jbooleanArray *result) {
        if (!env || !source || !result) {
            return;
        }
        size_t size = source->size();
        if (size > 0) {
            jboolean buff[size];
            for (size_t i = 0; i < size; ++i) {
                buff[i] = source->at(i);
            }
            env->SetBooleanArrayRegion(*result, 0, (int) size, buff);
        }
    }

    void
    JNIUtils::ConvertJavaByteArray(JNIEnv *env, std::vector<int8_t> *source, jbyteArray *result) {
        if (!env || !source || !result) {
            return;
        }
        size_t size = source->size();
        if (size > 0) {
            jbyte buff[size];
            for (size_t i = 0; i < size; ++i) {
                buff[i] = source->at(i);
            }
            env->SetByteArrayRegion(*result, 0, (int) size, buff);
        }
    }

    void
    JNIUtils::ConvertJavaCharArray(JNIEnv *env, std::vector<uint16_t> *source, jcharArray *result) {
        if (!env || !source || !result) {
            return;
        }
        size_t size = source->size();
        if (size > 0) {
            jchar buff[size];
            for (size_t i = 0; i < size; ++i) {
                buff[i] = source->at(i);
            }
            env->SetCharArrayRegion(*result, 0, (int) size, buff);
        }
    }

    void JNIUtils::ConvertJavaShortArray(JNIEnv *env, std::vector<int16_t> *source,
                                         jshortArray *result) {
        if (!env || !source || !result) {
            return;
        }
        size_t size = source->size();
        if (size > 0) {
            jshort buff[size];
            for (size_t i = 0; i < size; ++i) {
                buff[i] = source->at(i);
            }
            env->SetShortArrayRegion(*result, 0, (int) size, buff);
        }
    }

    void
    JNIUtils::ConvertJavaIntArray(JNIEnv *env, std::vector<int32_t> *source, jintArray *result) {
        if (!env || !source || !result) {
            return;
        }
        size_t size = source->size();
        if (size > 0) {
            jint buff[size];
            for (size_t i = 0; i < size; ++i) {
                buff[i] = source->at(i);
            }
            env->SetIntArrayRegion(*result, 0, (int) size, buff);
        }
    }

    void
    JNIUtils::ConvertJavaLongArray(JNIEnv *env, std::vector<int64_t> *source, jlongArray *result) {
        if (!env || !source || !result) {
            return;
        }
        size_t size = source->size();
        if (size > 0) {
            jlong buff[size];
            for (size_t i = 0; i < size; ++i) {
                buff[i] = source->at(i);
            }
            env->SetLongArrayRegion(*result, 0, (int) size, buff);
        }
    }

    void
    JNIUtils::ConvertJavaFloatArray(JNIEnv *env, std::vector<float> *source, jfloatArray *result) {
        if (!env || !source || !result) {
            return;
        }
        size_t size = source->size();
        if (size > 0) {
            jfloat buff[size];
            for (size_t i = 0; i < size; ++i) {
                buff[i] = source->at(i);
            }
            env->SetFloatArrayRegion(*result, 0, (int) size, buff);
        }
    }

    void JNIUtils::ConvertJavaDoubleArray(JNIEnv *env, std::vector<double> *source,
                                          jdoubleArray *result) {
        if (!env || !source || !result) {
            return;
        }
        size_t size = source->size();
        if (size > 0) {
            jdouble buff[size];
            for (size_t i = 0; i < size; ++i) {
                buff[i] = source->at(i);
            }
            env->SetDoubleArrayRegion(*result, 0, (int) size, buff);
        }
    }

    void
    JNIUtils::ConvertJavaString(JNIEnv *env, std::string *source, jstring *result) {
        if (!env || !source || !result) {
            return;
        }
        jclass strClass = env->FindClass("java/lang/String");
        jmethodID init = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
        const char *str = source->c_str();
        jbyteArray bytes = env->NewByteArray((jsize) strlen(str));
        env->SetByteArrayRegion(bytes, 0, (jsize) strlen(str), (jbyte *) str);
        jstring encoding = env->NewStringUTF("GB2312");
        (*result) = (jstring) env->NewObject(strClass, init, bytes, encoding);
    }

    void
    JNIUtils::ConvertJavaString(JNIEnv *env, const char *source, jstring *result) {
        if (!env || !source || !result) {
            return;
        }
        jclass strClass = env->FindClass("java/lang/String");
        jmethodID init = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
        jbyteArray bytes = env->NewByteArray((jsize) strlen(source));
        env->SetByteArrayRegion(bytes, 0, (jsize) strlen(source), (jbyte *) source);
        jstring encoding = env->NewStringUTF("GB2312");
        (*result) = (jstring) env->NewObject(strClass, init, bytes, encoding);
    }

    void
    JNIUtils::ConvertJavaStringArray(JNIEnv *env, std::vector<std::string> *source,
                                     jobjectArray *result) {
        if (!env || !source || !result) {
            return;
        }
        size_t size = source->size();
        if (size > 0) {
            for (size_t i = 0; i < size; ++i) {
                jstring jStr = env->NewStringUTF(source->at(i).c_str());
                env->SetObjectArrayElement(*result, i, jStr);
            }
        }
    }

    jobject
    JNIUtils::CallJavaObjectMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                   jobject object, jvalue *param) {
        jobject ret = nullptr;
        if (IsStatic(methodInfo->returnObject.flag)) {
            ret = env->CallStaticObjectMethodA(methodInfo->classID, methodInfo->methodID, param);
            ClearException(env);
        } else {
            if (object) {
                if (IsNonvirtual(methodInfo->returnObject.flag)) {
                    ret = env->CallNonvirtualObjectMethodA(object, methodInfo->classID,
                                                           methodInfo->methodID, param);
                } else {
                    ret = env->CallObjectMethodA(object, methodInfo->methodID, param);
                }
                ClearException(env);
            } else {
                JNI_LOGD("CallJavaObjectMethod : object is null");
            }
        }
        return ret;
    }

    jboolean
    JNIUtils::CallJavaBooleanMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                    jobject object, jvalue *param) {
        jboolean ret = JNI_FALSE;
        if (IsStatic(methodInfo->returnObject.flag)) {
            ret = env->CallStaticBooleanMethodA(methodInfo->classID, methodInfo->methodID, param);
            ClearException(env);
        } else {
            if (object) {
                if (IsNonvirtual(methodInfo->returnObject.flag)) {
                    ret = env->CallNonvirtualBooleanMethodA(object, methodInfo->classID,
                                                            methodInfo->methodID, param);
                } else {
                    ret = env->CallBooleanMethodA(object, methodInfo->methodID, param);
                }
                ClearException(env);
            } else {
                JNI_LOGD("CallJavaBooleanMethod : object is null");
            }
        }
        return ret;
    }

    jbyte
    JNIUtils::CallJavaByteMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                 jobject object, jvalue *param) {
        jbyte ret = 0;
        if (IsStatic(methodInfo->returnObject.flag)) {
            ret = env->CallStaticByteMethodA(methodInfo->classID, methodInfo->methodID, param);
            ClearException(env);
        } else {
            if (object) {
                if (IsNonvirtual(methodInfo->returnObject.flag)) {
                    ret = env->CallNonvirtualByteMethodA(object, methodInfo->classID,
                                                         methodInfo->methodID, param);
                } else {
                    ret = env->CallByteMethodA(object, methodInfo->methodID, param);
                }
                ClearException(env);
            } else {
                JNI_LOGD("CallJavaByteMethod : object is null");
            }
        }
        return ret;
    }

    jchar
    JNIUtils::CallJavaCharMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                 jobject object, jvalue *param) {
        jchar ret = 0;
        if (IsStatic(methodInfo->returnObject.flag)) {
            ret = env->CallStaticCharMethodA(methodInfo->classID, methodInfo->methodID, param);
            ClearException(env);
        } else {
            if (object) {
                if (IsNonvirtual(methodInfo->returnObject.flag)) {
                    ret = env->CallNonvirtualCharMethodA(object, methodInfo->classID,
                                                         methodInfo->methodID, param);
                } else {
                    ret = env->CallCharMethodA(object, methodInfo->methodID, param);
                }
                ClearException(env);
            } else {
                JNI_LOGD("CallJavaCharMethod : object is null");
            }
        }
        return ret;
    }

    jshort
    JNIUtils::CallJavaShortMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                  jobject object, jvalue *param) {
        jshort ret = 0;
        if (IsStatic(methodInfo->returnObject.flag)) {
            ret = env->CallStaticShortMethodA(methodInfo->classID, methodInfo->methodID, param);
            ClearException(env);
        } else {
            if (object) {
                if (IsNonvirtual(methodInfo->returnObject.flag)) {
                    ret = env->CallNonvirtualShortMethodA(object, methodInfo->classID,
                                                          methodInfo->methodID, param);
                } else {
                    ret = env->CallShortMethodA(object, methodInfo->methodID, param);
                }
                ClearException(env);
            } else {
                JNI_LOGD("CallJavaShortMethod : object is null");
            }
        }
        return ret;
    }

    jint
    JNIUtils::CallJavaIntMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                jobject object, jvalue *param) {
        jint ret = 0;
        if (IsStatic(methodInfo->returnObject.flag)) {
            ret = env->CallStaticIntMethodA(methodInfo->classID, methodInfo->methodID, param);
            ClearException(env);
        } else {
            if (object) {
                if (IsNonvirtual(methodInfo->returnObject.flag)) {
                    ret = env->CallNonvirtualIntMethodA(object, methodInfo->classID,
                                                        methodInfo->methodID, param);
                } else {
                    ret = env->CallIntMethodA(object, methodInfo->methodID, param);
                }
                ClearException(env);
            } else {
                JNI_LOGD("CallJavaIntMethod : object is null");
            }
        }
        return ret;
    }

    jlong
    JNIUtils::CallJavaLongMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                 jobject object, jvalue *param) {
        jlong ret = 0;
        if (IsStatic(methodInfo->returnObject.flag)) {
            ret = env->CallStaticLongMethodA(methodInfo->classID, methodInfo->methodID, param);
            ClearException(env);
        } else {
            if (object) {
                if (IsNonvirtual(methodInfo->returnObject.flag)) {
                    ret = env->CallNonvirtualLongMethodA(object, methodInfo->classID,
                                                         methodInfo->methodID, param);
                } else {
                    ret = env->CallLongMethodA(object, methodInfo->methodID, param);
                }
                ClearException(env);
            } else {
                JNI_LOGD("CallJavaLongMethod : object is null");
            }
        }
        return ret;
    }

    jfloat
    JNIUtils::CallJavaFloatMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                  jobject object, jvalue *param) {
        jfloat ret = 0;
        if (IsStatic(methodInfo->returnObject.flag)) {
            ret = env->CallStaticFloatMethodA(methodInfo->classID, methodInfo->methodID, param);
            ClearException(env);
        } else {
            if (object) {
                if (IsNonvirtual(methodInfo->returnObject.flag)) {
                    ret = env->CallNonvirtualFloatMethodA(object, methodInfo->classID,
                                                          methodInfo->methodID, param);
                } else {
                    ret = env->CallFloatMethodA(object, methodInfo->methodID, param);
                }
                ClearException(env);
            } else {
                JNI_LOGD("CallJavaFloatMethod : object is null");
            }
        }
        return ret;
    }

    jdouble
    JNIUtils::CallJavaDoubleMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                   jobject object, jvalue *param) {
        jdouble ret = 0;
        if (IsStatic(methodInfo->returnObject.flag)) {
            ret = env->CallStaticDoubleMethodA(methodInfo->classID, methodInfo->methodID, param);
            ClearException(env);
        } else {
            if (object) {
                if (IsNonvirtual(methodInfo->returnObject.flag)) {
                    ret = env->CallNonvirtualDoubleMethodA(object, methodInfo->classID,
                                                           methodInfo->methodID, param);
                } else {
                    ret = env->CallDoubleMethodA(object, methodInfo->methodID, param);
                }
                ClearException(env);
            } else {
                JNI_LOGD("CallJavaDoubleMethod : object is null");
            }
        }
        return ret;
    }

    void
    JNIUtils::CallJavaVoidMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                 jobject object, jvalue *param) {
        if (IsStatic(methodInfo->returnObject.flag)) {
            env->CallStaticVoidMethodA(methodInfo->classID, methodInfo->methodID, param);
            ClearException(env);
        } else {
            if (object) {
                if (IsNonvirtual(methodInfo->returnObject.flag)) {
                    env->CallNonvirtualVoidMethodA(object, methodInfo->classID,
                                                   methodInfo->methodID, param);
                } else {
                    env->CallVoidMethodA(object, methodInfo->methodID, param);
                }
                ClearException(env);
            } else {
                JNI_LOGD("CallJavaVoidMethod : object is null");
            }
        }
    }
}