package ohos.apitest;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

@JNIClass
public class Student {
    @JNIField(sign = "Ljava/lang/String;")
    public String name;
    @JNIField(sign = "I")
    public int age;
}
