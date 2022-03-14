//
// Created by guobin on 2022/3/10.
//

#ifndef JNITEMPLATE_TRANSFORM_H
#define JNITEMPLATE_TRANSFORM_H

#include "../jni_transform.h"
#include "../javaapiheaders/ohos_bundlemgr.h"

namespace OHOS {
    class InstallShellInfoTransform : public Transform<InstallShellInfo> {
        using Transform::Transform;

        void Extract(jobject source, InstallShellInfo* target) override;

        void Convert(jobject target, InstallShellInfo* source) override;
    };

    class PackageInstalledStatusTransform : public Transform<PackageInstalledStatus> {
        using Transform::Transform;

        void Extract(jobject source, PackageInstalledStatus* target) override;

        void Convert(jobject target, PackageInstalledStatus* source) override;
    };
}

#endif //JNITEMPLATE_TRANSFORM_H
