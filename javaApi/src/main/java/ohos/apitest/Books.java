package ohos.apitest;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

@JNIClass
public class Books {
    @JNIField(sign = "I")
    public int math;
    @JNIField(sign = "I")
    public int chinese;

    @Override
    public String toString() {
        return "Books{" +
                "math=" + math +
                ", chinese=" + chinese +
                '}';
    }
}
