//
// Created by guobin on 2022/3/10.
//

#ifndef JNITEMPLATE_JNI_UTILS_H
#define JNITEMPLATE_JNI_UTILS_H

#include <jni.h>

#include <string>

#include "jni_info.h"
#include "jni_log.h"
#include "jni_transform.h"
#include "singleton.h"

namespace OHOS {
namespace TEMPLATE {

#define JAVA_LANG_STRING "java/lang/String"
#define JAVA_LANG_BOOLEAN "java/lang/Boolean"
#define JAVA_LANG_BYTE "java/lang/Byte"
#define JAVA_LANG_CHARACTER "java/lang/Character"
#define JAVA_LANG_SHORT "java/lang/Short"
#define JAVA_LANG_INTEGER "java/lang/Integer"
#define JAVA_LANG_LONG "java/lang/Long"
#define JAVA_LANG_FLOAT "java/lang/Float"
#define JAVA_LANG_DOUBLE "java/lang/Double"
#define JAVA_UTIL_LIST "java/util/ArrayList"
#define JAVA_UTIL_MAP "java/util/HashMap"
//#define JAVA_UTIL_ARRAY_LIST "java/util/ArrayList"
//#define JAVA_UTIL_HASH_MAP "java/util/HashMap"
#define JAVA_UTIL_SET "java/util/Set"
#define JAVA_UTIL_ITERATOR "java/util/Iterator"
#define JAVA_UTIL_MAP_ENTRY "java/util/Map$Entry"

enum JavaUtilMethod {
    StringInit = 0x00,
    BooleanInit = 0x10,
    Boolean_booleanValue,
    ByteInit = 0x20,
    Byte_byteValue,
    CharacterInit = 0x30,
    Character_charValue,
    ShortInit = 0x40,
    Short_shortValue,
    IntegerInit = 0x50,
    Integer_intValue,
    LongInit = 0x60,
    Long_longValue,
    FloatInit = 0x70,
    Float_floatValue,
    DoubleInit = 0x80,
    Double_doubleValue,
    ListInit = 0x90,
    List_size,
    List_get,
    List_add,
    MapInit = 0xA0,
    Map_size,
    Map_get,
    Map_put,
    Map_entrySet,
    HashMapInit = 0xB0,
    HashMap_put,
    ArrayListInit = 0xC0,
    ArrayList_add,
    SetInit = 0xD0,
    Set_iterator,
    IteratorInit = 0xE0,
    Iterator_hasNext,
    Iterator_next,
    Map_Entry_getKey = 0xF0,
    Map_Entry_getValue,
};

struct JavaUtilMethodInfo {
    JavaUtilMethod index;
    std::string name;
    std::string sign;

    JavaUtilMethodInfo() : index(), name(), sign() {}

    JavaUtilMethodInfo(JavaUtilMethod index, std::string name, std::string sign)
        : index(index), name(name), sign(sign) {}
};

class JNIUtils {
    JNIUtils();

    friend DelayedSingleton<JNIUtils>;

public:
    ~JNIUtils();

    int InitUtilJavaClass(JNIEnv *env);

    int InitModuleJavaClass(JNIEnv *env, const std::string &config);

    int GetJNIMethodInfo(int32_t methodID, JNIMethodInfo *methodInfo);

    int GetJNIFieldInfo(int32_t fieldID, JNIFieldInfo *fieldInfo);

    jclass GetModuleJClass(std::string name);

    jclass GetUtilJClass(std::string name);

    jmethodID GetUtilJMethodID(JavaUtilMethod id);

    void ClearException(JNIEnv *env);

    jboolean GetBooleanField(JNIEnv *env, jobject object, JNIFieldInfo *info);

    void SetBooleanField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                         jboolean value);

    jbyte GetByteField(JNIEnv *env, jobject object, JNIFieldInfo *info);

    void SetByteField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                      jbyte value);

    jchar GetCharField(JNIEnv *env, jobject object, JNIFieldInfo *info);

