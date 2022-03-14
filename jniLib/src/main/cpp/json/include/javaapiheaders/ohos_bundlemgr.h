#ifndef JNI_OHOS_BUNDLEMGR_H
#define JNI_OHOS_BUNDLEMGR_H

#include <string>
#include <jni.h>
#include <vector>

#define JSON_CONFIG_FILE_OHOS_BUNDLEMGR "ohos_bundlemgr.json"

enum class MethodCode_OHOS_BUNDLEMGR {
    // sign: (Lohos/bundlemgr/InstallShellInfo;)Lohos/bundlemgr/PackageInstalledStatus;
    BundleMgrAdapter_installShellApk_1 = 1,
    // sign: (Ljava/lang/String;IZ)Lohos/bundlemgr/PackageInstalledStatus;
    BundleMgrAdapter_uninstallShellApk_1 = 2,
    // sign: (Ljava/lang/String;)Ljava/lang/String;
    BundleMgrAdapter_getPairBundleName_1 = 3,
};
struct InstallShellInfo {
    std::string entryHap;
    uint8_t isAppend;
    std::string packageName;
    int32_t userId;
    int32_t installLocation;
    std::vector<std::string> restrictedPermissions;
    std::string provisioningBundleName;
    int32_t installerUid;
    std::vector<std::string> featureHaps;
};

void convertC2JInstallShellInfo(InstallShellInfo data, jobject* obj);
void convertJ2CInstallShellInfo(jobject obj, InstallShellInfo* data);

enum class InstallShellInfo_FIELD_CODE {
    entryHap = 1,
    isAppend = 2,
    packageName = 3,
    userId = 4,
    installLocation = 5,
    restrictedPermissions = 6,
    provisioningBundleName = 7,
    installerUid = 8,
    featureHaps = 9,
};
struct PackageInstalledStatus {
    std::string shellInstalledDir;
    int32_t status;
    std::string statusMessage;
};

void convertC2JPackageInstalledStatus(PackageInstalledStatus data, jobject* obj);
void convertJ2CPackageInstalledStatus(jobject obj, PackageInstalledStatus* data);

enum class PackageInstalledStatus_FIELD_CODE {
    shellInstalledDir = 10,
    status = 11,
    statusMessage = 12,
};

#endif //JNI_OHOS_BUNDLEMGR_H
