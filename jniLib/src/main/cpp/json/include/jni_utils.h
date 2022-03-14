//
// Created by guobin on 2022/3/10.
//

#ifndef JNITEMPLATE_JNI_UTILS_H
#define JNITEMPLATE_JNI_UTILS_H

#include <jni.h>
#include <string>
#include "jni_info.h"
#include "jni_transform.h"

namespace OHOS {
    class JNIUtils {
    public:
        static void ClearException(JNIEnv *env);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, uint8_t *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, uint8_t source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int8_t *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int8_t source);

        static void
        GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, uint16_t *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, uint16_t source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int16_t *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int16_t source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int32_t *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int32_t source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int64_t *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, int64_t source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, float *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, float source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, double *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, double source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<uint8_t> *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<uint8_t> *source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<int8_t> *result);

        static void
        SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, std::vector<int8_t> *source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<uint16_t> *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<uint16_t> *source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<int16_t> *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<int16_t> *source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<int32_t> *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<int32_t> *source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<int64_t> *result);

        static void SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<int64_t> *source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<float> *result);

        static void
        SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, std::vector<float> *source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<double> *result);

        static void
        SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, std::vector<double> *source);

        static void
        GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, std::string *result);

        static void
        SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info, std::string *source);

        static void GetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                                  std::vector<std::string> *result);

        static void
        SetFieldValue(JNIEnv *env, jobject object, JNIFieldInfo *info,
                      std::vector<std::string> *source);

        static jobject
        CallJavaObjectMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                             jobject object, jvalue *param);

        static jboolean
        CallJavaBooleanMethod(JNIEnv *env, JNIMethodInfo const *methodInfo,
                              jobject object, jvalue *param);

        static jbyte
        CallJavaByteMethod(JNIEnv *env, JNIMethodInfo const *methodInfo, jobject object,
                           jvalue *param);

        static jchar
        CallJavaCharMethod(JNIEnv *env, JNIMethodInfo const *methodInfo, jobject object,
                           jvalue *param);

        static jshort
        CallJavaShortMethod(JNIEnv *env, JNIMethodInfo const *methodInfo, jobject object,
                            jvalue *param);

        static jint
        CallJavaIntMethod(JNIEnv *env, JNIMethodInfo const *methodInfo, jobject object,
                          jvalue *param);

        static jlong
        CallJavaLongMethod(JNIEnv *env, JNIMethodInfo const *methodInfo, jobject object,
                           jvalue *param);

        static jfloat
        CallJavaFloatMethod(JNIEnv *env, JNIMethodInfo const *methodInfo, jobject object,
                            jvalue *param);

        static jdouble
        CallJavaDoubleMethod(JNIEnv *env, JNIMethodInfo const *methodInfo, jobject object,
                             jvalue *param);

        static void
        CallJavaVoidMethod(JNIEnv *env, JNIMethodInfo const *methodInfo, jobject object,
                           jvalue *param);

        static void ExtractJavaBoolArray(JNIEnv *env, jbooleanArray source,
                                         std::vector<uint8_t> *result);

        static void
        ExtractJavaByteArray(JNIEnv *env, jbyteArray source, std::vector<int8_t> *result);

        static void
        ExtractJavaCharArray(JNIEnv *env, jcharArray source, std::vector<uint16_t> *result);

        static void ExtractJavaShortArray(JNIEnv *env, jshortArray source,
                                          std::vector<int16_t> *result);

        static void
        ExtractJavaIntArray(JNIEnv *env, jintArray source, std::vector<int32_t> *result);

        static void
        ExtractJavaLongArray(JNIEnv *env, jlongArray source, std::vector<int64_t> *result);

        static void ExtractJavaFloatArray(JNIEnv *env, jfloatArray source,
                                          std::vector<float> *result);

        static void
        ExtractJavaDoubleArray(JNIEnv *env, jdoubleArray source,
                               std::vector<double> *result);

        static void ExtractJavaString(JNIEnv *env, jstring source, std::string *result);

        static void ExtractJavaString(JNIEnv *env, jstring source, char **result);

        static void
        ExtractJavaStringArray(JNIEnv *env, jobjectArray source,
                               std::vector<std::string> *result);

        static void ConvertJavaBoolArray(JNIEnv *env, std::vector<uint8_t> *source,
                                         jbooleanArray *result);

        static void ConvertJavaByteArray(JNIEnv *env, std::vector<int8_t> *source,
                                         jbyteArray *result);

        static void ConvertJavaCharArray(JNIEnv *env, std::vector<uint16_t> *source,
                                         jcharArray *result);

        static void ConvertJavaShortArray(JNIEnv *env, std::vector<int16_t> *source,
                                          jshortArray *result);

        static void ConvertJavaIntArray(JNIEnv *env, std::vector<int32_t> *source,
                                        jintArray *result);

        static void ConvertJavaLongArray(JNIEnv *env, std::vector<int64_t> *source,
                                         jlongArray *result);

        static void ConvertJavaFloatArray(JNIEnv *env, std::vector<float> *source,
                                          jfloatArray *result);

        static void ConvertJavaDoubleArray(JNIEnv *env, std::vector<double> *source,
                                           jdoubleArray *result);

        static void ConvertJavaString(JNIEnv *env, std::string *source, jstring *result);

        static void ConvertJavaString(JNIEnv *env, const char *source, jstring *result);

        static void ConvertJavaStringArray(JNIEnv *env, std::vector<std::string> *source,
                                           jobjectArray *result);

        static jboolean GetBooleanField(JNIEnv *env, jobject object, JNIFieldInfo *info);

        static void
        SetBooleanField(JNIEnv *env, jobject object, JNIFieldInfo *info, jboolean value);

        static jbyte GetByteField(JNIEnv *env, jobject object, JNIFieldInfo *info);

        static void SetByteField(JNIEnv *env, jobject object, JNIFieldInfo *info, jbyte value);

        static jchar GetCharField(JNIEnv *env, jobject object, JNIFieldInfo *info);

        static void SetCharField(JNIEnv *env, jobject object, JNIFieldInfo *info, jchar value);

        static jshort GetShortField(JNIEnv *env, jobject object, JNIFieldInfo *info);

        static void SetShortField(JNIEnv *env, jobject object, JNIFieldInfo *info, jshort value);

        static jint GetIntField(JNIEnv *env, jobject object, JNIFieldInfo *info);

        static void SetIntField(JNIEnv *env, jobject object, JNIFieldInfo *info, jint value);

        static jlong GetLongField(JNIEnv *env, jobject object, JNIFieldInfo *info);

        static void SetLongField(JNIEnv *env, jobject object, JNIFieldInfo *info, jlong value);

        static jfloat GetFloatField(JNIEnv *env, jobject object, JNIFieldInfo *info);

        static void SetFloatField(JNIEnv *env, jobject object, JNIFieldInfo *info, jfloat value);

        static jdouble GetDoubleField(JNIEnv *env, jobject object, JNIFieldInfo *info);

        static void SetDoubleField(JNIEnv *env, jobject object, JNIFieldInfo *info, jdouble value);

        static jobject GetObjectField(JNIEnv *env, jobject object, JNIFieldInfo *info);

        static void SetObjectField(JNIEnv *env, jobject object, JNIFieldInfo *info, jobject value);
    };
}

#endif //JNITEMPLATE_JNI_UTILS_H