    void SetCharField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                      jchar value);

    jshort GetShortField(JNIEnv *env, jobject object, JNIFieldInfo *info);

    void SetShortField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                       jshort value);

    jint GetIntField(JNIEnv *env, jobject object, JNIFieldInfo *info);

    void SetIntField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                     jint value);

    jlong GetLongField(JNIEnv *env, jobject object, JNIFieldInfo *info);

    void SetLongField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                      jlong value);

    jfloat GetFloatField(JNIEnv *env, jobject object, JNIFieldInfo *info);

    void SetFloatField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                       jfloat value);

    jdouble GetDoubleField(JNIEnv *env, jobject object, JNIFieldInfo *info);

    void SetDoubleField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                        jdouble value);

    jobject GetObjectField(JNIEnv *env, jobject object, JNIFieldInfo *info);

    void SetObjectField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                        jobject value);

    void GetBooleanArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                              std::vector<uint8_t> *result);

    void SetBooleanArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                              std::vector<uint8_t> *source);

    void GetByteArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                           std::vector<int8_t> *result);

    void SetByteArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                           std::vector<int8_t> *source);

    void GetCharArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                           std::vector<uint16_t> *result);

    void SetCharArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                           std::vector<uint16_t> *source);

    void GetShortArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                            std::vector<int16_t> *result);

    void SetShortArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                            std::vector<int16_t> *source);

    void GetIntArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                          std::vector<int32_t> *result);

    void SetIntArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                          std::vector<int32_t> *source);

    void GetLongArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                           std::vector<int64_t> *result);

    void SetLongArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                           std::vector<int64_t> *source);

    void GetFloatArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                            std::vector<float> *result);

    void SetFloatArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                            std::vector<float> *source);

    void GetDoubleArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                             std::vector<double> *result);

    void SetDoubleArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                             std::vector<double> *source);

    void GetStringField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                        std::string *result);

    void SetStringField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                        std::string *source);

    void GetStringArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                             std::vector<std::string> *result);

    void SetStringArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                             std::vector<std::string> *source);

    void CallJavaVoidMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                            jobject holder, jvalue *param);

    jboolean CallJavaBooleanMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                   jobject holder, jvalue *param);

    jbyte CallJavaByteMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                             jobject holder, jvalue *param);

    jchar CallJavaCharMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                             jobject holder, jvalue *param);

    jshort CallJavaShortMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                               jobject holder, jvalue *param);

    jint CallJavaIntMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                           jobject holder, jvalue *param);

    jlong CallJavaLongMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                             jobject holder, jvalue *param);

    jfloat CallJavaFloatMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                               jobject holder, jvalue *param);

    jdouble CallJavaDoubleMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                 jobject holder, jvalue *param);

    void CallJavaStringMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                              jobject holder, jvalue *param,
                              std::string *result);

    jobject CallJavaObjectMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                 jobject holder, jvalue *param);

    void CallJavaBooleanArrayMethod(JNIEnv *env,
                                    JNIMethodInfo const *methodInfo,
                                    jobject holder, jvalue *param,
                                    std::vector<uint8_t> *result);

    void CallJavaByteArrayMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                 jobject holder, jvalue *param,
                                 std::vector<int8_t> *result);

    void CallJavaCharArrayMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                 jobject holder, jvalue *param,
                                 std::vector<uint16_t> *result);

    void CallJavaShortArrayMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                  jobject holder, jvalue *param,
                                  std::vector<int16_t> *result);

    void CallJavaIntArrayMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                jobject holder, jvalue *param,
                                std::vector<int32_t> *result);

    void CallJavaLongArrayMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                 jobject holder, jvalue *param,
                                 std::vector<int64_t> *result);

    void CallJavaFloatArrayMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                  jobject holder, jvalue *param,
                                  std::vector<float> *result);

    void CallJavaDoubleArrayMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                   jobject holder, jvalue *param,
                                   std::vector<double> *result);

    void CallJavaStringArrayMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                   jobject holder, jvalue *param,
                                   std::vector<std::string> *result);

    void ExtractJavaBoolArray(JNIEnv *env, jbooleanArray source,
                              std::vector<uint8_t> *result);

    void ExtractJavaByteArray(JNIEnv *env, jbyteArray source,
                              std::vector<int8_t> *result);

    void ExtractJavaCharArray(JNIEnv *env, jcharArray source,
                              std::vector<uint16_t> *result);

    void ExtractJavaShortArray(JNIEnv *env, jshortArray source,
                               std::vector<int16_t> *result);

    void ExtractJavaIntArray(JNIEnv *env, jintArray source,
                             std::vector<int32_t> *result);

    void ExtractJavaLongArray(JNIEnv *env, jlongArray source,
                              std::vector<int64_t> *result);

    void ExtractJavaFloatArray(JNIEnv *env, jfloatArray source,
                               std::vector<float> *result);

    void ExtractJavaDoubleArray(JNIEnv *env, jdoubleArray source,
                                std::vector<double> *result);

    void ExtractJavaString(JNIEnv *env, jstring source, std::string *result);

    void ExtractJavaString(JNIEnv *env, jstring source, char **result);

    void ExtractJavaStringArray(JNIEnv *env, jobjectArray source,
                                std::vector<std::string> *result);

    void ConvertJavaBoolArray(JNIEnv *env, std::vector<uint8_t> *source,
                              jbooleanArray *result);

    void ConvertJavaByteArray(JNIEnv *env, std::vector<int8_t> *source,
                              jbyteArray *result);

    void ConvertJavaCharArray(JNIEnv *env, std::vector<uint16_t> *source,
                              jcharArray *result);

    void ConvertJavaShortArray(JNIEnv *env, std::vector<int16_t> *source,
                               jshortArray *result);

    void ConvertJavaIntArray(JNIEnv *env, std::vector<int32_t> *source,
                             jintArray *result);

    void ConvertJavaLongArray(JNIEnv *env, std::vector<int64_t> *source,
                              jlongArray *result);

    void ConvertJavaFloatArray(JNIEnv *env, std::vector<float> *source,
                               jfloatArray *result);

    void ConvertJavaDoubleArray(JNIEnv *env, std::vector<double> *source,
                                jdoubleArray *result);

    void ConvertJavaString(JNIEnv *env, std::string *source, jstring *result);

    void ConvertJavaString(JNIEnv *env, std::string const *source,
                           jstring *result);

    void ConvertJavaString(JNIEnv *env, const char *source, jstring *result);

    void ConvertJavaStringArray(JNIEnv *env, std::vector<std::string> *source,
                                jobjectArray *result);

    template <typename T>
    void ExtractJavaObject(JNIEnv *env, jobject source, T *result,
                           Transform<T> *transform);

    template <typename T>
    void ExtractJavaObjectArray(JNIEnv *env, jobjectArray source,
                                std::vector<T> *result,
                                Transform<T> *transform);

    template <typename K, typename V>
    void ExtractJavaMap(JNIEnv *env, jobject source, std::map<K, V> *result,
                        Transform<K> *keyTransform,
                        Transform<V> *valueTransform);

    template <typename T>
    void ExtractJavaList(JNIEnv *env, jobject source, std::vector<T> *result,
                         Transform<T> *transform);

    template <typename T>
    void ConvertJavaObject(JNIEnv *env, T *source, jobject *result,
                           Transform<T> *transform);

    template <typename T>
    void ConvertJavaObjectArray(JNIEnv *env, std::vector<T> *source,
                                jobjectArray *result, Transform<T> *transform);

    template <typename K, typename V>
    void ConvertJavaMap(JNIEnv *env, std::map<K, V> *source, jobject *result,
                        Transform<K> *keyTransform,
                        Transform<V> *valueTransform);

    template <typename T>
    void ConvertJavaList(JNIEnv *env, std::vector<T> *source, jobject *result,
                         Transform<T> *transform);

    template <typename T>
    void CallJavaObjectMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                              jobject holder, jvalue *param, T *result,
                              Transform<T> *transform);

    template <typename T>
    void CallJavaObjectArrayMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                                   jobject holder, jvalue *param,
                                   std::vector<T> *result,
                                   Transform<T> *transform);

    template <typename T>
    void CallJavaListMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                            jobject holder, jvalue *param,
                            std::vector<T> *result, Transform<T> *transform);

    template <typename K, typename V>
    void CallJavaMapMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                           jobject holder, jvalue *param,
                           std::map<K, V> *result, Transform<K> *keyTransform,
                           Transform<V> *valueTransform);

    template <typename T>
    void GetObjectField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                        T *result, Transform<T> *transform);

    template <typename T>
    void GetObjectArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                             std::vector<T> *result, Transform<T> *transform);

    template <typename T>
    void GetListField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                      std::vector<T> *result, Transform<T> *transform);

    template <typename K, typename V>
    void GetMapField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                     std::map<K, V> *result, Transform<K> *keyTransform,
                     Transform<V> *valueTransform);

    template <typename T>
    void SetObjectField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                        T *source, Transform<T> *transform);

    template <typename T>
    void SetObjectArrayField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                             std::vector<T> *source, Transform<T> *transform);

    template <typename T>
    void SetListField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                      std::vector<T> *source, Transform<T> *transform);

    template <typename K, typename V>
    void SetMapField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                     std::map<K, V> *source, Transform<K> *keyTransform,
                     Transform<V> *valueTransform);

    jobject NewObject(JNIEnv *env, std::string *className);

