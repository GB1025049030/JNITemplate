package ohos.bundlemgr;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

@JNIClass
public class ShortcutIntent {
    @JNIField(sign = "Ljava/lang/String;")
    private final String targetBundle;
    @JNIField(sign = "Ljava/lang/String;")
    private final String targetClass;

    public ShortcutIntent(String targetBundle, String targetClass) {
        this.targetBundle = targetBundle;
        this.targetClass = targetClass;
    }

    public String getTargetBundle() {
        return this.targetBundle;
    }

    public String getTargetClass() {
        return this.targetClass;
    }
}
