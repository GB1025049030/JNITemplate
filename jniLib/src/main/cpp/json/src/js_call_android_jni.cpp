//
// Created by guobin on 2022/2/28.
//

#include "js_call_android_jni.h"
#include "jni_log.h"
#include <iostream>
#include <fstream>

namespace OHOS {
    JSCallAndroidJni::JSCallAndroidJni() {
        JNI_LOGI("instance is created");
    }

    JSCallAndroidJni::~JSCallAndroidJni() {
        JNI_LOGI("instance is destroyed");
        Jkit jkit;
        if (jkit.IsValidEnv()) {
            JNIEnv *env = jkit.operator->();
            for (auto jclassID : jclassIDs) {
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

    void JSCallAndroidJni::NativeInit(JNIEnv *env, std::string config) {
        JNI_LOGI("NativeInit: begin");
        nlohmann::json jsonObject;
        std::string s = "ohos_bundlemgr.json";
        std::ifstream jsonFile(
                "/sdcard/Android/data/com.pandon.javaapi.testannotation/files/Documents/" + config);
        jsonFile >> jsonObject;
        from_json(jsonObject, jniInfo);
        if (!jniInfo.classes.empty()) {
            for (auto &classInfo : jniInfo.classes) {
                JNI_LOGI("NativeInit: class : %" LIMIT "s", classInfo.className.c_str());
                auto clazzRet = env->FindClass(classInfo.className.c_str());
                if (!clazzRet) {
                    JNI_LOGE("NativeInit : class(%" LIMIT "s) is not exist",
                             classInfo.className.c_str());
                    continue;
                }
                auto clazz = (jclass) env->NewGlobalRef(clazzRet);
                jclassIDs.insert(std::pair<std::string, jclass>(classInfo.className, clazz));
                if (!classInfo.methods.empty()) {
                    for (auto &methodInfo : classInfo.methods) {
                        JNI_LOGI("NativeInit: method name: %" LIMIT "s", methodInfo.name.c_str());
                        jmethodID methodID;
                        if (IsStatic(methodInfo.returnObject.flag)) {
                            methodID = env->GetStaticMethodID(
                                    clazz,
                                    methodInfo.name.c_str(),
                                    methodInfo.sign.c_str()
                            );
                        } else {
                            methodID = env->GetMethodID(
                                    clazz,
                                    methodInfo.name.c_str(),
                                    methodInfo.sign.c_str()
                            );
                        }
                        if (!methodID) {
                            JNI_LOGE("NativeInit: method %" LIMIT "s is not exist",
                                     methodInfo.name.c_str());
                            JNIUtils::ClearException(env);
                            continue;
                        }
                        jniMethodInfos.insert(
                                std::pair<int32_t, JNIMethodInfo>(methodInfo.id,
                                                                  JNIMethodInfo(methodID, clazz,
                                                                                methodInfo.returnObject))
                        );
                    }
                }
                if (!classInfo.fields.empty()) {
                    for (auto &fieldInfo : classInfo.fields) {
                        JNI_LOGI("NativeInit: field name: %" LIMIT "s", fieldInfo.name.c_str());
                        jfieldID fieldId;
                        if (IsStatic(fieldInfo.flag)) {
                            fieldId = env->GetStaticFieldID(clazz, fieldInfo.name.c_str(),
                                                            fieldInfo.sign.c_str());
                        } else {
                            fieldId = env->GetFieldID(clazz, fieldInfo.name.c_str(),
                                                      fieldInfo.sign.c_str());
                        }
                        if (!fieldId) {
                            JNI_LOGE("NativeInit: field %" LIMIT "s is not exist",
                                     fieldInfo.name.c_str());
                            JNIUtils::ClearException(env);
                            continue;
                        }
                        jniFieldInfos.insert(std::pair<int32_t, JNIFieldInfo>(fieldInfo.id,
                                                                              JNIFieldInfo(fieldId,
                                                                                           clazz,
                                                                                           fieldInfo)));
                    }
                }
            }
        } else {
            JNI_LOGE("NativeInit: jniInfo is empty");
        }
        JNI_LOGI("NativeInit: end");
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          uint8_t *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 0 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN) {
            (*result) = JNIUtils::CallJavaBooleanMethod(env, &methodInfo, object, param);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          int8_t *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 0 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
            (*result) = JNIUtils::CallJavaByteMethod(env, &methodInfo, object, param);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          uint16_t *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 0 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
            (*result) = JNIUtils::CallJavaCharMethod(env, &methodInfo, object, param);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          int16_t *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 0 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT) {
            (*result) = JNIUtils::CallJavaShortMethod(env, &methodInfo, object, param);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          int32_t *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 0 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
            (*result) = JNIUtils::CallJavaIntMethod(env, &methodInfo, object, param);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          int64_t *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 0 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_LONG) {
            (*result) = JNIUtils::CallJavaLongMethod(env, &methodInfo, object, param);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          float *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 0 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
            (*result) = JNIUtils::CallJavaFloatMethod(env, &methodInfo, object, param);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          double *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 0 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE) {
            (*result) = JNIUtils::CallJavaDoubleMethod(env, &methodInfo, object, param);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          std::vector<uint8_t> *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 1 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_BOOLEAN) {
            auto arr = (jbooleanArray) JNIUtils::CallJavaObjectMethod(env, &methodInfo, object,
                                                                      param);
            if (!arr) {
                JNI_LOGE("arr is null");
                return;
            }
            JNIUtils::ExtractJavaBoolArray(env, arr, result);
            env->DeleteLocalRef(arr);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          std::vector<int8_t> *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 1 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_BYTE) {
            auto arr = (jbyteArray) JNIUtils::CallJavaObjectMethod(env, &methodInfo, object,
                                                                   param);
            if (!arr) {
                JNI_LOGE("arr is null");
                return;
            }
            JNIUtils::ExtractJavaByteArray(env, arr, result);
            env->DeleteLocalRef(arr);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          std::vector<uint16_t> *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 1 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_CHAR) {
            auto arr = (jcharArray) JNIUtils::CallJavaObjectMethod(env, &methodInfo, object,
                                                                   param);
            if (!arr) {
                JNI_LOGE("arr is null");
                return;
            }
            JNIUtils::ExtractJavaCharArray(env, arr, result);
            env->DeleteLocalRef(arr);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          std::vector<int16_t> *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 1 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_SHORT) {
            auto arr = (jshortArray) JNIUtils::CallJavaObjectMethod(env, &methodInfo, object,
                                                                    param);
            if (!arr) {
                JNI_LOGE("arr is null");
                return;
            }
            JNIUtils::ExtractJavaShortArray(env, arr, result);
            env->DeleteLocalRef(arr);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          std::vector<int32_t> *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 1 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_INT) {
            auto arr = (jintArray) JNIUtils::CallJavaObjectMethod(env, &methodInfo, object,
                                                                  param);
            if (!arr) {
                JNI_LOGE("arr is null");
                return;
            }
            JNIUtils::ExtractJavaIntArray(env, arr, result);
            env->DeleteLocalRef(arr);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          std::vector<int64_t> *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 1 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_LONG) {
            auto arr = (jlongArray) JNIUtils::CallJavaObjectMethod(env, &methodInfo, object,
                                                                   param);
            if (!arr) {
                JNI_LOGE("arr is null");
                return;
            }
            JNIUtils::ExtractJavaLongArray(env, arr, result);
            env->DeleteLocalRef(arr);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          std::vector<float> *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 1 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_FLOAT) {
            auto arr = (jfloatArray) JNIUtils::CallJavaObjectMethod(env, &methodInfo, object,
                                                                    param);
            if (!arr) {
                JNI_LOGE("arr is null");
                return;
            }
            JNIUtils::ExtractJavaFloatArray(env, arr, result);
            env->DeleteLocalRef(arr);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                          std::vector<double> *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (!methodInfo.classID || !methodInfo.methodID) {
            JNI_LOGE("CallJavaMethod: param error.");
            return;
        }
        if (methodInfo.returnObject.arrayDimension == 1 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_DOUBLE) {
            auto arr = (jdoubleArray) JNIUtils::CallJavaObjectMethod(env, &methodInfo, object,
                                                                     param);
            if (!arr) {
                JNI_LOGE("arr is null");
                return;
            }
            JNIUtils::ExtractJavaDoubleArray(env, arr, result);
            env->DeleteLocalRef(arr);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void
    JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                     std::string *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING &&
            methodInfo.returnObject.arrayDimension == 0) {
            auto str = (jstring) JNIUtils::CallJavaObjectMethod(env, &methodInfo, object, param);
            if (!str) {
                JNI_LOGE("str is null");
                return;
            }
            JNIUtils::ExtractJavaString(env, str, result);
            env->DeleteLocalRef(str);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void
    JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                     std::vector<std::string> *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (methodInfo.returnObject.arrayDimension == 1 &&
            returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_STRING) {
            auto strArr = (jobjectArray) JNIUtils::CallJavaObjectMethod(env, &methodInfo,
                                                                        object, param);
            if (!strArr) {
                JNI_LOGE("strArr is null");
                return;
            }
            JNIUtils::ExtractJavaStringArray(env, strArr, result);
            env->DeleteLocalRef(strArr);
        } else {
            JNI_LOGE(
                    "JNIMethodInfo is not match for CallJavaMethod, returnType: %" LIMIT "d, arrayDimension: %" LIMIT "d",
                    static_cast<int32_t>(returnType), methodInfo.returnObject.arrayDimension);
        }
    }

    void
    JSCallAndroidJni::CallJavaMethod(int32_t methodID, jobject object, jvalue *param,
                                     JavaMethodResult *result) {
        Jkit jkit;
        JNI_LOGI("CallJavaMethod: begin.");
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("CallJavaMethod: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIMethodInfo methodInfo = jniMethodInfos.at(methodID);
        MethodFlag returnType = GetReturnType(methodInfo.returnObject.flag);
        if (returnType == MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT) {
            result->value = JNIUtils::CallJavaObjectMethod(env, &methodInfo, object, param);
            result->returnObject = methodInfo.returnObject;
        }
    }

    void JSCallAndroidJni::GetJNIFieldInfo(int32_t id, JNIFieldInfo *jniFieldInfo) {
        (*jniFieldInfo) = jniFieldInfos.at(id);
    }

    void
    JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, uint8_t *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, int8_t *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, uint16_t *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, int16_t *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, int32_t *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, int64_t *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, float *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, double *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, std::string *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void
    JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, std::vector<uint8_t> *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void
    JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, std::vector<int8_t> *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                         std::vector<uint16_t> *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void
    JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, std::vector<int16_t> *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void
    JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, std::vector<int32_t> *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void
    JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, std::vector<int64_t> *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void
    JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, std::vector<float> *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void
    JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID, std::vector<double> *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void JSCallAndroidJni::GetFieldValue(jobject object, int32_t fieldID,
                                         std::vector<std::string> *target) {
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
        JNIUtils::GetFieldValue(env, object, &info, target);
    }

    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, uint8_t *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, *source);
    }

    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, int8_t *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, *source);
    }

    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, uint16_t *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, *source);
    }

    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, int16_t *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, *source);
    }

    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, int32_t *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, *source);
    }

    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, int64_t *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, *source);
    }

    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, float *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, *source);
    }

    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, double *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, *source);
    }

    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, std::string *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, source);
    }

    void
    JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, std::vector<uint8_t> *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, source);
    }

    void
    JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, std::vector<int8_t> *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, source);
    }

    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                         std::vector<uint16_t> *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, source);
    }

    void
    JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, std::vector<int16_t> *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, source);
    }

    void
    JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, std::vector<int32_t> *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, source);
    }

    void
    JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, std::vector<int64_t> *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, source);
    }

    void
    JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, std::vector<float> *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, source);
    }

    void
    JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID, std::vector<double> *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, source);
    }

    void JSCallAndroidJni::SetFieldValue(jobject object, int32_t fieldID,
                                         std::vector<std::string> *source) {
        if (jniFieldInfos.count(fieldID) < 1) {
            JNI_LOGE("SetFieldValue: fieldID is not init");
            return;
        }
        Jkit jkit;
        if ((jkit.IsValidEnv() & 1) == 0) {
            JNI_LOGE("SetFieldValue: env is null.");
            return;
        }
        JNIEnv *env = jkit.operator->();
        JNIFieldInfo info = jniFieldInfos.at(fieldID);
        JNIUtils::SetFieldValue(env, object, &info, source);
    }
}
