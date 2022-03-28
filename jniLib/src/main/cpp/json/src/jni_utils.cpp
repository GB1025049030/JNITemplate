//
// Created by guobin on 2022/3/10.
//

#include "jni_utils.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "jkit.h"
#include "jni_log.h"

namespace OHOS {
namespace TEMPLATE {

JNIUtils::JNIUtils() {
    JNI_LOGI("instance is created");
    sUtilClassMaps =
        new std::map<std::string, std::vector<JavaUtilMethodInfo>>();
    CreateClassMap();
    sUtilJClassIDs = new std::map<std::string, jclass>();
    sUtilJMethodIDs = new std::map<JavaUtilMethod, jmethodID>();
    sModuleJClassIDs = new std::map<std::string, jclass>();
    sModuleMethodInfos = new std::map<int32_t, JNIMethodInfo>();
    sModuleFieldInfos = new std::map<int32_t, JNIFieldInfo>();
}

JNIUtils::~JNIUtils() {
    JNI_LOGI("instance is destroyed");
    Jkit jkit;
    if (jkit.IsValidEnv()) {
        JNIEnv *env = jkit.operator->();
        for (std::map<std::string, jclass>::iterator it =
                 sUtilJClassIDs->begin();
             it != sUtilJClassIDs->end(); it++) {
            if (it->second) {
                env->DeleteGlobalRef(it->second);
            }
        }
        for (std::map<std::string, jclass>::iterator it =
                 sModuleJClassIDs->begin();
             it != sModuleJClassIDs->end(); it++) {
            if (it->second) {
                env->DeleteGlobalRef(it->second);
            }
        }
    }
    delete sUtilJMethodIDs;
    delete sUtilJClassIDs;
    delete sUtilClassMaps;
    delete sModuleJClassIDs;
    delete sModuleMethodInfos;
    delete sModuleFieldInfos;
}

int JNIUtils::InitUtilJavaClass(JNIEnv *env) {
    std::map<std::string, std::vector<JavaUtilMethodInfo>>::iterator it;
    for (it = sUtilClassMaps->begin(); it != sUtilClassMaps->end(); it++) {
        auto clazzRet = env->FindClass(it->first.c_str());
        if (!clazzRet) {
            JNI_LOGE("InitJavaUtilList : class(%" LOG_LIMIT "s) is not exist",
                     it->first.c_str());
            return JNI_ERR;
        }
        auto clazz = (jclass)env->NewGlobalRef(clazzRet);
        sUtilJClassIDs->insert(
            std::pair<std::string, jclass>(it->first.c_str(), clazz));
        for (auto info : it->second) {
            jmethodID method =
                env->GetMethodID(clazz, info.name.c_str(), info.sign.c_str());
            if (!method) {
                JNI_LOGE("InitJavaUtilList : class(%" LOG_LIMIT
                         "s) don't have method(%" LOG_LIMIT "s)",
                         it->first.c_str(), info.name.c_str());
                continue;
            }
            sUtilJMethodIDs->insert(
                std::pair<JavaUtilMethod, jmethodID>(info.index, method));
        }
    }
    return JNI_OK;
}

int JNIUtils::InitModuleJavaClass(JNIEnv *env, const std::string &config) {
    JNI_LOGI("InitModuleJavaClass: begin");
    nlohmann::json jsonObject;
    std::ifstream jsonFile(
        "/sdcard/Android/data/com.pandon.javaapi.testannotation/files/" +
        config);
    jsonFile >> jsonObject;
    from_json(jsonObject, jniInfo);
    JNI_LOGI("InitModuleJavaClass: load config success");
    if (!jniInfo.classes.empty()) {
        for (auto &classInfo : jniInfo.classes) {
            JNI_LOGI("InitModuleJavaClass: class : %" LOG_LIMIT "s",
                     classInfo.className.c_str());
            auto clazzRet = env->FindClass(classInfo.className.c_str());
            if (!clazzRet) {
                JNI_LOGE("InitModuleJavaClass : class(%" LOG_LIMIT
                         "s) is not exist",
                         classInfo.className.c_str());
                continue;
            }
            auto clazz = (jclass)env->NewGlobalRef(clazzRet);
            if (!clazz) {
                JNI_LOGE("InitModuleJavaClass : class(%" LOG_LIMIT
                         "s) is not exist",
                         classInfo.className.c_str());
                continue;
            }
            sModuleJClassIDs->insert(
                std::pair<std::string, jclass>(classInfo.className, clazz));
            if (!classInfo.methods.empty()) {
                for (auto &methodInfo : classInfo.methods) {
                    jmethodID methodID;
                    if (JNIInfoUtil::IsStatic(
                            methodInfo.returnObject.baseType.flag)) {
                        methodID = env->GetStaticMethodID(
                            clazz, methodInfo.name.c_str(),
                            methodInfo.sign.c_str());
                    } else {
                        methodID =
                            env->GetMethodID(clazz, methodInfo.name.c_str(),
                                             methodInfo.sign.c_str());
                    }
                    if (!methodID) {
                        JNI_LOGE("InitModuleJavaClass: method %" LOG_LIMIT
                                 "s(sign: %" LOG_LIMIT "s, id = %" LOG_LIMIT
                                 "d) is not exist",
                                 methodInfo.name.c_str(),
                                 methodInfo.sign.c_str(), methodInfo.id);
                        ClearException(env);
                        continue;
                    }
                    sModuleMethodInfos->insert(
                        std::pair<int32_t, JNIMethodInfo>(
                            methodInfo.id,
                            JNIMethodInfo(methodID, clazz,
                                          methodInfo.returnObject)));
                }
            }
            if (!classInfo.fields.empty()) {
                for (auto &fieldInfo : classInfo.fields) {
                    jfieldID fieldId;
                    JNI_LOGD("guobin: name: %s, flag: %d",
                             fieldInfo.name.c_str(), fieldInfo.baseType.flag);
                    if (fieldInfo.baseType.additionalValue) {
                        JNI_LOGD("guobin: additionalValue: flag: %d",
                                 fieldInfo.baseType.additionalValue->flag);
                    }
                    if (fieldInfo.baseType.additionalKey) {
                        JNI_LOGD("guobin: additionalKey: flag: %d",
                                 fieldInfo.baseType.additionalKey->flag);
                    }
                    if (JNIInfoUtil::IsStatic(fieldInfo.baseType.flag)) {
                        fieldId = env->GetStaticFieldID(
                            clazz, fieldInfo.name.c_str(),
                            fieldInfo.baseType.sign.c_str());
                    } else {
                        fieldId =
                            env->GetFieldID(clazz, fieldInfo.name.c_str(),
                                            fieldInfo.baseType.sign.c_str());
                    }
                    if (!fieldId) {
                        JNI_LOGE("InitModuleJavaClass: field %" LOG_LIMIT
                                 "s(sign: %" LOG_LIMIT "s, id = %" LOG_LIMIT
                                 "d) is not exist",
                                 fieldInfo.name.c_str(),
                                 fieldInfo.baseType.sign.c_str(), fieldInfo.id);
                        ClearException(env);
                        continue;
                    }
                    sModuleFieldInfos->insert(std::pair<int32_t, JNIFieldInfo>(
                        fieldInfo.id, JNIFieldInfo(fieldId, clazz, fieldInfo)));
                }
            }
        }
    } else {
        JNI_LOGE("InitModuleJavaClass: jniInfo is empty");
        return JNI_ERR;
    }
    JNI_LOGI("InitModuleJavaClass: end");
    return JNI_OK;
}

int JNIUtils::GetJNIMethodInfo(int32_t methodID, JNIMethodInfo *methodInfo) {
    if (sModuleMethodInfos) {
        if (sModuleMethodInfos->count(methodID) > 0) {
            (*methodInfo) = sModuleMethodInfos->at(methodID);
            if (methodInfo->classID && methodInfo->methodID) {
                return JNI_OK;
            }
        }
    }
    JNI_LOGE("GetJNIMethodInfo: methodID(%" LOG_LIMIT "d) is not init",
             methodID);
    return JNI_ERR;
}

int JNIUtils::GetJNIFieldInfo(int32_t fieldID, JNIFieldInfo *fieldInfo) {
    if (sModuleFieldInfos) {
        if (sModuleFieldInfos->count(fieldID) > 0) {
            (*fieldInfo) = sModuleFieldInfos->at(fieldID);
            if (fieldInfo->classID && fieldInfo->fieldId) {
                return JNI_OK;
            }
        }
    }
    JNI_LOGE("GetJNIFieldInfo: fieldID(%" LOG_LIMIT "d) is not init", fieldID);
    return JNI_ERR;
}

jclass JNIUtils::GetModuleJClass(std::string name) {
    if (sModuleJClassIDs) {
        if (sModuleJClassIDs->count(name) > 0) {
            return sModuleJClassIDs->at(name);
        }
    }
    JNI_LOGE("GetModuleJClass : class(%" LOG_LIMIT "s) don't init",
             JAVA_LANG_STRING);
    return nullptr;
}

jclass JNIUtils::GetUtilJClass(std::string name) {
    if (sUtilJClassIDs) {
        if (sUtilJClassIDs->count(name) > 0) {
            return sUtilJClassIDs->at(name);
        }
    }
    JNI_LOGE("GetUtilJClass : class(%" LOG_LIMIT "s) don't init",
             JAVA_LANG_STRING);
    return nullptr;
}

jmethodID JNIUtils::GetUtilJMethodID(JavaUtilMethod id) {
    if (sUtilJMethodIDs) {
        if (sUtilJMethodIDs->count(id) > 0) {
            return sUtilJMethodIDs->at(id);
        }
    }
    JNI_LOGE("GetUtilJMethodID : method(%" LOG_LIMIT "d) don't init", id);
    return nullptr;
}

void JNIUtils::ClearException(JNIEnv *env) {
    if (env->ExceptionCheck()) {
        JNI_LOGE("exception occurred");
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
}

jboolean JNIUtils::GetBooleanField(JNIEnv *env, jobject object,
                                   JNIFieldInfo *info) {
    jboolean result = JNI_FALSE;
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        result = env->GetStaticBooleanField(info->classID, info->fieldId);
    } else {
        if (!object) {
            JNI_LOGE("GetBooleanField : object is null");
            return result;
        }
        result = env->GetBooleanField(object, info->fieldId);
    }
    ClearException(env);
    return result;
}

void JNIUtils::SetBooleanField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                               jboolean value) {
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        env->SetStaticBooleanField(info->classID, info->fieldId, value);
    } else {
        if (!object) {
            JNI_LOGE("SetBooleanField : object is null");
            return;
        }
        env->SetBooleanField(object, info->fieldId, value);
    }
    ClearException(env);
}

