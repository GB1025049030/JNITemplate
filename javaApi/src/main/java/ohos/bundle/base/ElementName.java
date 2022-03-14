package ohos.bundle.base;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

@JNIClass
public class ElementName {
    @JNIField(sign = "Ljava/lang/String;")
    private String deviceId_;
    @JNIField(sign = "Ljava/lang/String;")
    private String bundleName_;
    @JNIField(sign = "Ljava/lang/String;")
    private String abilityName_;
}
