package ohos.apitest;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

@JNIClass
public class ClassRoom {
    @JNIField(sign = "Ljava/lang/String;")
    public String name;
    @JNIField(sign = "[Lohos/apitest/Student;")
    public Student[] students;
}