jbyte JNIUtils::GetByteField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
    jbyte result = 0;
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        result = env->GetStaticByteField(info->classID, info->fieldId);
    } else {
        if (!object) {
            JNI_LOGE("GetByteField : object is null");
            return result;
        }
        result = env->GetByteField(object, info->fieldId);
    }
    ClearException(env);
    return result;
}

void JNIUtils::SetByteField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                            jbyte value) {
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        env->SetStaticByteField(info->classID, info->fieldId, value);
    } else {
        if (!object) {
            JNI_LOGE("SetByteField : object is null");
            return;
        }
        env->SetByteField(object, info->fieldId, value);
    }
    ClearException(env);
}

jchar JNIUtils::GetCharField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
    jchar result = 0;
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        result = env->GetStaticCharField(info->classID, info->fieldId);
    } else {
        if (!object) {
            JNI_LOGE("GetCharField : object is null");
            return result;
        }
        result = env->GetCharField(object, info->fieldId);
    }
    ClearException(env);
    return result;
}

void JNIUtils::SetCharField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                            jchar value) {
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        env->SetStaticCharField(info->classID, info->fieldId, value);
    } else {
        if (!object) {
            JNI_LOGE("SetCharField : object is null");
            return;
        }
        env->SetCharField(object, info->fieldId, value);
    }
    ClearException(env);
}

jshort JNIUtils::GetShortField(JNIEnv *env, jobject object,
                               JNIFieldInfo *info) {
    jshort result = 0;
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        result = env->GetStaticShortField(info->classID, info->fieldId);
    } else {
        if (!object) {
            JNI_LOGE("GetShortField : object is null");
            return result;
        }
        result = env->GetShortField(object, info->fieldId);
    }
    ClearException(env);
    return result;
}

void JNIUtils::SetShortField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                             jshort value) {
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        env->SetStaticShortField(info->classID, info->fieldId, value);
    } else {
        if (!object) {
            JNI_LOGE("SetShortField : object is null");
            return;
        }
        env->SetShortField(object, info->fieldId, value);
    }
    ClearException(env);
}

jint JNIUtils::GetIntField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
    jint result = 0;
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        result = env->GetStaticIntField(info->classID, info->fieldId);
    } else {
        if (!object) {
            JNI_LOGE("GetIntField : object is null");
            return result;
        }
        result = env->GetIntField(object, info->fieldId);
    }
    ClearException(env);
    return result;
}

void JNIUtils::SetIntField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                           jint value) {
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        env->SetStaticIntField(info->classID, info->fieldId, value);
    } else {
        if (!object) {
            JNI_LOGE("SetIntField : object is null");
            return;
        }
        env->SetIntField(object, info->fieldId, value);
    }
    ClearException(env);
}

