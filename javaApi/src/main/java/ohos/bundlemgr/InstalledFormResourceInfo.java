package ohos.bundlemgr;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

@JNIClass
class InstalledFormResourceInfo {
    @JNIField(sign = "Ljava/lang/String;")
    String abilityName;
    @JNIField(sign = "Ljava/lang/String;")
    String bundleName;
    @JNIField(sign = "I")
    int descriptionId;
    @JNIField(sign = "Ljava/lang/String;")
    String hapSourceDir;
    @JNIField(sign = "Z")
    boolean isJsForm;
    @JNIField(sign = "[I")
    int[] landscapeLayoutIds;
    @JNIField(sign = "Ljava/lang/String;")
    String moduleName;
    @JNIField(sign = "Ljava/lang/String;")
    String name;
    @JNIField(sign = "Ljava/lang/String;")
    String originalBundleName;
    @JNIField(sign = "Ljava/lang/String;")
    String packageName;
    @JNIField(sign = "[I")
    int[] portraitLayoutIds;

    InstalledFormResourceInfo() {
        this(null);
    }

    InstalledFormResourceInfo(InstalledFormResourceInfo installedFormResourceInfo) {
        this.descriptionId = 0;
        if (installedFormResourceInfo != null) {
            this.packageName = installedFormResourceInfo.packageName;
            this.hapSourceDir = installedFormResourceInfo.hapSourceDir;
            this.bundleName = installedFormResourceInfo.bundleName;
            this.originalBundleName = installedFormResourceInfo.originalBundleName;
            this.moduleName = installedFormResourceInfo.moduleName;
            this.abilityName = installedFormResourceInfo.abilityName;
            this.name = installedFormResourceInfo.name;
            this.isJsForm = installedFormResourceInfo.isJsForm;
            this.descriptionId = installedFormResourceInfo.descriptionId;
            int[] landscapeLayoutIds = installedFormResourceInfo.landscapeLayoutIds;
            if (landscapeLayoutIds != null) {
                this.landscapeLayoutIds = landscapeLayoutIds.clone();
            }
            int[] portraitLayoutIds = installedFormResourceInfo.portraitLayoutIds;
            if (portraitLayoutIds != null) {
                this.portraitLayoutIds = portraitLayoutIds.clone();
            }
        }
    }
}
