package ohos.bundlemgr;

import android.content.pm.ActivityInfo;
import android.content.pm.PackageInfo;
import android.content.pm.ProviderInfo;
import android.content.pm.ServiceInfo;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

import java.util.ArrayList;

@JNIClass
public class InstalledBundleInfo {
    @JNIField(sign = "Ljava/lang/String;")
    String appId;
    @JNIField(sign = "Ljava/lang/String;")
    String bundleName;
    @JNIField(sign = "[Ljava/lang/String;")
    String[] enabledAbilities = new String[0];
    @JNIField(sign = "Z")
    boolean isSystemApp;
    @JNIField(sign = "Ljava/lang/String;")
    String sourceDir;
    @JNIField(sign = "[Ljava/lang/String;")
    String[] splitNames;
    @JNIField(sign = "I")
    int uid;
    @JNIField(sign = "I")
    int userId;

    public InstalledBundleInfo(PackageInfo packageInfo, String appId, int userId) {
        this.splitNames = new String[0];
        this.uid = -1;
        this.userId = 0;
        this.isSystemApp = false;
        if (packageInfo != null) {
            this.bundleName = packageInfo.packageName;
            if (packageInfo.splitNames != null) {
                this.splitNames = packageInfo.splitNames.clone();
            }
            if (packageInfo.applicationInfo != null) {
                this.uid = packageInfo.applicationInfo.uid;
                this.sourceDir = getBundleSourceDir(packageInfo.applicationInfo.sourceDir);
                this.isSystemApp = packageInfo.applicationInfo.isSystemApp();
            }
        }
        this.userId = userId;
        this.appId = appId;
        getEnabledAbilities(packageInfo);
    }

    private String getBundleSourceDir(String sourceDir) {
        int lastIndexOf = sourceDir.lastIndexOf(47);
        return lastIndexOf != -1 ? sourceDir.substring(0, lastIndexOf) : sourceDir;
    }

    private void getEnabledAbilities(PackageInfo packageInfo) {
        ArrayList<String> arrayList = new ArrayList<>();
        if (packageInfo != null) {
            if (packageInfo.activities != null) {
                for (ActivityInfo activityInfo : packageInfo.activities) {
                    arrayList.add(activityInfo.name);
                }
            }
            if (packageInfo.services != null) {
                for (ServiceInfo serviceInfo : packageInfo.services) {
                    arrayList.add(serviceInfo.name);
                }
            }
            if (packageInfo.providers != null) {
                for (ProviderInfo providerInfo : packageInfo.providers) {
                    arrayList.add(providerInfo.name);
                }
            }
            int size = arrayList.size();
            if (size > 0) {
                String[] strArr = new String[size];
                arrayList.toArray(strArr);
                this.enabledAbilities = strArr.clone();
            }
        }
    }
}