jlong JNIUtils::GetLongField(JNIEnv *env, jobject object, JNIFieldInfo *info) {
    jlong result = 0;
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        result = env->GetStaticLongField(info->classID, info->fieldId);
    } else {
        if (!object) {
            JNI_LOGE("GetLongField : object is null");
            return result;
        }
        result = env->GetLongField(object, info->fieldId);
    }
    ClearException(env);
    return result;
}

void JNIUtils::SetLongField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                            jlong value) {
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        env->SetStaticLongField(info->classID, info->fieldId, value);
    } else {
        if (!object) {
            JNI_LOGE("SetLongField : object is null");
            return;
        }
        env->SetLongField(object, info->fieldId, value);
    }
    ClearException(env);
}

jfloat JNIUtils::GetFloatField(JNIEnv *env, jobject object,
                               JNIFieldInfo *info) {
    jfloat result = 0;
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        result = env->GetStaticFloatField(info->classID, info->fieldId);
    } else {
        if (!object) {
            JNI_LOGE("GetFloatField : object is null");
            return result;
        }
        result = env->GetFloatField(object, info->fieldId);
    }
    ClearException(env);
    return result;
}

void JNIUtils::SetFloatField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                             jfloat value) {
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        env->SetStaticFloatField(info->classID, info->fieldId, value);
    } else {
        if (!object) {
            JNI_LOGE("SetFloatField : object is null");
            return;
        }
        env->SetFloatField(object, info->fieldId, value);
    }
    ClearException(env);
}

jdouble JNIUtils::GetDoubleField(JNIEnv *env, jobject object,
                                 JNIFieldInfo *info) {
    jdouble result = 0;
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        result = env->GetStaticDoubleField(info->classID, info->fieldId);
    } else {
        if (!object) {
            JNI_LOGE("GetDoubleField : object is null");
            return result;
        }
        result = env->GetDoubleField(object, info->fieldId);
    }
    ClearException(env);
    return result;
}

void JNIUtils::SetDoubleField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                              jdouble value) {
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        env->SetStaticDoubleField(info->classID, info->fieldId, value);
    } else {
        if (!object) {
            JNI_LOGE("SetDoubleField : object is null");
            return;
        }
        env->SetDoubleField(object, info->fieldId, value);
    }
    ClearException(env);
}

jobject JNIUtils::GetObjectField(JNIEnv *env, jobject object,
                                 JNIFieldInfo *info) {
    jobject result = nullptr;
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        result = env->GetStaticObjectField(info->classID, info->fieldId);
    } else {
        if (!object) {
            JNI_LOGE("GetObjectField : object is null");
            return result;
        }
        result = env->GetObjectField(object, info->fieldId);
    }
    ClearException(env);
    return result;
}

void JNIUtils::SetObjectField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                              jobject value) {
    if (JNIInfoUtil::IsStatic(info->fieldInfo.baseType.flag)) {
        env->SetStaticObjectField(info->classID, info->fieldId, value);
    } else {
        if (!object) {
            JNI_LOGE("SetObjectField : object is null");
            return;
        }
        env->SetObjectField(object, info->fieldId, value);
    }
    ClearException(env);
}

void JNIUtils::GetBooleanArrayField(JNIEnv *env, jobject object,
                                    JNIFieldInfo *info,
                                    std::vector<uint8_t> *result) {
    auto source = static_cast<jbooleanArray>(GetObjectField(env, object, info));
    ExtractJavaBoolArray(env, source, result);
    env->DeleteLocalRef(source);
}

void JNIUtils::GetByteArrayField(JNIEnv *env, jobject object,
                                 JNIFieldInfo *info,
                                 std::vector<int8_t> *result) {
    auto source = static_cast<jbyteArray>(GetObjectField(env, object, info));
    ExtractJavaByteArray(env, source, result);
    env->DeleteLocalRef(source);
}

void JNIUtils::GetCharArrayField(JNIEnv *env, jobject object,
                                 JNIFieldInfo *info,
                                 std::vector<uint16_t> *result) {
    auto source = static_cast<jcharArray>(GetObjectField(env, object, info));
    ExtractJavaCharArray(env, source, result);
    env->DeleteLocalRef(source);
}

void JNIUtils::GetShortArrayField(JNIEnv *env, jobject object,
                                  JNIFieldInfo *info,
                                  std::vector<int16_t> *result) {
    auto source = static_cast<jshortArray>(GetObjectField(env, object, info));
    ExtractJavaShortArray(env, source, result);
    env->DeleteLocalRef(source);
}

void JNIUtils::GetIntArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                std::vector<int32_t> *result) {
    auto source = static_cast<jintArray>(GetObjectField(env, object, info));
    ExtractJavaIntArray(env, source, result);
    env->DeleteLocalRef(source);
}

void JNIUtils::GetLongArrayField(JNIEnv *env, jobject object,
                                 JNIFieldInfo *info,
                                 std::vector<int64_t> *result) {
    auto source = static_cast<jlongArray>(GetObjectField(env, object, info));
    ExtractJavaLongArray(env, source, result);
    env->DeleteLocalRef(source);
}

void JNIUtils::GetFloatArrayField(JNIEnv *env, jobject object,
                                  JNIFieldInfo *info,
                                  std::vector<float> *result) {
    auto source = static_cast<jfloatArray>(GetObjectField(env, object, info));
    ExtractJavaFloatArray(env, source, result);
    env->DeleteLocalRef(source);
}

void JNIUtils::GetDoubleArrayField(JNIEnv *env, jobject object,
                                   JNIFieldInfo *info,
                                   std::vector<double> *result) {
    auto source = static_cast<jdoubleArray>(GetObjectField(env, object, info));
    ExtractJavaDoubleArray(env, source, result);
    env->DeleteLocalRef(source);
}

void JNIUtils::GetStringField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                              std::string *result) {
    auto source = static_cast<jstring>(GetObjectField(env, object, info));
    ExtractJavaString(env, source, result);
    env->DeleteLocalRef(source);
}

void JNIUtils::GetStringArrayField(JNIEnv *env, jobject object,
                                   JNIFieldInfo *info,
                                   std::vector<std::string> *result) {
    auto source = static_cast<jobjectArray>(GetObjectField(env, object, info));
    ExtractJavaStringArray(env, source, result);
    env->DeleteLocalRef(source);
}

void JNIUtils::SetBooleanArrayField(JNIEnv *env, jobject object,
                                    JNIFieldInfo *info,
                                    std::vector<uint8_t> *source) {
    jbooleanArray arr = env->NewBooleanArray(source->size());
    ConvertJavaBoolArray(env, source, &arr);
    SetObjectField(env, object, info, arr);
    ClearException(env);
}

