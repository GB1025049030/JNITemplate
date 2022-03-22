//
// Created by guobin on 2022/3/14.
//

#ifndef JNITEMPLATE_NATIVE_H
#define JNITEMPLATE_NATIVE_H

#include <jni.h>

#include <memory>

#include "javaapiheaders/ohos_apitest.h"
#include "js_call_android_jni.h"

namespace OHOS {
namespace APITEST {

using namespace APITEST;

class APITest {
    APITest();

    friend DelayedSingleton<APITest>;

public:
    ~APITest();

    int InitJavaVm(JavaVM *vm);

    int Register(JNIEnv *env);

    void NativeInit(JNIEnv *env);

    void Test(JNIEnv *env);

    void AddClassRoom(ClassRoom room);

private:
    std::weak_ptr<JSCallAndroidJni> sJSCallAndroidJniPtr;
};
}  // namespace APITEST
}  // namespace OHOS

#endif  // JNITEMPLATE_NATIVE_H
