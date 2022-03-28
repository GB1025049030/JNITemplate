package ohos.apitest;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

import java.util.List;
import java.util.Map;

@JNIClass
public class ClassRoom {
    @JNIField(sign = "Ljava/lang/String;")
    public String name;
    @JNIField(sign = "Ljava/util/List;")
    public List<Student> students;
    @JNIField(sign = "Ljava/util/Map;")
    public Map<Integer, Books> books;

    @Override
    public String toString() {
        return "ClassRoom{" +
                "name='" + name + '\'' +
                ", students=" + students +
                ", books=" + books +
                '}';
    }
}
