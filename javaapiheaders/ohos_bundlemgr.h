#ifndef JNI_OHOS_BUNDLEMGR_H
#define JNI_OHOS_BUNDLEMGR_H

#include "jni_transform.h"
#include <string>
#include <jni.h>
#include <vector>

namespace OHOS {
namespace BUNDLEMGR {

#define JSON_FILE_OHOS_BUNDLEMGR "ohos_bundlemgr.json"

#define JAVA_BEAN_InstalledBundleInfo "ohos/bundlemgr/InstalledBundleInfo"
#define JAVA_BEAN_InstalledFormResourceInfo "ohos/bundlemgr/InstalledFormResourceInfo"
#define JAVA_BEAN_InstalledForms "ohos/bundlemgr/InstalledForms"
#define JAVA_BEAN_InstallShellInfo "ohos/bundlemgr/InstallShellInfo"
#define JAVA_BEAN_PackageInstalledStatus "ohos/bundlemgr/PackageInstalledStatus"
#define JAVA_BEAN_ShortcutIntent "ohos/bundlemgr/ShortcutIntent"

using namespace TEMPLATE;

struct InstalledFormResourceInfo;

struct InstalledBundleInfo {
    std::string appId;
    std::string bundleName;
    std::vector<std::string> enabledAbilities;
    uint8_t isSystemApp;
    std::string sourceDir;
    std::vector<std::string> splitNames;
    int32_t uid;
    int32_t userId;
};

struct InstalledFormResourceInfo {
    std::string abilityName;
    std::string bundleName;
    int32_t descriptionId;
    std::string hapSourceDir;
    uint8_t isJsForm;
    std::vector<int32_t> landscapeLayoutIds;
    std::string moduleName;
    std::string name;
    std::string originalBundleName;
    std::string packageName;
    std::vector<int32_t> portraitLayoutIds;
};

struct InstalledForms {
    std::string bundleName;
    std::vector<InstalledFormResourceInfo> forms;
    std::vector<std::string> hapSourceDirs;
    std::string originalBundleName;
    std::string packageName;
};

struct InstallShellInfo {
    std::string entryHap;
    std::vector<std::string> featureHaps;
    int32_t installerUid;
    int32_t installLocation;
    uint8_t isAppend;
    std::string packageName;
    std::string provisioningBundleName;
    std::vector<std::string> restrictedPermissions;
    int32_t userId;
};

struct PackageInstalledStatus {
    std::string shellInstalledDir;
    int32_t status;
    std::string statusMessage;
};

struct ShortcutIntent {
    std::string targetBundle;
    std::string targetClass;
};

class TransformInstalledBundleInfo : public Transform<InstalledBundleInfo> {
    using Transform::Transform;
    public:
        void Extract(jobject source, InstalledBundleInfo *target) override;
        void Convert(jobject target, const InstalledBundleInfo *source) override;
        jobject CreateJavaObject(const InstalledBundleInfo *source) override;
        void Release() override;
};

class TransformInstalledFormResourceInfo : public Transform<InstalledFormResourceInfo> {
    using Transform::Transform;
    public:
        void Extract(jobject source, InstalledFormResourceInfo *target) override;
        void Convert(jobject target, const InstalledFormResourceInfo *source) override;
        jobject CreateJavaObject(const InstalledFormResourceInfo *source) override;
        void Release() override;
};

class TransformInstalledForms : public Transform<InstalledForms> {
    using Transform::Transform;
    public:
        void Extract(jobject source, InstalledForms *target) override;
        void Convert(jobject target, const InstalledForms *source) override;
        jobject CreateJavaObject(const InstalledForms *source) override;
        void Release() override;
};

class TransformInstallShellInfo : public Transform<InstallShellInfo> {
    using Transform::Transform;
    public:
        void Extract(jobject source, InstallShellInfo *target) override;
        void Convert(jobject target, const InstallShellInfo *source) override;
        jobject CreateJavaObject(const InstallShellInfo *source) override;
        void Release() override;
};

class TransformPackageInstalledStatus : public Transform<PackageInstalledStatus> {
    using Transform::Transform;
    public:
        void Extract(jobject source, PackageInstalledStatus *target) override;
        void Convert(jobject target, const PackageInstalledStatus *source) override;
        jobject CreateJavaObject(const PackageInstalledStatus *source) override;
        void Release() override;
};

class TransformShortcutIntent : public Transform<ShortcutIntent> {
    using Transform::Transform;
    public:
        void Extract(jobject source, ShortcutIntent *target) override;
        void Convert(jobject target, const ShortcutIntent *source) override;
        jobject CreateJavaObject(const ShortcutIntent *source) override;
        void Release() override;
};

enum class InstalledBundleInfo_FIELD_CODE {
    appId = 49,
    bundleName = 50,
    enabledAbilities = 51,
    isSystemApp = 52,
    sourceDir = 53,
    splitNames = 54,
    uid = 55,
    userId = 56,
};

enum class InstalledFormResourceInfo_FIELD_CODE {
    abilityName = 57,
    bundleName = 58,
    descriptionId = 59,
    hapSourceDir = 60,
    isJsForm = 61,
    landscapeLayoutIds = 62,
    moduleName = 63,
    name = 64,
    originalBundleName = 65,
    packageName = 66,
    portraitLayoutIds = 67,
};

enum class InstalledForms_FIELD_CODE {
    bundleName = 68,
    forms = 69,
    hapSourceDirs = 70,
    originalBundleName = 71,
    packageName = 72,
};

enum class InstallShellInfo_FIELD_CODE {
    entryHap = 73,
    featureHaps = 74,
    installerUid = 75,
    installLocation = 76,
    isAppend = 77,
    packageName = 78,
    provisioningBundleName = 79,
    restrictedPermissions = 80,
    userId = 81,
};

enum class PackageInstalledStatus_FIELD_CODE {
    shellInstalledDir = 82,
    status = 83,
    statusMessage = 84,
};

enum class ShortcutIntent_FIELD_CODE {
    targetBundle = 85,
    targetClass = 86,
};

enum class MethodCode_OHOS_BUNDLEMGR {

    /**
     * sign: (Ljava/lang/String;)Ljava/lang/String;
     * isStaticMethod: true
     * isNonvirtualMethod: false
     */
    BundleMgrAdapter_getPairBundleName_1 = 11,

    /**
     * sign: (Lohos/bundlemgr/InstallShellInfo;)Lohos/bundlemgr/PackageInstalledStatus;
     * isStaticMethod: true
     * isNonvirtualMethod: false
     */
    BundleMgrAdapter_installShellApk_1 = 12,

    /**
     * sign: (Ljava/lang/String;IZ)Lohos/bundlemgr/PackageInstalledStatus;
     * isStaticMethod: true
     * isNonvirtualMethod: false
     */
    BundleMgrAdapter_uninstallShellApk_1 = 13,
};

} // namespace BUNDLEMGR
} // namespace OHOS

#endif //JNI_OHOS_BUNDLEMGR_H
