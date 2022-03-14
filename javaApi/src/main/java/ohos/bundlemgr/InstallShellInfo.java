package ohos.bundlemgr;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@JNIClass
public class InstallShellInfo {
    @JNIField(sign = "Ljava/lang/String;")
    private final String entryHap;
    @JNIField(sign = "Z")
    private final boolean isAppend;
    @JNIField(sign = "Ljava/lang/String;")
    private final String packageName;
    @JNIField(sign = "I")
    private final int userId;
    @JNIField(sign = "I")
    private final int installLocation = 1;
    @JNIField(sign = "[Ljava/lang/String;")
    private final String[] restrictedPermissions = new String[0];
    @JNIField(sign = "Ljava/lang/String;")
    private final String provisioningBundleName = "";
    @JNIField(sign = "I")
    private final int installerUid = -1;
    @JNIField(sign = "[Ljava/lang/String;")
    private String[] featureHaps;

    public InstallShellInfo(String packageName, String entryHap, String[] featureHaps, int userId, boolean isAppend) {
        this.packageName = packageName;
        this.entryHap = entryHap;
        if (featureHaps != null) {
            this.featureHaps = featureHaps.clone();
        }
        this.userId = userId;
        this.isAppend = isAppend;
    }

    public String getPackageName() {
        return this.packageName;
    }

    public String getEntryHap() {
        return this.entryHap;
    }

    public String[] getFeatureHaps() {
        return featureHaps != null ? featureHaps.clone() : new String[0];
    }

    public int getUserId() {
        return this.userId;
    }

    public boolean isAppend() {
        return this.isAppend;
    }

    public int getInstallLocation() {
        return this.installLocation;
    }

    public List<String> getRestrictedPermissions() {
        return restrictedPermissions == null || restrictedPermissions.length == 0 ? new ArrayList<>() : Arrays.asList(restrictedPermissions);
    }

    public String getProvisioningBundleName() {
        return this.provisioningBundleName;
    }

    public int getInstallerUid() {
        return this.installerUid;
    }
}
