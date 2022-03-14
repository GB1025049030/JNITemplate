//
// Created by guobin on 2022/3/10.
//

#include "js_call_android_jni.h"
#include "test/transform.h"
#include "jni_utils.h"
#include "javaapiheaders/ohos_bundlemgr.h"

namespace OHOS {
    void InstallShellInfoTransform::Extract(jobject source, InstallShellInfo *target) {
        std::shared_ptr<JSCallAndroidJni> instance = DelayedSingleton<JSCallAndroidJni>::GetInstance();
        instance->GetFieldValue(source, (int32_t) InstallShellInfo_FIELD_CODE::entryHap, &(target->entryHap));
        instance->GetFieldValue(source, (int32_t) InstallShellInfo_FIELD_CODE::isAppend, &(target->isAppend));
        instance->GetFieldValue(source, (int32_t) InstallShellInfo_FIELD_CODE::packageName, &(target->packageName));
        instance->GetFieldValue(source, (int32_t) InstallShellInfo_FIELD_CODE::userId, &(target->userId));
        instance->GetFieldValue(source, (int32_t) InstallShellInfo_FIELD_CODE::installLocation, &(target->installLocation));
        instance->GetFieldValue(source, (int32_t) InstallShellInfo_FIELD_CODE::restrictedPermissions, &(target->restrictedPermissions));
        instance->GetFieldValue(source, (int32_t) InstallShellInfo_FIELD_CODE::provisioningBundleName, &(target->provisioningBundleName));
        instance->GetFieldValue(source, (int32_t) InstallShellInfo_FIELD_CODE::installerUid, &(target->installerUid));
        instance->GetFieldValue(source, (int32_t) InstallShellInfo_FIELD_CODE::featureHaps, &(target->featureHaps));
//        PackageInstalledStatusTransform transform = PackageInstalledStatusTransform(&(target->status));
//        instance->GetFieldValue(source, (int32_t) InstallShellInfo_FIELD_CODE::featureHaps, &transform);
    }

    void InstallShellInfoTransform::Convert(jobject target, InstallShellInfo *source) {
        std::shared_ptr<JSCallAndroidJni> instance = DelayedSingleton<JSCallAndroidJni>::GetInstance();
        instance->SetFieldValue(target, (int32_t) InstallShellInfo_FIELD_CODE::entryHap, &(source->entryHap));
        instance->SetFieldValue(target, (int32_t) InstallShellInfo_FIELD_CODE::isAppend, &(source->isAppend));
        instance->SetFieldValue(target, (int32_t) InstallShellInfo_FIELD_CODE::packageName, &(source->packageName));
        instance->SetFieldValue(target, (int32_t) InstallShellInfo_FIELD_CODE::userId, &(source->userId));
        instance->SetFieldValue(target, (int32_t) InstallShellInfo_FIELD_CODE::installLocation, &(source->installLocation));
        instance->SetFieldValue(target, (int32_t) InstallShellInfo_FIELD_CODE::restrictedPermissions, &(source->restrictedPermissions));
        instance->SetFieldValue(target, (int32_t) InstallShellInfo_FIELD_CODE::provisioningBundleName, &(source->provisioningBundleName));
        instance->SetFieldValue(target, (int32_t) InstallShellInfo_FIELD_CODE::installerUid, &(source->installerUid));
        instance->SetFieldValue(target, (int32_t) InstallShellInfo_FIELD_CODE::featureHaps, &(source->featureHaps));
//        PackageInstalledStatusTransform transform = PackageInstalledStatusTransform(&(source->status));
//        instance->SetFieldValue(target, (int32_t) InstallShellInfo_FIELD_CODE::featureHaps, &transform);
    }

    void PackageInstalledStatusTransform::Extract(jobject source, PackageInstalledStatus *target) {

    }

    void PackageInstalledStatusTransform::Convert(jobject target, PackageInstalledStatus *source) {

    }
}