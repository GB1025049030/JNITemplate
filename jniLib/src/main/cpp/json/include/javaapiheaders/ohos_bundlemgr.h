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
                void Convert(jobject target, InstalledBundleInfo *source) override;
        };

        class TransformInstalledFormResourceInfo : public Transform<InstalledFormResourceInfo> {
            using Transform::Transform;
            public:
                void Extract(jobject source, InstalledFormResourceInfo *target) override;
                void Convert(jobject target, InstalledFormResourceInfo *source) override;
        };

        class TransformInstalledForms : public Transform<InstalledForms> {
            using Transform::Transform;
            public:
                void Extract(jobject source, InstalledForms *target) override;
                void Convert(jobject target, InstalledForms *source) override;
        };

        class TransformInstallShellInfo : public Transform<InstallShellInfo> {
            using Transform::Transform;
            public:
                void Extract(jobject source, InstallShellInfo *target) override;
                void Convert(jobject target, InstallShellInfo *source) override;
        };

        class TransformPackageInstalledStatus : public Transform<PackageInstalledStatus> {
            using Transform::Transform;
            public:
                void Extract(jobject source, PackageInstalledStatus *target) override;
                void Convert(jobject target, PackageInstalledStatus *source) override;
        };

        class TransformShortcutIntent : public Transform<ShortcutIntent> {
            using Transform::Transform;
            public:
                void Extract(jobject source, ShortcutIntent *target) override;
                void Convert(jobject target, ShortcutIntent *source) override;
        };

        enum class InstalledBundleInfo_FIELD_CODE {
            appId = 1,
            bundleName = 2,
            enabledAbilities = 3,
            isSystemApp = 4,
            sourceDir = 5,
            splitNames = 6,
            uid = 7,
            userId = 8,
        };

        enum class InstalledFormResourceInfo_FIELD_CODE {
            abilityName = 9,
            bundleName = 10,
            descriptionId = 11,
            hapSourceDir = 12,
            isJsForm = 13,
            landscapeLayoutIds = 14,
            moduleName = 15,
            name = 16,
            originalBundleName = 17,
            packageName = 18,
            portraitLayoutIds = 19,
        };

        enum class InstalledForms_FIELD_CODE {
            bundleName = 20,
            forms = 21,
            hapSourceDirs = 22,
            originalBundleName = 23,
            packageName = 24,
        };

        enum class InstallShellInfo_FIELD_CODE {
            entryHap = 25,
            featureHaps = 26,
            installerUid = 27,
            installLocation = 28,
            isAppend = 29,
            packageName = 30,
            provisioningBundleName = 31,
            restrictedPermissions = 32,
            userId = 33,
        };

        enum class PackageInstalledStatus_FIELD_CODE {
            shellInstalledDir = 34,
            status = 35,
            statusMessage = 36,
        };

        enum class ShortcutIntent_FIELD_CODE {
            targetBundle = 37,
            targetClass = 38,
        };

        enum class MethodCode_OHOS_BUNDLEMGR {
            // sign: (Ljava/lang/String;)Ljava/lang/String;
            BundleMgrAdapter_getPairBundleName_1 = 1,
            // sign: (Lohos/bundlemgr/InstallShellInfo;)Lohos/bundlemgr/PackageInstalledStatus;
            BundleMgrAdapter_installShellApk_1 = 2,
            // sign: (Ljava/lang/String;IZ)Lohos/bundlemgr/PackageInstalledStatus;
            BundleMgrAdapter_uninstallShellApk_1 = 3,
        };
    }
}

#endif //JNI_OHOS_BUNDLEMGR_H