private:
    void CreateClassMap();

private:
    JNIInfo jniInfo;
    std::map<std::string, std::vector<JavaUtilMethodInfo>> *sUtilClassMaps;
    std::map<std::string, jclass> *sUtilJClassIDs;
    std::map<JavaUtilMethod, jmethodID> *sUtilJMethodIDs;
    std::map<std::string, jclass> *sModuleJClassIDs;
    std::map<int32_t, JNIMethodInfo> *sModuleMethodInfos;
    std::map<int32_t, JNIFieldInfo> *sModuleFieldInfos;
};

template <typename T>
void JNIUtils::ExtractJavaObject(JNIEnv *env, jobject source, T *result,
                                 Transform<T> *transform) {
    transform->Extract(source, result);
}

template <typename T>
void JNIUtils::ExtractJavaObjectArray(JNIEnv *env, jobjectArray source,
                                      std::vector<T> *result,
                                      Transform<T> *transform) {
    jsize length = env->GetArrayLength(source);
    for (jsize i = 0; i < length; i++) {
        auto object = env->GetObjectArrayElement(source, i);
        if (object) {
            T item;
            transform->Extract(object, &item);
            result->push_back(item);
            env->DeleteLocalRef(object);
        }
    }
}

template <typename K, typename V>
void JNIUtils::ExtractJavaMap(JNIEnv *env, jobject source,
                              std::map<K, V> *result,
                              Transform<K> *keyTransform,
                              Transform<V> *valueTransform) {
    jobject entrySet = env->CallObjectMethod(
        source, GetUtilJMethodID(JavaUtilMethod::Map_entrySet));
    jobject iterator = env->CallObjectMethod(
        entrySet, GetUtilJMethodID(JavaUtilMethod::Set_iterator));
    while (env->CallBooleanMethod(
        iterator, GetUtilJMethodID(JavaUtilMethod::Iterator_hasNext))) {
        jobject entry = env->CallObjectMethod(
            iterator, GetUtilJMethodID(JavaUtilMethod::Iterator_next));
        jobject jKey = env->CallObjectMethod(
            entry, GetUtilJMethodID(JavaUtilMethod::Map_Entry_getKey));
        jobject jValue = env->CallObjectMethod(
            entry, GetUtilJMethodID(JavaUtilMethod::Map_Entry_getValue));
        K key;
        keyTransform->Extract(jKey, &key);
        V value;
        valueTransform->Extract(jValue, value);
        result->insert(std::pair<K, V>(key, value));
    }
}

