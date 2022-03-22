//
// Created by guobin on 2022/2/28.
//

#include "js_call_android_jni.h"

#include <fstream>
#include <iostream>

#include "jni_log.h"

namespace OHOS {
namespace TEMPLATE {

JSCallAndroidJni::JSCallAndroidJni() { JNI_LOGI("instance is created"); }

JSCallAndroidJni::~JSCallAndroidJni() {
    JNI_LOGI("instance is destroyed");
    Jkit jkit;
    if (jkit.IsValidEnv()) {
        JNIEnv *env = jkit.operator->();
        for (const auto &jclassID : jclassIDs) {
            if (jclassID.second != nullptr) {
                env->DeleteGlobalRef(jclassID.second);
            }
        }
    }
}

void JSCallAndroidJni::InitJavaVm(JavaVM *vm) {
    JNI_LOGI("InitJavaVm: begin");
    OHOS::Jkit::nativeInit(vm);
    JNI_LOGI("InitJavaVm: end");
}

void JSCallAndroidJni::NativeInit(JNIEnv *env, const std::string &config) {
    JNI_LOGI("NativeInit: begin");
    nlohmann::json jsonObject;
    std::ifstream jsonFile(
        "/sdcard/Android/data/com.pandon.javaapi.testannotation/files/" +
        config);
    jsonFile >> jsonObject;
    from_json(jsonObject, jniInfo);
    if (!jniInfo.classes.empty()) {
        for (auto &classInfo : jniInfo.classes) {
            JNI_LOGI("NativeInit: class : %" LIMIT "s",
                     classInfo.className.c_str());
            auto clazzRet = env->FindClass(classInfo.className.c_str());
            if (!clazzRet) {
                JNI_LOGE("NativeInit : class(%" LIMIT "s) is not exist",
                         classInfo.className.c_str());
                continue;
            }
            auto clazz = (jclass)env->NewGlobalRef(clazzRet);
            jclassIDs.insert(
                std::pair<std::string, jclass>(classInfo.className, clazz));
            if (!classInfo.methods.empty()) {
                for (auto &methodInfo : classInfo.methods) {
                    jmethodID methodID;
                    if (IsStatic(methodInfo.returnObject.flag)) {
                        methodID = env->GetStaticMethodID(
                            clazz, methodInfo.name.c_str(),
                            methodInfo.sign.c_str());
                    } else {
                        methodID =
                            env->GetMethodID(clazz, methodInfo.name.c_str(),
                                             methodInfo.sign.c_str());
                    }
                    if (!methodID) {
                        JNI_LOGE("NativeInit: method %" LIMIT "s(sign: %" LIMIT
                                 "s, id = %" LIMIT "d) is not exist",
                                 methodInfo.name.c_str(),
                                 methodInfo.sign.c_str(), methodInfo.id);
                        JNIUtils::ClearException(env);
                        continue;
                    }
                    jniMethodInfos.insert(std::pair<int32_t, JNIMethodInfo>(
                        methodInfo.id, JNIMethodInfo(methodID, clazz,
                                                     methodInfo.returnObject)));
                }
            }
            if (!classInfo.fields.empty()) {
                for (auto &fieldInfo : classInfo.fields) {
                    jfieldID fieldId;
                    if (IsStatic(fieldInfo.flag)) {
                        fieldId =
                            env->GetStaticFieldID(clazz, fieldInfo.name.c_str(),
                                                  fieldInfo.sign.c_str());
                    } else {
                        fieldId = env->GetFieldID(clazz, fieldInfo.name.c_str(),
                                                  fieldInfo.sign.c_str());
                    }
                    if (!fieldId) {
                        JNI_LOGE("NativeInit: field %" LIMIT "s(sign: %" LIMIT
                                 "s, id = %" LIMIT "d) is not exist",
                                 fieldInfo.name.c_str(), fieldInfo.sign.c_str(),
                                 fieldInfo.id);
                        JNIUtils::ClearException(env);
                        continue;
                    }
                    jniFieldInfos.insert(std::pair<int32_t, JNIFieldInfo>(
                        fieldInfo.id, JNIFieldInfo(fieldId, clazz, fieldInfo)));
                }
            }
        }
    } else {
        JNI_LOGE("NativeInit: jniInfo is empty");
    }
    JNI_LOGI("NativeInit: end");
}

int JSCallAndroidJni::GetJNIMethodInfo(int32_t methodID,
                                       JNIMethodInfo *methodInfo) {
    if (jniMethodInfos.count(methodID) > 0) {
        (*methodInfo) = jniMethodInfos.at(methodID);
        if (methodInfo->classID && methodInfo->methodID) {
            return JNI_OK;
        }
    }
    JNI_LOGE("GetJNIMethodInfo: methodID(%" LIMIT "d) is not init", methodID);
    return JNI_ERR;
}

int JSCallAndroidJni::GetJNIFieldInfo(int32_t fieldID,
                                      JNIFieldInfo *fieldInfo) {
    if (jniFieldInfos.count(fieldID) > 0) {
        (*fieldInfo) = jniFieldInfos.at(fieldID);
        if (fieldInfo->classID && fieldInfo->fieldId) {
            return JNI_OK;
        }
    }
    JNI_LOGE("GetJNIFieldInfo: fieldID(%" LIMIT "d) is not init", fieldID);
    return JNI_ERR;
}

void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object,
                                      jvalue *param) {
    JNI_LOGI("CallJavaMethod(Void): begin.");
    JNIMethodInfo methodInfo;
    if (GetJNIMethodInfo(methodID, &methodInfo) != JNI_OK) {
        return;
    }
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(Void): returnType: %" LIMIT "d", returnType);
    if (returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_VOID) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Void): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::CallJavaVoidMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Void): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(Boolean): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 0 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Boolean): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            JNIUtils::CallJavaBooleanMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Boolean): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(Byte): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 0 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Byte): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            JNIUtils::CallJavaByteMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Byte): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(Char): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 0 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Char): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            JNIUtils::CallJavaCharMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Char): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(Short): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 0 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Short): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            JNIUtils::CallJavaShortMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Short): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(Int): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 0 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Int): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            JNIUtils::CallJavaIntMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Int): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(Long): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 0 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_LONG) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Long): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            JNIUtils::CallJavaLongMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Long): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(Float): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 0 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Float): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            JNIUtils::CallJavaFloatMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Float): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(Double): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 0 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(Double): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*result) =
            JNIUtils::CallJavaDoubleMethod(env, &methodInfo, object, param);
    } else {
        JNI_LOGE(
            "CallJavaMethod(Double): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(BooleanArray): returnType: %" LIMIT "d",
             returnType);
    if (methodInfo.returnObject.arrayDimension == 1 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(BooleanArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::CallJavaBooleanArrayMethod(env, &methodInfo, object, param,
                                             result);
    } else {
        JNI_LOGE(
            "CallJavaMethod(BooleanArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(ByteArray): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 1 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(ByteArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::CallJavaByteArrayMethod(env, &methodInfo, object, param,
                                          result);
    } else {
        JNI_LOGE(
            "CallJavaMethod(ByteArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(CharArray): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 1 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(CharArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::CallJavaCharArrayMethod(env, &methodInfo, object, param,
                                          result);
    } else {
        JNI_LOGE(
            "CallJavaMethod(CharArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(ShortArray): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 1 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(ShortArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::CallJavaShortArrayMethod(env, &methodInfo, object, param,
                                           result);
    } else {
        JNI_LOGE(
            "CallJavaMethod(ShortArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(IntArray): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 1 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(IntArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::CallJavaIntArrayMethod(env, &methodInfo, object, param,
                                         result);
    } else {
        JNI_LOGE(
            "CallJavaMethod(IntArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(LongArray): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 1 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_LONG) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(LongArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::CallJavaLongArrayMethod(env, &methodInfo, object, param,
                                          result);
    } else {
        JNI_LOGE(
            "CallJavaMethod(LongArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(FloatArray): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 1 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(FloatArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::CallJavaFloatArrayMethod(env, &methodInfo, object, param,
                                           result);
    } else {
        JNI_LOGE(
            "CallJavaMethod(FloatArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(DoubleArray): returnType: %" LIMIT "d",
             returnType);
    if (methodInfo.returnObject.arrayDimension == 1 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(DoubleArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::CallJavaDoubleArrayMethod(env, &methodInfo, object, param,
                                            result);
    } else {
        JNI_LOGE(
            "CallJavaMethod(DoubleArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(String): returnType: %" LIMIT "d", returnType);
    if (methodInfo.returnObject.arrayDimension == 0 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(String): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::CallJavaStringMethod(env, &methodInfo, object, param, result);
    } else {
        JNI_LOGE(
            "CallJavaMethod(String): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
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
    MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
    JNI_LOGI("CallJavaMethod(StringArray): returnType: %" LIMIT "d",
             returnType);
    if (methodInfo.returnObject.arrayDimension == 1 &&
        returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod(StringArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::CallJavaStringArrayMethod(env, &methodInfo, object, param,
                                            result);
    } else {
        JNI_LOGE(
            "CallJavaMethod(StringArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            methodInfo.returnObject.arrayDimension, (int32_t)returnType);
    }
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     uint8_t *target) {
    JNI_LOGI("GetFieldValue(boolean): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(boolean) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(boolean): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = JNIUtils::GetBooleanField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(boolean): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(boolean): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     int8_t *target) {
    JNI_LOGI("GetFieldValue(byte): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(byte) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(byte): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = JNIUtils::GetByteField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(byte): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(byte): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     uint16_t *target) {
    JNI_LOGI("GetFieldValue(char): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(char) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(char): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = JNIUtils::GetCharField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(char): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(char): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     int16_t *target) {
    JNI_LOGI("GetFieldValue(short): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(short) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(short): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = JNIUtils::GetShortField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(short): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(short): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     int32_t *target) {
    JNI_LOGI("GetFieldValue(int): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(int) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(int): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = JNIUtils::GetIntField(env, object, &info);
    } else {
        JNI_LOGE("GetFieldValue(int): Type Err, current(arrayDimension: %" LIMIT
                 "d, type: %" LIMIT "d)",
                 info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(int): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     int64_t *target) {
    JNI_LOGI("GetFieldValue(long): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(long) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_LONG) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(long): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = JNIUtils::GetLongField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(long): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(long): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     float *target) {
    JNI_LOGI("GetFieldValue(float): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(float) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(float): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = JNIUtils::GetFloatField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(float): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(float): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     double *target) {
    JNI_LOGI("GetFieldValue(double): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(double) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(double): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        (*target) = JNIUtils::GetDoubleField(env, object, &info);
    } else {
        JNI_LOGE(
            "GetFieldValue(double): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(double): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::string *target) {
    JNI_LOGI("GetFieldValue(String): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(String) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(String): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::GetStringField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(String): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(String): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<uint8_t> *target) {
    JNI_LOGI("GetFieldValue(BooleanArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(BooleanArray) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(BooleanArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::GetBooleanArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(BooleanArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(BooleanArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int8_t> *target) {
    JNI_LOGI("GetFieldValue(ByteArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(ByteArray) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(ByteArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::GetByteArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(ByteArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(ByteArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<uint16_t> *target) {
    JNI_LOGI("GetFieldValue(CharArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(CharArray) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(CharArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::GetCharArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(CharArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(CharArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int16_t> *target) {
    JNI_LOGI("GetFieldValue(ShortArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(ShortArray) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(ShortArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::GetShortArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(ShortArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(ShortArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int32_t> *target) {
    JNI_LOGI("GetFieldValue(IntArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(IntArray) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(IntArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::GetIntArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(IntArray): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(IntArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int64_t> *target) {
    JNI_LOGI("GetFieldValue(LongArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(LongArray) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_LONG) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(LongArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::GetLongArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(LongArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(LongArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<float> *target) {
    JNI_LOGI("GetFieldValue(FloatArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(FloatArray) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(FloatArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::GetFloatArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(FloatArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(FloatArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<double> *target) {
    JNI_LOGI("GetFieldValue(DoubleArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(DoubleArray) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(DoubleArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::GetDoubleArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(DoubleArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(DoubleArray): end");
}

void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<std::string> *target) {
    JNI_LOGI("GetFieldValue(StringArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !target) {
        JNI_LOGE("GetFieldValue(StringArray) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("GetFieldValue(StringArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::GetStringArrayField(env, object, &info, target);
    } else {
        JNI_LOGE(
            "GetFieldValue(StringArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("GetFieldValue(StringArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     uint8_t *source) {
    JNI_LOGI("SetFieldValue(boolean): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(boolean) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(boolean): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetBooleanField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(boolean): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(boolean): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     int8_t *source) {
    JNI_LOGI("SetFieldValue(byte): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(byte) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(byte): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetByteField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(byte): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(byte): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     uint16_t *source) {
    JNI_LOGI("SetFieldValue(char): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(char) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(char): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetCharField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(char): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(char): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     int16_t *source) {
    JNI_LOGI("SetFieldValue(short): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(short) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(short): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetShortField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(short): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(short): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     int32_t *source) {
    JNI_LOGI("SetFieldValue(int): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(int) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(int): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetIntField(env, object, &info, *source);
    } else {
        JNI_LOGE("SetFieldValue(int): Type Err, current(arrayDimension: %" LIMIT
                 "d, type: %" LIMIT "d)",
                 info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(int): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     int64_t *source) {
    JNI_LOGI("SetFieldValue(long): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(long) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_LONG) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(long): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetLongField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(long): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(long): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     float *source) {
    JNI_LOGI("SetFieldValue(float): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(float) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(float): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetFloatField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(float): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(float): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     double *source) {
    JNI_LOGI("SetFieldValue(double): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(double) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(double): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetDoubleField(env, object, &info, *source);
    } else {
        JNI_LOGE(
            "SetFieldValue(double): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(double): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::string *source) {
    JNI_LOGI("SetFieldValue(String): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(String) : param error");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 0 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(String): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetStringField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(String): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(String): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<uint8_t> *source) {
    JNI_LOGI("SetFieldValue(BooleanArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(BooleanArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(BooleanArray) : source is empty");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(BooleanArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetBooleanArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(BooleanArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(BooleanArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int8_t> *source) {
    JNI_LOGI("SetFieldValue(ByteArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(ByteArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(ByteArray) : source is empty");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(ByteArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetByteArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(ByteArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(ByteArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<uint16_t> *source) {
    JNI_LOGI("SetFieldValue(CharArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(CharArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(CharArray) : source is empty");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(CharArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetCharArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(CharArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(CharArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int16_t> *source) {
    JNI_LOGI("SetFieldValue(ShortArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(ShortArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(ShortArray) : source is empty");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(ShortArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetShortArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(ShortArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(ShortArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int32_t> *source) {
    JNI_LOGI("SetFieldValue(IntArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(IntArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(IntArray) : source is empty");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(IntArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetIntArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(IntArray): Type Err, current(arrayDimension: %" LIMIT
            "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(IntArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<int64_t> *source) {
    JNI_LOGI("SetFieldValue(LongArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(LongArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(LongArray) : source is empty");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_LONG) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(LongArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetLongArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(LongArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(LongArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<float> *source) {
    JNI_LOGI("SetFieldValue(FloatArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(FloatArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(FloatArray) : source is empty");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(FloatArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetFloatArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(FloatArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(FloatArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<double> *source) {
    JNI_LOGI("SetFieldValue(DoubleArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(DoubleArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(DoubleArray) : source is empty");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(DoubleArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetDoubleArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(DoubleArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
    }
    JNI_LOGI("SetFieldValue(DoubleArray): end");
}

void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                     std::vector<std::string> *source) {
    JNI_LOGI("SetFieldValue(StringArray): begin(%" LIMIT "d)", fieldID);
    JNIFieldInfo info;
    if (GetJNIFieldInfo(fieldID, &info) != JNI_OK) {
        return;
    }
    if (!info.classID || !info.fieldId || !object || !source) {
        JNI_LOGE("SetFieldValue(StringArray) : param error");
        return;
    }
    if (source->size() == 0) {
        JNI_LOGW("SetFieldValue(StringArray) : source is empty");
        return;
    }
    MethodFlag type = GetReturnType(info.fieldInfo.flag);
    if (info.fieldInfo.arrayDimension == 1 &&
        type == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING) {
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue(StringArray): env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIUtils::SetStringArrayField(env, object, &info, source);
    } else {
        JNI_LOGE(
            "SetFieldValue(StringArray): Type Err, current(arrayDimension: "
            "%" LIMIT "d, type: %" LIMIT "d)",
            info.fieldInfo.arrayDimension, (int32_t)type);
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

jobject JSCallAndroidJni::NewObject(std::string className) {
    jobject result = nullptr;
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("NewObject: env is null.");
        return result;
    }
    JNIEnv *env = jkit.operator->();
    if (env) {
        jobject ret = NewObject(env, &className);
        if (ret) {
            result = env->NewGlobalRef(ret);
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

jobject JSCallAndroidJni::NewObject(JNIEnv *env, std::string *className) {
    jobject result = nullptr;
    if (className && !className->empty()) {
        jclass targetClass = jclassIDs.at(*className);
        jmethodID init = env->GetMethodID(targetClass, "<init>", "()V");
        result = env->NewObject(targetClass, init);
    } else {
        JNI_LOGE("NewObject : className is null or empty");
    }
    return result;
}

void JSCallAndroidJni::ExtractJavaBoolArray(jbooleanArray source,
                                            std::vector<uint8_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ExtractJavaBoolArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaByteArray(jbyteArray source,
                                            std::vector<int8_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ExtractJavaByteArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaCharArray(jcharArray source,
                                            std::vector<uint16_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ExtractJavaCharArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaShortArray(jshortArray source,
                                             std::vector<int16_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ExtractJavaShortArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaIntArray(jintArray source,
                                           std::vector<int32_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ExtractJavaIntArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaLongArray(jlongArray source,
                                            std::vector<int64_t> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ExtractJavaLongArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaFloatArray(jfloatArray source,
                                             std::vector<float> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ExtractJavaFloatArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaDoubleArray(jdoubleArray source,
                                              std::vector<double> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ExtractJavaDoubleArray(env, source, result);
}

void JSCallAndroidJni::ExtractJavaString(jstring source, std::string *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ExtractJavaString(env, source, result);
}

void JSCallAndroidJni::ExtractJavaString(jstring source, char **result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ExtractJavaString(env, source, result);
}

void JSCallAndroidJni::ExtractJavaStringArray(
    jobjectArray source, std::vector<std::string> *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ExtractJavaStringArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaBoolArray(std::vector<uint8_t> *source,
                                            jbooleanArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaBoolArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaByteArray(std::vector<int8_t> *source,
                                            jbyteArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaByteArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaCharArray(std::vector<uint16_t> *source,
                                            jcharArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaCharArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaShortArray(std::vector<int16_t> *source,
                                             jshortArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaShortArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaIntArray(std::vector<int32_t> *source,
                                           jintArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaIntArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaLongArray(std::vector<int64_t> *source,
                                            jlongArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaLongArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaFloatArray(std::vector<float> *source,
                                             jfloatArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaFloatArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaDoubleArray(std::vector<double> *source,
                                              jdoubleArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaDoubleArray(env, source, result);
}

void JSCallAndroidJni::ConvertJavaString(std::string *source, jstring *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaString(env, source, result);
}

void JSCallAndroidJni::ConvertJavaString(std::string const *source,
                                         jstring *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaString(env, source, result);
}

void JSCallAndroidJni::ConvertJavaString(const char *source, jstring *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaString(env, source, result);
}

void JSCallAndroidJni::ConvertJavaStringArray(std::vector<std::string> *source,
                                              jobjectArray *result) {
    Jkit jkit;
    if ((jkit.IsValidEnv() & 1) == 0) {
        JNI_LOGE("GetFieldValue: env is null.");
        return;
    }
    JNIEnv *env = jkit.operator->();
    JNIUtils::ConvertJavaStringArray(env, source, result);
}
}  // namespace TEMPLATE
}  // namespace OHOS
