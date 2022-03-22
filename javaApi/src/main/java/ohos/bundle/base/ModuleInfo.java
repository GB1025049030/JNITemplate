package ohos.bundle.base;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

@JNIClass
public class ModuleInfo{
    @JNIField(sign = "Ljava/lang/String;")
    private String moduleName;
    @JNIField(sign = "Ljava/lang/String;")
    private String moduleSourceDir;
}
