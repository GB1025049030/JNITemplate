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
        if (JNI_OK == OHOS::APITEST::APITest::Register(env)) {
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
APITest::APITest() = default;

APITest::~APITest() = default;

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
            //tmp->NativeInit(env, JSON_FILE_OHOS_BUNDLEMGR);
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

    std::vector<ClassRoom> rooms;
    ClassRoom item;
    item.name = "LiClass";
    Student li;
    li.name = "li";
    li.age = 25;
    item.students.emplace_back(li);
    Books books{4, 5};
    item.books.insert(std::pair<int32_t, Books>(1, books));
    rooms.emplace_back(item);
    JNI_LOGI("Test : Show");
    for (const auto &r : item.students) {
        JNI_LOGI("Test : rooms : %s", r.name.c_str());
    }
    AddClassRooms(rooms);

    std::vector<ClassRoom> resultRooms;
    GetClassRooms(&resultRooms);
    std::map<int, Books> resultBooks;
    GetFirstBooks(&resultBooks);

    ClassRoom resultRoom;
    GetClassRoomFirst(&resultRoom);
}

void APITest::GetClassRooms(std::vector<ClassRoom> *rooms) {
    JNI_LOGI("APITest : GetClassRooms : begin");
    if (auto tmp = sJSCallAndroidJniPtr.lock()) {
        TransformClassRoom transformClassRoom =
            TransformClassRoom(JAVA_BEAN_ClassRoom);
        tmp->CallJavaMethod(
            (int32_t)MethodCode_OHOS_APITEST::SchoolManager_getClassRooms_1,
            nullptr, nullptr, rooms, &transformClassRoom);
        for (const ClassRoom &room : *rooms) {
            JNI_LOGI("guobin : GetClassRooms : room : %s", room.name.c_str());
        }
    }
    JNI_LOGI("APITest : GetClassRooms : end");
}

    void APITest::GetClassRoomFirst(ClassRoom* room) {
        JNI_LOGI("APITest : GetClassRoomFirst : begin");
        if (auto tmp = sJSCallAndroidJniPtr.lock()) {
            TransformClassRoom transformClassRoom =
                    TransformClassRoom(JAVA_BEAN_ClassRoom);
            jobject source;
            tmp->CallJavaMethod((int32_t)MethodCode_OHOS_APITEST::SchoolManager_getInstance_1,
                                nullptr, nullptr, &source);
            if (source) {
                tmp->CallJavaMethod(
                        (int32_t)MethodCode_OHOS_APITEST::SchoolManager_getClassRoomFirst_1,
                        source, nullptr, room, &transformClassRoom);
                JNI_LOGI("guobin : GetClassRoomFirst : room : %s", room->name.c_str());
            }
        }
        JNI_LOGI("APITest : GetClassRooms : end");
    }

void APITest::GetFirstBooks(std::map<int, Books> *books) {
    JNI_LOGI("APITest : GetFirstBooks : begin");
    if (auto tmp = sJSCallAndroidJniPtr.lock()) {
        TransformInt transformInt = TransformInt(JAVA_LANG_INTEGER);
        TransformBooks transformBooks = TransformBooks(JAVA_BEAN_Books);
        tmp->CallJavaMethod(
            (int32_t)MethodCode_OHOS_APITEST::SchoolManager_getFirstBooks_1,
            nullptr, nullptr, books, &transformInt, &transformBooks);
        if (books) {
            for (auto it = books->begin(); it != books->end(); it++) {
                JNI_LOGI("guobin : GetFirstBooks : first : %d, second : %d",
                         it->first, it->second.chinese);
            }
        }
    }
    JNI_LOGI("APITest : GetFirstBooks : end");
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

void APITest::AddClassRooms(std::vector<ClassRoom> rooms) {
    JNI_LOGI("APITest : AddClassRooms : begin");
    if (auto tmp = sJSCallAndroidJniPtr.lock()) {
        TransformClassRoom transformClassRoom =
            TransformClassRoom(JAVA_BEAN_ClassRoom);
        jvalue params[1];
        tmp->ConvertJavaList(&rooms, &(params[0].l), &transformClassRoom);
        tmp->CallJavaMethod(
            (int32_t)MethodCode_OHOS_APITEST::SchoolManager_addClassRooms_1,
            nullptr, params);
    }
    JNI_LOGI("APITest : AddClassRooms : end");
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

void TransformStudent::Convert(jobject target, const Student *source) {
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

jobject TransformStudent::CreateObject(const Student *source) {
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    return instance->NewObject(JAVA_BEAN_Student);
}

void TransformStudent::Release() { Transform::Release(); }

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

    TransformInt transformInt = TransformInt(JAVA_LANG_INTEGER);
    TransformBooks transformBooks = TransformBooks(JAVA_BEAN_Books);
    instance->GetFieldValue(source,
                            static_cast<int32_t>(ClassRoom_FIELD_CODE::books),
                            &(target->books), &transformInt, &transformBooks);
}

void TransformClassRoom::Convert(jobject target, const ClassRoom *source) {
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

    TransformInt transformInt = TransformInt(JAVA_LANG_INTEGER);
    TransformBooks transformBooks = TransformBooks(JAVA_BEAN_Books);
    instance->SetFieldValue(target,
                            static_cast<int32_t>(ClassRoom_FIELD_CODE::books),
                            &(source->books), &transformInt, &transformBooks);
    JNI_LOGI("TransformClassRoom : CreateObject : end");
}

jobject TransformClassRoom::CreateObject(const ClassRoom *source) {
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    return instance->NewObject(JAVA_BEAN_ClassRoom);
}

void TransformClassRoom::Release() { Transform::Release(); }

void TransformBooks::Extract(jobject source, Books *target) {
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    instance->GetFieldValue(source,
                            static_cast<int32_t>(Books_FIELD_CODE::chinese),
                            &(target->chinese));
    instance->GetFieldValue(
        source, static_cast<int32_t>(Books_FIELD_CODE::math), &(target->math));
}

void TransformBooks::Convert(jobject target, const Books *source) {
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    instance->SetFieldValue(target,
                            static_cast<int32_t>(Books_FIELD_CODE::chinese),
                            &(source->chinese));
    instance->SetFieldValue(
        target, static_cast<int32_t>(Books_FIELD_CODE::math), &(source->math));
}

jobject TransformBooks::CreateObject(const Books *source) {
    std::shared_ptr<JSCallAndroidJni> instance =
        DelayedSingleton<JSCallAndroidJni>::GetInstance();
    return instance->NewObject(JAVA_BEAN_Books);
}

void TransformBooks::Release() { Transform::Release(); }
}  // namespace APITEST
}  // namespace OHOS
