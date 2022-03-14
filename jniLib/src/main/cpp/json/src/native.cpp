//
// Created by guobin on 2022/3/8.
//

#include "js_call_android_jni.h"
#include "jkit.h"
#include "jni_log.h"

void nativeInit(JNIEnv *env, jobject thiz) {
    OHOS::DelayedSingleton<OHOS::JSCallAndroidJni>::GetInstance()->NativeInit(env,
                                                                              "ohos_bundlemgr.json");
}

static const JNINativeMethod sMethods[] = {
        {"nativeInit", "()V", reinterpret_cast<void *>(nativeInit)}
};

int Register(JNIEnv *env) {
    jclass clazz = env->FindClass("com/pandon/jnilib/NativeLib");
    if (JNI_OK !=
        env->RegisterNatives(clazz, sMethods, sizeof(sMethods) / sizeof(sMethods[0]))) {
        return JNI_ERR;
    }
    return JNI_OK;
}

//void Test(JNIEnv *env) {
//    jvalue params[2];
//    jintArray arr = env->NewIntArray(2);
//    jint c_arr[2];
//    env->SetIntArrayRegion(arr, 0, 2, c_arr);
//
//    params[0].l = arr;
//    params[1].z = false;
//
//    std::shared_ptr<OHOS::JSCallAndroidJni> test = OHOS::DelayedSingleton<OHOS::JSCallAndroidJni>::GetInstance();
//
//    std::vector<OHOS::cvalue> boolResult;
//    test->CallJavaMethod(
//            static_cast<int32_t>(MethodCode::ohos_app_sample_TestJavaApi_getBoolValue_1),
//            nullptr, nullptr, &boolResult);
//    if (boolResult.at(0).z) {
//        UTILS_LOGD("guobin log : call java ohos_app_sample_TestJavaApi_getBoolValue_1 success");
//    }
//
//    std::vector<OHOS::cvalue> boolArrResult;
//    test->CallJavaMethod(
//            static_cast<int32_t>(MethodCode::ohos_app_sample_TestJavaApi_getBoolValues_1),
//            nullptr, nullptr, &boolArrResult);
//    if (!boolArrResult.empty()) {
//        size_t size = boolArrResult.size();
//        UTILS_LOGD("guobin log : call java boolArrResult size : %zu", size);
//        UTILS_LOGD(
//                "guobin log : call java ohos_app_sample_TestJavaApi_getBoolValues_1 success");
//    }
//
//    std::vector<OHOS::cvalue> byteArrResult;
//    test->CallJavaMethod(
//            static_cast<int32_t>(MethodCode::ohos_app_sample_TestJavaApi_getByteValues_1),
//            nullptr, nullptr, &byteArrResult);
//    if (!byteArrResult.empty()) {
//        size_t size = byteArrResult.size();
//        UTILS_LOGD("guobin log : call java byteArrResult size : %zu", size);
//        UTILS_LOGD(
//                "guobin log : call java ohos_app_sample_TestJavaApi_getByteValues_1 success");
//    }
//
//    std::vector<OHOS::cvalue> charArrResult;
//    test->CallJavaMethod(
//            static_cast<int32_t>(MethodCode::ohos_app_sample_TestJavaApi_getCharValues_1),
//            nullptr, nullptr, &charArrResult);
//    if (!charArrResult.empty()) {
//        size_t size = charArrResult.size();
//        UTILS_LOGD("guobin log : call java charArrResult size : %zu", size);
//        UTILS_LOGD(
//                "guobin log : call java ohos_app_sample_TestJavaApi_getCharValues_1 success");
//    }
//
//    std::vector<OHOS::cvalue> shortArrResult;
//    test->CallJavaMethod(
//            static_cast<int32_t>(MethodCode::ohos_app_sample_TestJavaApi_getShortValues_1),
//            nullptr, nullptr, &shortArrResult);
//    if (!shortArrResult.empty()) {
//        size_t size = shortArrResult.size();
//        UTILS_LOGD("guobin log : call java shortArrResult size : %zu", size);
//        UTILS_LOGD(
//                "guobin log : call java ohos_app_sample_TestJavaApi_getShortValues_1 success");
//    }
//
//    std::vector<OHOS::cvalue> intArrResult;
//    test->CallJavaMethod(
//            static_cast<int32_t>(MethodCode::ohos_app_sample_TestJavaApi_getIntValues_1),
//            nullptr, nullptr, &intArrResult);
//    if (!intArrResult.empty()) {
//        size_t size = intArrResult.size();
//        UTILS_LOGD("guobin log : call java intArrResult size : %zu", size);
//        UTILS_LOGD("guobin log : call java ohos_app_sample_TestJavaApi_getIntValues_1 success");
//    }
//
//    std::vector<OHOS::cvalue> longArrResult;
//    test->CallJavaMethod(
//            static_cast<int32_t>(MethodCode::ohos_app_sample_TestJavaApi_getLongValues_1),
//            nullptr, nullptr, &longArrResult);
//    if (!longArrResult.empty()) {
//        size_t size = longArrResult.size();
//        UTILS_LOGD("guobin log : call java longArrResult size : %zu", size);
//        UTILS_LOGD(
//                "guobin log : call java ohos_app_sample_TestJavaApi_getLongValues_1 success");
//    }
//
//    std::vector<OHOS::cvalue> floatArrResult;
//    test->CallJavaMethod(
//            static_cast<int32_t>(MethodCode::ohos_app_sample_TestJavaApi_getFloatValues_1),
//            nullptr, nullptr, &floatArrResult);
//    if (!floatArrResult.empty()) {
//        size_t size = floatArrResult.size();
//        UTILS_LOGD("guobin log : call java floatArrResult size : %zu", size);
//        UTILS_LOGD(
//                "guobin log : call java ohos_app_sample_TestJavaApi_getFloatValues_1 success");
//    }
//
//    std::vector<OHOS::cvalue> doubleArrResult;
//    test->CallJavaMethod(
//            static_cast<int32_t>(MethodCode::ohos_app_sample_TestJavaApi_getDoubleValues_1),
//            nullptr, nullptr, &doubleArrResult);
//    if (!doubleArrResult.empty()) {
//        size_t size = doubleArrResult.size();
//        UTILS_LOGD("guobin log : call java doubleArrResult size : %zu", size);
//        UTILS_LOGD(
//                "guobin log : call java ohos_app_sample_TestJavaApi_getDoubleValues_1 success");
//    }
//
//    std::vector<std::string> stringArrResult;
//    test->CallJavaMethod(
//            static_cast<int32_t>(MethodCode::ohos_app_sample_TestJavaApi_getStrings_1),
//            nullptr, nullptr, &stringArrResult);
//    if (!stringArrResult.empty()) {
//        size_t size = stringArrResult.size();
//        UTILS_LOGD("guobin log : call java stringArrResult size : %zu", size);
//        if (size > 0) {
//            UTILS_LOGD("guobin log : call java stringArrResult first string : %s",
//                       stringArrResult.at(0).c_str());
//        }
//        UTILS_LOGD("guobin log : call java ohos_app_sample_TestJavaApi_getStrings_1 success");
//    }
//
//    std::string stringResult;
//    test->CallJavaMethod(
//            static_cast<int32_t>(MethodCode::ohos_app_sample_TestJavaApi_getString_1),
//            nullptr, nullptr, &stringResult);
//    UTILS_LOGD("guobin log : call java ohos_app_sample_TestJavaApi_getString_1 success : %s",
//               stringResult.c_str());
//}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    jint result;
    if (vm) {
        result = JNI_VERSION_1_4;
        JNIEnv *env;
        if (JNI_OK != vm->GetEnv((void **) (&env), JNI_VERSION_1_4)) {
            result = JNI_ERR;
        }
        if (JNI_OK == Register(env)) {
            OHOS::DelayedSingleton<OHOS::JSCallAndroidJni>::GetInstance()->InitJavaVm(vm);
        } else {
            result = JNI_ERR;
        }
    } else {
        result = JNI_EINVAL;
    }
    return result;
}
