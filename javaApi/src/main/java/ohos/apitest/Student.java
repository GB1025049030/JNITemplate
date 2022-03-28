package ohos.apitest;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

import java.util.Objects;

@JNIClass
public class Student {
    @JNIField(sign = "I")
    public int id;
    @JNIField(sign = "Ljava/lang/String;")
    public String name;
    @JNIField(sign = "I")
    public int age;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Student student = (Student) o;
        return id == student.id;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}
