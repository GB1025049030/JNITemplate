package ohos.bundle.base;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

@JNIClass
public class ApplicationInfo {
    @JNIField(sign = "Ljava/lang/String;")
    private String name;
    @JNIField(sign = "Ljava/lang/String;")
    private String bundleName;
    @JNIField(sign = "Ljava/lang/String;")
    private String description;
    @JNIField(sign = "Ljava/lang/String;")
    private String icon;
    @JNIField(sign = "Ljava/lang/String;")
    private String label;
    @JNIField(sign = "Ljava/lang/String;")
    private String deviceId;
    @JNIField(sign = "Ljava/lang/String;")
    private String signatureKey;
    @JNIField(sign = "Ljava/lang/String;")
    private String process;
    @JNIField(sign = "Ljava/lang/String;")
    private String entryDir;
    @JNIField(sign = "Ljava/lang/String;")
    private String codePath;
    @JNIField(sign = "Ljava/lang/String;")
    private String dataDir;
    @JNIField(sign = "Ljava/lang/String;")
    private String dataBaseDir;
    @JNIField(sign = "Ljava/lang/String;")
    private String cacheDir;
    @JNIField(sign = "Z")
    private boolean systemApp;
    @JNIField(sign = "Z")
    private boolean isLauncherApp;
    @JNIField(sign = "Z")
    private boolean enabled;
    @JNIField(sign = "I")
    private int supportedModes;
    @JNIField(sign = "I")
    private int labelId;
    @JNIField(sign = "I")
    private int iconId;
    @JNIField(sign = "I")
    private int descriptionId;
    @JNIField(sign = "I")
    private int flags;
//    private List<String> permissions = new ArrayList<>(0);
//    private List<String> moduleSourceDirs = new ArrayList<>(0);
//    private List<ModuleInfo> moduleInfos = new ArrayList<>(0);
}
