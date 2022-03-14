package ohos.bundlemgr;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

@JNIClass
class InstalledForms {
    @JNIField(sign = "Ljava/lang/String;")
    String bundleName;
    @JNIField(sign = "[Lohos/bundlemgr/InstalledFormResourceInfo;")
    InstalledFormResourceInfo[] forms;
    @JNIField(sign = "[Ljava/lang/String;")
    String[] hapSourceDirs;
    @JNIField(sign = "Ljava/lang/String;")
    String originalBundleName;
    @JNIField(sign = "Ljava/lang/String;")
    String packageName;

    InstalledForms() {
    }
}
