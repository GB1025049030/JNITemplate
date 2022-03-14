package ohos.app;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIMethod;

@JNIClass
public class AbilityManager {
    @JNIMethod(sign = "(Ljava/lang/String;)V")
    public void killProcessesByBundleName(String str) {
    }
}