template <class T>
void JNIUtils::ExtractJavaList(JNIEnv *env, jobject source,
                               std::vector<T> *result,
                               Transform<T> *transform) {
    jint length =
        env->CallIntMethod(source, GetUtilJMethodID(JavaUtilMethod::List_size));
    for (jint i = 0; i < length; i++) {
        auto object = env->CallObjectMethod(
            source, GetUtilJMethodID(JavaUtilMethod::List_get), i);
        if (object) {
            T resultItem;
            transform->Extract(object, &resultItem);
            result->push_back(resultItem);
            env->DeleteLocalRef(object);
        }
    }
}

template <typename T>
void JNIUtils::ConvertJavaObject(JNIEnv *env, T *source, jobject *result,
                                 Transform<T> *transform) {
    auto object = transform->CreateObject(source);
    if (!object) {
        JNI_LOGE("ConvertJavaMap: CreateObject failed.");
        return;
    }
    transform->Convert(object, source);
    (*result) = object;
}

template <typename T>
void JNIUtils::ConvertJavaObjectArray(JNIEnv *env, std::vector<T> *source,
                                      jobjectArray *result,
                                      Transform<T> *transform) {
    int size = source->size();
    jclass targetClass = GetModuleJClass(transform->GetClassName());
    if (size > 0 && targetClass) {
        auto array = env->NewObjectArray(size, targetClass, NULL);
        (*result) = static_cast<jobjectArray>(env->NewGlobalRef(array));
        for (int i = 0; i < size; ++i) {
            jobject item = transform->CreateObject(&(source->at(i)));
            if (!item) {
                JNI_LOGE("ConvertJavaMap: CreateObject failed.");
                break;
            }
            transform->Convert(item, &(source->at(i)));
            env->SetObjectArrayElement(*result, i, item);
        }
    }
}

