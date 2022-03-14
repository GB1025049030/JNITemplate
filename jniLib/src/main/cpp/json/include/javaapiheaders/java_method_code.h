#ifndef JNI_METHOD_CODE_H
#define JNI_METHOD_CODE_H

enum class MethodCode {
    // sign: (Lohos/bundlemgr/InstallShellInfo;)Lohos/bundlemgr/PackageInstalledStatus;
    ohos_bundlemgr_BundleMgrAdapter_installShellApk_1 = 2,
    // sign: (Ljava/lang/String;IZ)Lohos/bundlemgr/PackageInstalledStatus;
    ohos_bundlemgr_BundleMgrAdapter_uninstallShellApk_1 = 3,
    // sign: (Ljava/lang/String;)Ljava/lang/String;
    ohos_bundlemgr_BundleMgrAdapter_getPairBundleName_1 = 4,
    // sign: (Ljava/lang/String;)V
    ohos_app_AbilityManager_killProcessesByBundleName_1 = 1,
};

#endif //JNI_METHOD_CODE_H
