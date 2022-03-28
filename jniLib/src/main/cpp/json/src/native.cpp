//
// Created by APITest on 2022/3/8.
//

#include "native.h"

#include <javaapiheaders/ohos_apitest.h>

#include "jkit.h"
#include "jni_log.h"
#include "js_call_android_jni.h"

void nativeInit(JNIEnv *env, jobject thiz) {
    OHOS::DelayedSingleton<OHOS::APITEST::APITest>::GetInstance()->NativeInit(
        env);
}

static const JNINativeMethod sMethods[] = {
    {"nativeInit", "()V", reinterpret_cast<void *>(nativeInit)}};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    jint result;
    if (vm) {
        result = JNI_VERSION_1_4;
        JNIEnv *env;
        if (JNI_OK != vm->GetEnv((void **)(&env), JNI_VERSION_1_4)) {
            result = JNI_ERR;
        }
        if (JNI_OK ==
            OHOS::DelayedSingleton<OHOS::APITEST::APITest>::GetInstance()
                ->Register(env)) {
            OHOS::DelayedSingleton<OHOS::APITEST::APITest>::GetInstance()
                ->InitJavaVm(vm);
        } else {
            result = JNI_ERR;
        }
    } else {
        result = JNI_EINVAL;
    }
    return result;
}

namespace OHOS {
namespace APITEST {
APITest::APITest() {}

APITest::~APITest() {}

int APITest::InitJavaVm(JavaVM *vm) {
    JNI_LOGI("APITest : InitJavaVm : begin");
    sJSCallAndroidJniPtr = DelayedSingleton<JSCallAndroidJni>::GetInstance();
    if (auto tmp = sJSCallAndroidJniPtr.lock()) {
        JNI_LOGI("APITest : InitJavaVm : work");
        tmp->InitJavaVm(vm);
    }
    JNI_LOGI("APITest : InitJavaVm : end");
    return JNI_OK;
}

int APITest::Register(JNIEnv *env) {
    jclass clazz = env->FindClass("com/pandon/jnilib/NativeLib");
    if (JNI_OK !=
        env->RegisterNatives(clazz, sMethods,
                             sizeof(sMethods) / sizeof(sMethods[0]))) {
        return JNI_ERR;
    }
    return JNI_OK;
}

void APITest::NativeInit(JNIEnv *env) {
    if (env) {
        JNI_LOGI("APITest : NativeInit : begin");
        if (auto tmp = sJSCallAndroidJniPtr.lock()) {
            JNI_LOGI("APITest : NativeInit : work");
            tmp->NativeInit(env, JSON_FILE_OHOS_APITEST);
        }
        JNI_LOGI("APITest : NativeInit : end");
    }
    Test(env);
}

void APITest::Test(JNIEnv *env) {
    ClassRoom room;
    room.name = "xxx class";
    Student ming;
    ming.name = "ming";
    ming.age = 18;
    room.students.emplace_back(ming);
    Student juan;
    juan.name = "juan";
    juan.age = 19;
    room.students.emplace_back(juan);
    AddClassRoom(room);
}

void APITest::AddClassRoom(ClassRoom room) {
    JNI_LOGI("APITest : AddClassRoom : begin");
    if (auto tmp = sJSCallAndroidJniPtr.lock()) {
        TransformClassRoom transformClassRoom =
            TransformClassRoom(JAVA_BEAN_ClassRoom);
        jvalue params[1];
        tmp->ConvertJavaObject(&room, &(params[0].l), &transformClassRoom);
        tmp->CallJavaMethod(
            (int32_t)MethodCode_OHOS_APITEST::SchoolManager_addClassRoom_1,
            nullptr, params);
    }
    JNI_LOGI("APITest : AddClassRoom : end");
}

void TransformStudent::Extract(jobject source, Student *target) {
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    instance->GetFieldValue(source,
                            static_cast<int32_t>(Student_FIELD_CODE::name),
                            &(target->name));
    instance->GetFieldValue(
        source, static_cast<int32_t>(Student_FIELD_CODE::age), &(target->age));
}

void TransformStudent::Convert(jobject target, Student *source) {
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    instance->SetFieldValue(target,
                            static_cast<int32_t>(Student_FIELD_CODE::name),
                            &(source->name));
    instance->SetFieldValue(
        target, static_cast<int32_t>(Student_FIELD_CODE::age), &(source->age));
    JNI_LOGI("TransformStudent : CreateObject : name = %s",
             source->name.c_str());
}

jobject TransformStudent::CreateObject(Student *source) {
    std::shared_ptr<JSCallAndroidJni> instance =
            DelayedSingleton<JSCallAndroidJni>::GetInstance();
    return instance->NewObject(JAVA_BEAN_Student);
}

void TransformClassRoom::Extract(jobject source, ClassRoom *target) {
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    instance->GetFieldValue(source,
                            static_cast<int32_t>(ClassRoom_FIELD_CODE::name),
                            &(target->name));
    TransformStudent transformStudent = TransformStudent(JAVA_BEAN_Student);
    instance->GetFieldValue(
        source, static_cast<int32_t>(ClassRoom_FIELD_CODE::students),
        &(target->students), &transformStudent);
}

void TransformClassRoom::Convert(jobject target, ClassRoom *source) {
    JNI_LOGI("TransformClassRoom : CreateObject : begin");
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    instance->SetFieldValue(target,
                            static_cast<int32_t>(ClassRoom_FIELD_CODE::name),
                            &(source->name));
    TransformStudent transformStudent = TransformStudent(JAVA_BEAN_Student);
    instance->SetFieldValue(
        target, static_cast<int32_t>(ClassRoom_FIELD_CODE::students),
        &(source->students), &transformStudent);
    JNI_LOGI("TransformClassRoom : CreateObject : end");
}

jobject TransformClassRoom::CreateObject(ClassRoom *source) {
    std::shared_ptr<JSCallAndroidJni> instance =
            DelayedSingleton<JSCallAndroidJni>::GetInstance();
    return instance->NewObject(JAVA_BEAN_ClassRoom);
}
}  // namespace APITEST
}  // namespace OHOS
