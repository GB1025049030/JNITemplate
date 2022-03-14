//
// Created by guobin on 2022/3/14.
//

#ifndef JNITEMPLATE_NATIVE_H
#define JNITEMPLATE_NATIVE_H

#include <jni.h>
#include <memory>
#include "js_call_android_jni.h"
#include "javaapiheaders/ohos_bundlemgr.h"

namespace OHOS {
    class APITest {
        APITest();

        friend DelayedSingleton<APITest>;
    public:
        ~APITest();

        int InitJavaVm(JavaVM *vm);

        int Register(JNIEnv *env);

        void NativeInit(JNIEnv *env);

        void Test(JNIEnv *env);

        int InstallShellApk(InstallShellInfo *shellInfo, PackageInstalledStatus *status);

        int UnInstallShellApk(std::string packageName, int userId, bool isAppend,
                              PackageInstalledStatus *status);

        void GetPairBundleName(const std::string &packageName, std::string *bundleName);

        void GetPairID(int32_t id, int32_t* newID);

    private:
        std::weak_ptr<JSCallAndroidJni> sJSCallAndroidJniPtr;
    };

    class InstallShellInfoTransform : public Transform<InstallShellInfo> {
        using Transform::Transform;

    public:
        void Extract(jobject source, InstallShellInfo *target) override;

        void Convert(jobject target, InstallShellInfo *source) override;
    };

    class PackageInstalledStatusTransform : public Transform<PackageInstalledStatus> {
        using Transform::Transform;

    public:
        void Extract(jobject source, PackageInstalledStatus *target) override;

        void Convert(jobject target, PackageInstalledStatus *source) override;
    };
}

#endif //JNITEMPLATE_NATIVE_H