void JNIUtils::SetByteArrayField(JNIEnv *env, jobject object,
                                 JNIFieldInfo *info,
                                 std::vector<int8_t> *source) {
    jbyteArray arr = env->NewByteArray(source->size());
    ConvertJavaByteArray(env, source, &arr);
    SetObjectField(env, object, info, arr);
    ClearException(env);
}

void JNIUtils::SetCharArrayField(JNIEnv *env, jobject object,
                                 JNIFieldInfo *info,
                                 std::vector<uint16_t> *source) {
    jcharArray arr = env->NewCharArray(source->size());
    ConvertJavaCharArray(env, source, &arr);
    SetObjectField(env, object, info, arr);
    ClearException(env);
}

void JNIUtils::SetShortArrayField(JNIEnv *env, jobject object,
                                  JNIFieldInfo *info,
                                  std::vector<int16_t> *source) {
    jshortArray arr = env->NewShortArray(source->size());
    ConvertJavaShortArray(env, source, &arr);
    SetObjectField(env, object, info, arr);
    ClearException(env);
}

void JNIUtils::SetIntArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                std::vector<int32_t> *source) {
    jintArray arr = env->NewIntArray(source->size());
    ConvertJavaIntArray(env, source, &arr);
    SetObjectField(env, object, info, arr);
    ClearException(env);
}

void JNIUtils::SetLongArrayField(JNIEnv *env, jobject object,
                                 JNIFieldInfo *info,
                                 std::vector<int64_t> *source) {
    jlongArray arr = env->NewLongArray(source->size());
    ConvertJavaLongArray(env, source, &arr);
    SetObjectField(env, object, info, arr);
    ClearException(env);
}

void JNIUtils::SetFloatArrayField(JNIEnv *env, jobject object,
                                  JNIFieldInfo *info,
                                  std::vector<float> *source) {
    jfloatArray arr = env->NewFloatArray(source->size());
    ConvertJavaFloatArray(env, source, &arr);
    SetObjectField(env, object, info, arr);
    ClearException(env);
}

void JNIUtils::SetDoubleArrayField(JNIEnv *env, jobject object,
                                   JNIFieldInfo *info,
                                   std::vector<double> *source) {
    jdoubleArray arr = env->NewDoubleArray(source->size());
    ConvertJavaDoubleArray(env, source, &arr);
    SetObjectField(env, object, info, arr);
    ClearException(env);
}

void JNIUtils::SetStringField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                              std::string *source) {
    jstring str;
    ConvertJavaString(env, source, &str);
    SetObjectField(env, object, info, str);
    ClearException(env);
}

void JNIUtils::SetStringArrayField(JNIEnv *env, jobject object,
                                   JNIFieldInfo *info,
                                   std::vector<std::string> *source) {
    jclass jstringClass = env->FindClass(JAVA_LANG_STRING);
    jint size = (jint)source->size();
    if (size > 0) {
        jobjectArray strArr = env->NewObjectArray(size, jstringClass, nullptr);
        for (jint i = 0; i < size; ++i) {
            jstring str;
            ConvertJavaString(env, &(source->at(i)), &str);
            env->SetObjectArrayElement(strArr, i, str);
        }
        env->SetObjectField(object, info->fieldId, strArr);
    }
}