template <typename K, typename V>
void JNIUtils::ConvertJavaMap(JNIEnv *env, std::map<K, V> *source,
                              jobject *result, Transform<K> *keyTransform,
                              Transform<V> *valueTransform) {
    JNI_LOGI("ConvertJavaMap: begin.");
    if (!source || !keyTransform || !valueTransform) {
        JNI_LOGE("ConvertJavaMap: params is null");
        return;
    }
    std::string keyClassName = keyTransform->GetClassName();
    std::string valueClassName = valueTransform->GetClassName();
    auto map = env->NewObject(GetUtilJClass(JAVA_UTIL_MAP),
                              GetUtilJMethodID(JavaUtilMethod::MapInit));
    (*result) = static_cast<jobjectArray>(env->NewGlobalRef(map));
    for (auto it = source->begin(); it != source->end(); it++) {
        jobject jKey = keyTransform->CreateObject(it->first);
        jobject jValue = valueTransform->CreateObject(it->second);
        if (!jKey || !jValue) {
            JNI_LOGE("ConvertJavaMap: CreateObject failed.");
            break;
        }
        keyTransform->Convert(jKey, it->first);
        valueTransform->Convert(jKey, it->second);
        env->CallObjectMethod(
            *result, GetUtilJMethodID(JavaUtilMethod::Map_put), jKey, jValue);
    }
    JNI_LOGI("ConvertJavaMap: end.");
}

template <class T>
void JNIUtils::ConvertJavaList(JNIEnv *env, std::vector<T> *source,
                               jobject *result, Transform<T> *transform) {
    JNI_LOGI("ConvertJavaList: begin.");
    if (!source || !transform) {
        JNI_LOGE("ConvertJavaList: params is null");
        return;
    }
    jint size = source->size();
    if (size > 0) {
        jobject list =
            env->NewObject(GetUtilJClass(JAVA_UTIL_LIST),
                           GetUtilJMethodID(JavaUtilMethod::ListInit), "");
        (*result) = env->NewGlobalRef(list);
        for (jint i = 0; i < size; ++i) {
            jobject item = transform->CreateObject(&(source->at(i)));
            if (!item) {
                JNI_LOGE("ConvertJavaMap: CreateObject failed.");
                break;
            }
            transform->Convert(item, &(source->at(i)));
            env->CallVoidMethod(
                *result, GetUtilJMethodID(JavaUtilMethod::List_add), i, item);
        }
    }
    JNI_LOGI("ConvertJavaList: end.");
}

template <typename T>
void JNIUtils::CallJavaObjectMethod(JNIEnv *env,
                                    const JNIMethodInfo *methodInfo,
                                    jobject holder, jvalue *param, T *result,
                                    Transform<T> *transform) {
    jobject source = CallJavaObjectMethod(env, methodInfo, holder, param);
    if (source) {
        transform->Extract(source, result);
        env->DeleteLocalRef(source);
    }
}

template <typename T>
void JNIUtils::CallJavaObjectArrayMethod(JNIEnv *env,
                                         const JNIMethodInfo *methodInfo,
                                         jobject holder, jvalue *param,
                                         std::vector<T> *result,
                                         Transform<T> *transform) {
    jobjectArray source =
        (jobjectArray)CallJavaObjectMethod(env, methodInfo, holder, param);
    if (source) {
        ExtractJavaObjectArray(env, source, result, transform);
        env->DeleteLocalRef(source);
    }
}

