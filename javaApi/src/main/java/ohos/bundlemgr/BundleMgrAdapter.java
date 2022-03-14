package ohos.bundlemgr;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIMethod;

@JNIClass
public class BundleMgrAdapter {
    @JNIMethod(sign = "(Lohos/bundlemgr/InstallShellInfo;)Lohos/bundlemgr/PackageInstalledStatus;", isStaticMethod = true)
    public static PackageInstalledStatus installShellApk(InstallShellInfo installShellInfo) {
        return null;
    }

    @JNIMethod(sign = "(Ljava/lang/String;IZ)Lohos/bundlemgr/PackageInstalledStatus;", isStaticMethod = true)
    public static PackageInstalledStatus uninstallShellApk(String packageName, int userId, boolean isAppend) {
        return null;
    }

    @JNIMethod(sign = "(Ljava/lang/String;)Ljava/lang/String;", isStaticMethod = true)
    public static String getPairBundleName(String packageName) {
        return null;
    }
}