void JNIUtils::ExtractJavaBoolArray(JNIEnv *env, jbooleanArray source,
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

void JNIUtils::ExtractJavaByteArray(JNIEnv *env, jbyteArray source,
                                    std::vector<int8_t> *result) {
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

void JNIUtils::ExtractJavaCharArray(JNIEnv *env, jcharArray source,
                                    std::vector<uint16_t> *result) {
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

void JNIUtils::ExtractJavaShortArray(JNIEnv *env, jshortArray source,
                                     std::vector<int16_t> *result) {
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

void JNIUtils::ExtractJavaIntArray(JNIEnv *env, jintArray source,
                                   std::vector<int32_t> *result) {
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

void JNIUtils::ExtractJavaLongArray(JNIEnv *env, jlongArray source,
                                    std::vector<int64_t> *result) {
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

void JNIUtils::ExtractJavaFloatArray(JNIEnv *env, jfloatArray source,
                                     std::vector<float> *result) {
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

void JNIUtils::ExtractJavaString(JNIEnv *env, jstring source,
                                 std::string *result) {
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
        auto j_str = (jstring)env->GetObjectArrayElement(source, i);
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
        env->SetBooleanArrayRegion(*result, 0, (int)size, buff);
    }
}

void JNIUtils::ConvertJavaByteArray(JNIEnv *env, std::vector<int8_t> *source,
                                    jbyteArray *result) {
    if (!env || !source || !result) {
        return;
    }
    size_t size = source->size();
    if (size > 0) {
        jbyte buff[size];
        for (size_t i = 0; i < size; ++i) {
            buff[i] = source->at(i);
        }
        env->SetByteArrayRegion(*result, 0, (int)size, buff);
    }
}

void JNIUtils::ConvertJavaCharArray(JNIEnv *env, std::vector<uint16_t> *source,
                                    jcharArray *result) {
    if (!env || !source || !result) {
        return;
    }
    size_t size = source->size();
    if (size > 0) {
        jchar buff[size];
        for (size_t i = 0; i < size; ++i) {
            buff[i] = source->at(i);
        }
        env->SetCharArrayRegion(*result, 0, (int)size, buff);
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
        env->SetShortArrayRegion(*result, 0, (int)size, buff);
    }
}

void JNIUtils::ConvertJavaIntArray(JNIEnv *env, std::vector<int32_t> *source,
                                   jintArray *result) {
    if (!env || !source || !result) {
        return;
    }
    size_t size = source->size();
    if (size > 0) {
        jint buff[size];
        for (size_t i = 0; i < size; ++i) {
            buff[i] = source->at(i);
        }
        env->SetIntArrayRegion(*result, 0, (int)size, buff);
    }
}

void JNIUtils::ConvertJavaLongArray(JNIEnv *env, std::vector<int64_t> *source,
                                    jlongArray *result) {
    if (!env || !source || !result) {
        return;
    }
    size_t size = source->size();
    if (size > 0) {
        jlong buff[size];
        for (size_t i = 0; i < size; ++i) {
            buff[i] = source->at(i);
        }
        env->SetLongArrayRegion(*result, 0, (int)size, buff);
    }
}

void JNIUtils::ConvertJavaFloatArray(JNIEnv *env, std::vector<float> *source,
                                     jfloatArray *result) {
    if (!env || !source || !result) {
        return;
    }
    size_t size = source->size();
    if (size > 0) {
        jfloat buff[size];
        for (size_t i = 0; i < size; ++i) {
            buff[i] = source->at(i);
        }
        env->SetFloatArrayRegion(*result, 0, (int)size, buff);
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
        env->SetDoubleArrayRegion(*result, 0, (int)size, buff);
    }
}

void JNIUtils::ConvertJavaString(JNIEnv *env, std::string *source,
                                 jstring *result) {
    if (!env || !source || !result) {
        return;
    }
    jclass strClass = env->FindClass(JAVA_LANG_STRING);
    jmethodID init =
        env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    const char *str = source->c_str();
    jbyteArray bytes = env->NewByteArray((jsize)strlen(str));
    env->SetByteArrayRegion(bytes, 0, (jsize)strlen(str), (jbyte *)str);
    jstring encoding = env->NewStringUTF("GB2312");
    auto ret = (jstring)env->NewObject(strClass, init, bytes, encoding);
    if (ret) {
        (*result) = static_cast<jstring>(env->NewGlobalRef(ret));
    }
}

void JNIUtils::ConvertJavaString(JNIEnv *env, std::string const *source,
                                 jstring *result) {
    if (!env || !source || !result) {
        return;
    }
    jclass strClass = env->FindClass(JAVA_LANG_STRING);
    jmethodID init =
        env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    const char *str = source->c_str();
    jbyteArray bytes = env->NewByteArray((jsize)strlen(str));
    env->SetByteArrayRegion(bytes, 0, (jsize)strlen(str), (jbyte *)str);
    jstring encoding = env->NewStringUTF("GB2312");
    auto ret = (jstring)env->NewObject(strClass, init, bytes, encoding);
    if (ret) {
        (*result) = static_cast<jstring>(env->NewGlobalRef(ret));
    }
}

void JNIUtils::ConvertJavaString(JNIEnv *env, const char *source,
                                 jstring *result) {
    if (!env || !source || !result) {
        return;
    }
    jclass strClass = env->FindClass(JAVA_LANG_STRING);
    jmethodID init =
        env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray((jsize)strlen(source));
    env->SetByteArrayRegion(bytes, 0, (jsize)strlen(source), (jbyte *)source);
    jstring encoding = env->NewStringUTF("GB2312");
    auto ret = (jstring)env->NewObject(strClass, init, bytes, encoding);
    if (ret) {
        (*result) = static_cast<jstring>(env->NewGlobalRef(ret));
    }
}

void JNIUtils::ConvertJavaStringArray(JNIEnv *env,
                                      std::vector<std::string> *source,
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

jobject JNIUtils::CallJavaObjectMethod(JNIEnv *env,
                                       JNIMethodInfo const *methodInfo,
                                       jobject holder, jvalue *param) {
    jobject ret = nullptr;
    if (JNIInfoUtil::IsStatic(methodInfo->returnObject.baseType.flag)) {
        ret = env->CallStaticObjectMethodA(methodInfo->classID,
                                           methodInfo->methodID, param);
        ClearException(env);
    } else {
        jobject object = holder;
        if (!object) {
            JNI_LOGW("CallJavaObjectMethod : holder is null");
            jmethodID init =
                env->GetMethodID(methodInfo->classID, "<init>", "()V");
            object = env->NewObject(methodInfo->classID, init);
            ClearException(env);
        }
        if (!object) {
            JNI_LOGE(
                "CallJavaObjectMethod : object is null, there may be no "
                "no-argument constructor");
            return ret;
        }
        if (JNIInfoUtil::IsNonvirtual(methodInfo->returnObject.baseType.flag)) {
            ret = env->CallNonvirtualObjectMethodA(object, methodInfo->classID,
                                                   methodInfo->methodID, param);
        } else {
            ret = env->CallObjectMethodA(object, methodInfo->methodID, param);
        }
        ClearException(env);
    }
    return ret;
}

jboolean JNIUtils::CallJavaBooleanMethod(JNIEnv *env,
                                         JNIMethodInfo const *methodInfo,
                                         jobject holder, jvalue *param) {
    jboolean ret = JNI_FALSE;
    if (JNIInfoUtil::IsStatic(methodInfo->returnObject.baseType.flag)) {
        ret = env->CallStaticBooleanMethodA(methodInfo->classID,
                                            methodInfo->methodID, param);
        ClearException(env);
    } else {
        jobject object = holder;
        if (!object) {
            JNI_LOGW("CallJavaBooleanMethod : holder is null");
            jmethodID init =
                env->GetMethodID(methodInfo->classID, "<init>", "()V");
            object = env->NewObject(methodInfo->classID, init);
            ClearException(env);
        }
        if (!object) {
            JNI_LOGE(
                "CallJavaBooleanMethod : object is null, there may be no "
                "no-argument constructor");
            return ret;
        }
        if (JNIInfoUtil::IsNonvirtual(methodInfo->returnObject.baseType.flag)) {
            ret = env->CallNonvirtualBooleanMethodA(
                object, methodInfo->classID, methodInfo->methodID, param);
        } else {
            ret = env->CallBooleanMethodA(object, methodInfo->methodID, param);
        }
        ClearException(env);
    }
    return ret;
}

jbyte JNIUtils::CallJavaByteMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                   jobject holder, jvalue *param) {
    jbyte ret = 0;
    if (JNIInfoUtil::IsStatic(methodInfo->returnObject.baseType.flag)) {
        ret = env->CallStaticByteMethodA(methodInfo->classID,
                                         methodInfo->methodID, param);
        ClearException(env);
    } else {
        jobject object = holder;
        if (!object) {
            JNI_LOGW("CallJavaByteMethod : holder is null");
            jmethodID init =
                env->GetMethodID(methodInfo->classID, "<init>", "()V");
            object = env->NewObject(methodInfo->classID, init);
            ClearException(env);
        }
        if (!object) {
            JNI_LOGE(
                "CallJavaByteMethod : object is null, there may be no "
                "no-argument constructor");
            return ret;
        }
        if (JNIInfoUtil::IsNonvirtual(methodInfo->returnObject.baseType.flag)) {
            ret = env->CallNonvirtualByteMethodA(object, methodInfo->classID,
                                                 methodInfo->methodID, param);
        } else {
            ret = env->CallByteMethodA(object, methodInfo->methodID, param);
        }
        ClearException(env);
    }
    return ret;
}

jchar JNIUtils::CallJavaCharMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                   jobject holder, jvalue *param) {
    jchar ret = 0;
    if (JNIInfoUtil::IsStatic(methodInfo->returnObject.baseType.flag)) {
        ret = env->CallStaticCharMethodA(methodInfo->classID,
                                         methodInfo->methodID, param);
        ClearException(env);
    } else {
        jobject object = holder;
        if (!object) {
            JNI_LOGW("CallJavaCharMethod : holder is null");
            jmethodID init =
                env->GetMethodID(methodInfo->classID, "<init>", "()V");
            object = env->NewObject(methodInfo->classID, init);
            ClearException(env);
        }
        if (!object) {
            JNI_LOGE(
                "CallJavaCharMethod : object is null, there may be no "
                "no-argument constructor");
            return ret;
        }
        if (JNIInfoUtil::IsNonvirtual(methodInfo->returnObject.baseType.flag)) {
            ret = env->CallNonvirtualCharMethodA(object, methodInfo->classID,
                                                 methodInfo->methodID, param);
        } else {
            ret = env->CallCharMethodA(object, methodInfo->methodID, param);
        }
        ClearException(env);
    }
    return ret;
}

jshort JNIUtils::CallJavaShortMethod(JNIEnv *env,
                                     JNIMethodInfo const *methodInfo,
                                     jobject holder, jvalue *param) {
    jshort ret = 0;
    if (JNIInfoUtil::IsStatic(methodInfo->returnObject.baseType.flag)) {
        ret = env->CallStaticShortMethodA(methodInfo->classID,
                                          methodInfo->methodID, param);
        ClearException(env);
    } else {
        jobject object = holder;
        if (!object) {
            JNI_LOGW("CallJavaShortMethod : holder is null");
            jmethodID init =
                env->GetMethodID(methodInfo->classID, "<init>", "()V");
            object = env->NewObject(methodInfo->classID, init);
            ClearException(env);
        }
        if (!object) {
            JNI_LOGE(
                "CallJavaShortMethod : object is null, there may be no "
                "no-argument constructor");
            return ret;
        }
        if (JNIInfoUtil::IsNonvirtual(methodInfo->returnObject.baseType.flag)) {
            ret = env->CallNonvirtualShortMethodA(object, methodInfo->classID,
                                                  methodInfo->methodID, param);
        } else {
            ret = env->CallShortMethodA(object, methodInfo->methodID, param);
        }
        ClearException(env);
    }
    return ret;
}

jint JNIUtils::CallJavaIntMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                 jobject holder, jvalue *param) {
    jint ret = 0;
    if (JNIInfoUtil::IsStatic(methodInfo->returnObject.baseType.flag)) {
        ret = env->CallStaticIntMethodA(methodInfo->classID,
                                        methodInfo->methodID, param);
        ClearException(env);
    } else {
        jobject object = holder;
        if (!object) {
            JNI_LOGW("CallJavaIntMethod : holder is null");
            jmethodID init =
                env->GetMethodID(methodInfo->classID, "<init>", "()V");
            object = env->NewObject(methodInfo->classID, init);
            ClearException(env);
        }
        if (!object) {
            JNI_LOGE(
                "CallJavaIntMethod : object is null, there may be no "
                "no-argument constructor");
            return ret;
        }
        if (JNIInfoUtil::IsNonvirtual(methodInfo->returnObject.baseType.flag)) {
            ret = env->CallNonvirtualIntMethodA(object, methodInfo->classID,
                                                methodInfo->methodID, param);
        } else {
            ret = env->CallIntMethodA(object, methodInfo->methodID, param);
        }
        ClearException(env);
    }
    return ret;
}

jlong JNIUtils::CallJavaLongMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                   jobject holder, jvalue *param) {
    jlong ret = 0;
    if (JNIInfoUtil::IsStatic(methodInfo->returnObject.baseType.flag)) {
        ret = env->CallStaticLongMethodA(methodInfo->classID,
                                         methodInfo->methodID, param);
        ClearException(env);
    } else {
        jobject object = holder;
        if (!object) {
            JNI_LOGW("CallJavaLongMethod : holder is null");
            jmethodID init =
                env->GetMethodID(methodInfo->classID, "<init>", "()V");
            object = env->NewObject(methodInfo->classID, init);
            ClearException(env);
        }
        if (!object) {
            JNI_LOGE(
                "CallJavaLongMethod : object is null, there may be no "
                "no-argument constructor");
            return ret;
        }
        if (JNIInfoUtil::IsNonvirtual(methodInfo->returnObject.baseType.flag)) {
            ret = env->CallNonvirtualLongMethodA(object, methodInfo->classID,
                                                 methodInfo->methodID, param);
        } else {
            ret = env->CallLongMethodA(object, methodInfo->methodID, param);
        }
        ClearException(env);
    }
    return ret;
}

jfloat JNIUtils::CallJavaFloatMethod(JNIEnv *env,
                                     JNIMethodInfo const *methodInfo,
                                     jobject holder, jvalue *param) {
    jfloat ret = 0;
    if (JNIInfoUtil::IsStatic(methodInfo->returnObject.baseType.flag)) {
        ret = env->CallStaticFloatMethodA(methodInfo->classID,
                                          methodInfo->methodID, param);
        ClearException(env);
    } else {
        jobject object = holder;
        if (!object) {
            JNI_LOGW("CallJavaFloatMethod : holder is null");
            jmethodID init =
                env->GetMethodID(methodInfo->classID, "<init>", "()V");
            object = env->NewObject(methodInfo->classID, init);
            ClearException(env);
        }
        if (!object) {
            JNI_LOGE(
                "CallJavaFloatMethod : object is null, there may be no "
                "no-argument constructor");
            return ret;
        }
        if (JNIInfoUtil::IsNonvirtual(methodInfo->returnObject.baseType.flag)) {
            ret = env->CallNonvirtualFloatMethodA(object, methodInfo->classID,
                                                  methodInfo->methodID, param);
        } else {
            ret = env->CallFloatMethodA(object, methodInfo->methodID, param);
        }
        ClearException(env);
    }
    return ret;
}

jdouble JNIUtils::CallJavaDoubleMethod(JNIEnv *env,
                                       JNIMethodInfo const *methodInfo,
                                       jobject holder, jvalue *param) {
    jdouble ret = 0;
    if (JNIInfoUtil::IsStatic(methodInfo->returnObject.baseType.flag)) {
        ret = env->CallStaticDoubleMethodA(methodInfo->classID,
                                           methodInfo->methodID, param);
        ClearException(env);
    } else {
        jobject object = holder;
        if (!object) {
            JNI_LOGW("CallJavaDoubleMethod : holder is null");
            jmethodID init =
                env->GetMethodID(methodInfo->classID, "<init>", "()V");
            object = env->NewObject(methodInfo->classID, init);
            ClearException(env);
        }
        if (!object) {
            JNI_LOGE(
                "CallJavaDoubleMethod : object is null, there may be no "
                "no-argument constructor");
            return ret;
        }
        if (JNIInfoUtil::IsNonvirtual(methodInfo->returnObject.baseType.flag)) {
            ret = env->CallNonvirtualDoubleMethodA(object, methodInfo->classID,
                                                   methodInfo->methodID, param);
        } else {
            ret = env->CallDoubleMethodA(object, methodInfo->methodID, param);
        }
        ClearException(env);
    }
    return ret;
}

void JNIUtils::CallJavaVoidMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                  jobject holder, jvalue *param) {
    if (JNIInfoUtil::IsStatic(methodInfo->returnObject.baseType.flag)) {
        env->CallStaticVoidMethodA(methodInfo->classID, methodInfo->methodID,
                                   param);
        ClearException(env);
    } else {
        jobject object = holder;
        if (!object) {
            JNI_LOGW("CallJavaVoidMethod : holder is null");
            jmethodID init =
                env->GetMethodID(methodInfo->classID, "<init>", "()V");
            object = env->NewObject(methodInfo->classID, init);
            ClearException(env);
        }
        if (!object) {
            JNI_LOGE(
                "CallJavaVoidMethod : object is null, there may be no "
                "no-argument constructor");
            return;
        }
        if (JNIInfoUtil::IsNonvirtual(methodInfo->returnObject.baseType.flag)) {
            env->CallNonvirtualVoidMethodA(object, methodInfo->classID,
                                           methodInfo->methodID, param);
        } else {
            env->CallVoidMethodA(object, methodInfo->methodID, param);
        }
        ClearException(env);
    }
}

void JNIUtils::CallJavaStringMethod(JNIEnv *env,
                                    const JNIMethodInfo *methodInfo,
                                    jobject holder, jvalue *param,
                                    std::string *result) {
    auto str =
        (jstring)CallJavaObjectMethod(env, methodInfo, holder, param);
    if (!str) {
        JNI_LOGE("CallJavaMethod: str is null");
        return;
    }
    ExtractJavaString(env, str, result);
    env->DeleteLocalRef(str);
}

void JNIUtils::CallJavaBooleanArrayMethod(JNIEnv *env,
                                          const JNIMethodInfo *methodInfo,
                                          jobject holder, jvalue *param,
                                          std::vector<uint8_t> *result) {
    auto arr =
        (jbooleanArray)CallJavaObjectMethod(env, methodInfo, holder, param);
    if (!arr) {
        JNI_LOGE("CallJavaBooleanArrayMethod: arr is null");
        return;
    }
    ExtractJavaBoolArray(env, arr, result);
    env->DeleteLocalRef(arr);
}

void JNIUtils::CallJavaByteArrayMethod(JNIEnv *env,
                                       const JNIMethodInfo *methodInfo,
                                       jobject holder, jvalue *param,
                                       std::vector<int8_t> *result) {
    auto arr = (jbyteArray)CallJavaObjectMethod(env, methodInfo, holder, param);
    if (!arr) {
        JNI_LOGE("CallJavaByteArrayMethod: arr is null");
        return;
    }
    ExtractJavaByteArray(env, arr, result);
    env->DeleteLocalRef(arr);
}

void JNIUtils::CallJavaCharArrayMethod(JNIEnv *env,
                                       const JNIMethodInfo *methodInfo,
                                       jobject holder, jvalue *param,
                                       std::vector<uint16_t> *result) {
    auto arr = (jcharArray)CallJavaObjectMethod(env, methodInfo, holder, param);
    if (!arr) {
        JNI_LOGE("CallJavaCharArrayMethod: arr is null");
        return;
    }
    ExtractJavaCharArray(env, arr, result);
    env->DeleteLocalRef(arr);
}

void JNIUtils::CallJavaShortArrayMethod(JNIEnv *env,
                                        const JNIMethodInfo *methodInfo,
                                        jobject holder, jvalue *param,
                                        std::vector<int16_t> *result) {
    auto arr =
        (jshortArray)CallJavaObjectMethod(env, methodInfo, holder, param);
    if (!arr) {
        JNI_LOGE("CallJavaShortArrayMethod: arr is null");
        return;
    }
    ExtractJavaShortArray(env, arr, result);
    env->DeleteLocalRef(arr);
}

void JNIUtils::CallJavaIntArrayMethod(JNIEnv *env,
                                      const JNIMethodInfo *methodInfo,
                                      jobject holder, jvalue *param,
                                      std::vector<int32_t> *result) {
    auto arr = (jintArray)CallJavaObjectMethod(env, methodInfo, holder, param);
    if (!arr) {
        JNI_LOGE("CallJavaIntArrayMethod: arr is null");
        return;
    }
    ExtractJavaIntArray(env, arr, result);
    env->DeleteLocalRef(arr);
}

void JNIUtils::CallJavaLongArrayMethod(JNIEnv *env,
                                       const JNIMethodInfo *methodInfo,
                                       jobject holder, jvalue *param,
                                       std::vector<int64_t> *result) {
    auto arr = (jlongArray)CallJavaObjectMethod(env, methodInfo, holder, param);
    if (!arr) {
        JNI_LOGE("CallJavaLongArrayMethod: arr is null");
        return;
    }
    ExtractJavaLongArray(env, arr, result);
    env->DeleteLocalRef(arr);
}

void JNIUtils::CallJavaFloatArrayMethod(JNIEnv *env,
                                        const JNIMethodInfo *methodInfo,
                                        jobject holder, jvalue *param,
                                        std::vector<float> *result) {
    auto arr =
        (jfloatArray)CallJavaObjectMethod(env, methodInfo, holder, param);
    if (!arr) {
        JNI_LOGE("CallJavaFloatArrayMethod: arr is null");
        return;
    }
    ExtractJavaFloatArray(env, arr, result);
    env->DeleteLocalRef(arr);
}

void JNIUtils::CallJavaDoubleArrayMethod(JNIEnv *env,
                                         const JNIMethodInfo *methodInfo,
                                         jobject holder, jvalue *param,
                                         std::vector<double> *result) {
    auto arr =
        (jdoubleArray)CallJavaObjectMethod(env, methodInfo, holder, param);
    if (!arr) {
        JNI_LOGE("CallJavaDoubleArrayMethod: arr is null");
        return;
    }
    ExtractJavaDoubleArray(env, arr, result);
    env->DeleteLocalRef(arr);
}

void JNIUtils::CallJavaStringArrayMethod(JNIEnv *env,
                                         const JNIMethodInfo *methodInfo,
                                         jobject holder, jvalue *param,
                                         std::vector<std::string> *result) {
    auto arr = (jobjectArray)JNIUtils::CallJavaObjectMethod(env, methodInfo,
                                                            holder, param);
    if (!arr) {
        JNI_LOGE("CallJavaStringArrayMethod: strArr is null");
        return;
    }
    ExtractJavaStringArray(env, arr, result);
    env->DeleteLocalRef(arr);
}

jobject JNIUtils::NewObject(JNIEnv *env, std::string *className) {
    jobject result = nullptr;
    if (className && !className->empty()) {
        jclass clazz = GetModuleJClass(*className);
        if (!clazz) {
            clazz = GetUtilJClass(*className);
        }
        if (clazz) {
            jmethodID init = env->GetMethodID(clazz, "<init>", "()V");
            result = env->NewObject(clazz, init);
        }
    } else {
        JNI_LOGE("NewObject : className is null or empty");
    }
    return result;
}

void JNIUtils::CreateClassMap() {
    // TODO: JAVA_LANG_STRING
    std::vector<JavaUtilMethodInfo> java_lang_String{
        JavaUtilMethodInfo(JavaUtilMethod::StringInit, "<init>", "()V")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_LANG_STRING, java_lang_String));
    // TODO: JAVA_LANG_BOOLEAN
    std::vector<JavaUtilMethodInfo> java_lang_Boolean{
        JavaUtilMethodInfo(JavaUtilMethod::BooleanInit, "<init>", "(Z)V"),
        JavaUtilMethodInfo(JavaUtilMethod::Boolean_booleanValue, "booleanValue",
                           "()Z")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_LANG_BOOLEAN, java_lang_Boolean));
    // TODO: JAVA_LANG_BYTE
    std::vector<JavaUtilMethodInfo> java_lang_Byte{
        JavaUtilMethodInfo(JavaUtilMethod::ByteInit, "<init>", "(B)V"),
        JavaUtilMethodInfo(JavaUtilMethod::Byte_byteValue, "byteValue", "()B")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_LANG_BYTE, java_lang_Byte));
    // TODO: JAVA_LANG_CHARACTER
    std::vector<JavaUtilMethodInfo> java_lang_Character{
        JavaUtilMethodInfo(JavaUtilMethod::CharacterInit, "<init>", "(C)V"),
        JavaUtilMethodInfo(JavaUtilMethod::Character_charValue, "charValue",
                           "()C")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_LANG_CHARACTER, java_lang_Character));
    // TODO: JAVA_LANG_SHORT
    std::vector<JavaUtilMethodInfo> java_lang_Short{
        JavaUtilMethodInfo(JavaUtilMethod::ShortInit, "<init>", "(S)V"),
        JavaUtilMethodInfo(JavaUtilMethod::Short_shortValue, "shortValue",
                           "()S")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_LANG_SHORT, java_lang_Short));
    // TODO: JAVA_LANG_INTEGER
    std::vector<JavaUtilMethodInfo> java_lang_Integer{
        JavaUtilMethodInfo(JavaUtilMethod::IntegerInit, "<init>", "(I)V"),
        JavaUtilMethodInfo(JavaUtilMethod::Integer_intValue, "intValue",
                           "()I")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_LANG_INTEGER, java_lang_Integer));
    // TODO: JAVA_LANG_LONG
    std::vector<JavaUtilMethodInfo> java_lang_Long{
        JavaUtilMethodInfo(JavaUtilMethod::LongInit, "<init>", "(J)V"),
        JavaUtilMethodInfo(JavaUtilMethod::Long_longValue, "longValue", "()J")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_LANG_LONG, java_lang_Long));
    // TODO: JAVA_LANG_FLOAT
    std::vector<JavaUtilMethodInfo> java_lang_Float{
        JavaUtilMethodInfo(JavaUtilMethod::FloatInit, "<init>", "(F)V"),
        JavaUtilMethodInfo(JavaUtilMethod::Float_floatValue, "floatValue",
                           "()F")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_LANG_FLOAT, java_lang_Float));
    // TODO: JAVA_LANG_DOUBLE
    std::vector<JavaUtilMethodInfo> java_lang_Double{
        JavaUtilMethodInfo(JavaUtilMethod::DoubleInit, "<init>", "(D)V"),
        JavaUtilMethodInfo(JavaUtilMethod::Double_doubleValue, "doubleValue",
                           "()D")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_LANG_DOUBLE, java_lang_Double));
    // TODO: JAVA_UTIL_LIST
    std::vector<JavaUtilMethodInfo> java_lang_List{
        JavaUtilMethodInfo(JavaUtilMethod::ListInit, "<init>", "()V"),
        JavaUtilMethodInfo(JavaUtilMethod::List_add, "add",
                           "(ILjava/lang/Object;)V"),
        JavaUtilMethodInfo(JavaUtilMethod::List_get, "get",
                           "(I)Ljava/lang/Object;"),
        JavaUtilMethodInfo(JavaUtilMethod::List_size, "size", "()I")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_UTIL_LIST, java_lang_List));
    // TODO: JAVA_UTIL_MAP
    std::vector<JavaUtilMethodInfo> java_lang_Map{
        JavaUtilMethodInfo(JavaUtilMethod::MapInit, "<init>", "()V"),
        JavaUtilMethodInfo(
            JavaUtilMethod::Map_put, "put",
            "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;"),
        JavaUtilMethodInfo(JavaUtilMethod::Map_get, "get",
                           "(Ljava/lang/Object;)Ljava/lang/Object;"),
        JavaUtilMethodInfo(JavaUtilMethod::Map_size, "size", "()I"),
        JavaUtilMethodInfo(JavaUtilMethod::Map_entrySet, "entrySet",
                           "()Ljava/util/Set;")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(JAVA_UTIL_MAP,
                                                                java_lang_Map));
    // TODO: JAVA_UTIL_SET
    std::vector<JavaUtilMethodInfo> java_util_Set{
        JavaUtilMethodInfo(JavaUtilMethod::SetInit, "<init>", "()V"),
        JavaUtilMethodInfo(JavaUtilMethod::Set_iterator, "iterator",
                           "()Ljava/util/Iterator;")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(JAVA_UTIL_SET,
                                                                java_util_Set));
    // TODO: JAVA_UTIL_ITERATOR
    std::vector<JavaUtilMethodInfo> java_util_Iterator{
        JavaUtilMethodInfo(JavaUtilMethod::IteratorInit, "<init>", "()V"),
        JavaUtilMethodInfo(JavaUtilMethod::Iterator_hasNext, "hasNext", "()Z"),
        JavaUtilMethodInfo(JavaUtilMethod::Iterator_next, "next",
                           "()Ljava/lang/Object;")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_UTIL_ITERATOR, java_util_Iterator));
    // TODO: JAVA_UTIL_MAP_ENTRY
    std::vector<JavaUtilMethodInfo> java_util_map_entry{
        JavaUtilMethodInfo(JavaUtilMethod::Map_Entry_getKey, "getKey",
                           "()Ljava/lang/Object;"),
        JavaUtilMethodInfo(JavaUtilMethod::Map_Entry_getValue, "getValue",
                           "()Ljava/lang/Object;")};
    sUtilClassMaps->insert(
        std::pair<std::string, std::vector<JavaUtilMethodInfo>>(
            JAVA_UTIL_MAP_ENTRY, java_util_map_entry));
}

int32_t JNITest(JNIEnv *env) {
    auto clazzRet = env->FindClass(JAVA_LANG_STRING);
    auto clazz = (jclass)env->NewGlobalRef(clazzRet);
    jmethodID list_init =
        env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;)V");
    return JNI_ERR;
}
}  // namespace TEMPLATE
}  // namespace OHOS