template <typename T>
void JNIUtils::CallJavaListMethod(JNIEnv *env, const JNIMethodInfo *methodInfo,
                                  jobject holder, jvalue *param,
                                  std::vector<T> *result,
                                  Transform<T> *transform) {
    jobject source = CallJavaObjectMethod(env, methodInfo, holder, param);
    if (source) {
        ExtractJavaList(env, source, result, transform);
        env->DeleteLocalRef(source);
    }
}

template <typename K, typename V>
void JNIUtils::CallJavaMapMethod(JNIEnv *env, const JNIMethodInfo *methodInfo,
                                 jobject holder, jvalue *param,
                                 std::map<K, V> *result,
                                 Transform<K> *keyTransform,
                                 Transform<V> *valueTransform) {
    jobject source = CallJavaObjectMethod(env, methodInfo, holder, param);
    if (source) {
        ExtractJavaMap(source, result, keyTransform, valueTransform);
        env->DeleteLocalRef(source);
    }
}

template <typename T>
void JNIUtils::GetObjectField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                              T *result, Transform<T> *transform) {
    jobject source = GetObjectField(env, object, info);
    if (source) {
        transform->Extract(source, result);
        env->DeleteLocalRef(source);
    }
}

template <typename T>
void JNIUtils::GetObjectArrayField(JNIEnv *env, jobject object,
                                   JNIFieldInfo *info, std::vector<T> *result,
                                   Transform<T> *transform) {
    jobjectArray source = (jobjectArray)GetObjectField(env, object, info);
    if (source) {
        ExtractJavaObjectArray(env, source, result, transform);
        env->DeleteLocalRef(source);
    }
}

template <typename T>
void JNIUtils::GetListField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                            std::vector<T> *result, Transform<T> *transform) {
    jobject source = GetObjectField(env, object, info);
    if (source) {
        ExtractJavaList(env, source, result, transform);
        env->DeleteLocalRef(source);
    }
}

template <typename K, typename V>
void JNIUtils::GetMapField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                           std::map<K, V> *result, Transform<K> *keyTransform,
                           Transform<V> *valueTransform) {
    jobject source = GetObjectField(env, object, info);
    if (source) {
        ExtractJavaMap(source, result, keyTransform, valueTransform);
        env->DeleteLocalRef(source);
    }
}

template <typename T>
void JNIUtils::SetObjectField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                              T *source, Transform<T> *transform) {
    jobject target = transform->CreateObject(source);
    if (target) {
        JNI_LOGE("ConvertJavaMap: CreateObject failed.");
        return;
    }
    transform->Convert(target, source);
    env->SetObjectField(object, info->fieldId, target);
}

template <typename T>
void JNIUtils::SetObjectArrayField(JNIEnv *env, jobject object,
                                   JNIFieldInfo *info, std::vector<T> *source,
                                   Transform<T> *transform) {
    jobjectArray target;
    ConvertJavaObjectArray(env, source, &target, transform);
    if (target) {
        env->SetObjectField(object, info->fieldId, target);
    }
    // env->DeleteGlobalRef(target);
}

template <typename T>
void JNIUtils::SetListField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                            std::vector<T> *source, Transform<T> *transform) {
    jobject target;
    ConvertJavaList(env, source, &target, transform);
    if (target) {
        env->SetObjectField(object, info->fieldId, target);
    }
    // env->DeleteGlobalRef(target);
}

template <typename K, typename V>
void JNIUtils::SetMapField(JNIEnv *env, jobject object, JNIFieldInfo *info,
                           std::map<K, V> *source, Transform<K> *keyTransform,
                           Transform<V> *valueTransform) {
    jobject target;
    ConvertJavaMap(env, source, &target, keyTransform, valueTransform);
    if (target) {
        env->SetObjectField(object, info->fieldId, target);
    }
    // env->DeleteGlobalRef(target);
}

}  // namespace TEMPLATE
}  // namespace OHOS

#endif  // JNITEMPLATE_JNI_UTILS_H
