package ohos.apitest;

import android.util.Log;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIMethod;

import java.util.ArrayList;
import java.util.List;

@JNIClass
public class SchoolManager {
    public static List<ClassRoom> classRooms = new ArrayList<>();

    public static List<ClassRoom> getClassRooms() {
        return classRooms;
    }

    @JNIMethod(sign = "(Lohos/apitest/ClassRoom;)V", isStaticMethod = true)
    public static void addClassRoom(ClassRoom room) {
        Log.d("guobin_tag", "JAVA: addClassRoom: ");
        if (room != null) {
            Log.d("guobin_tag", "JAVA: addClassRoom: room = " + room.name);
            if (room.students != null) {
                for (Student student : room.students) {
                    Log.d("guobin_tag", "JAVA: student: name = " + student.name + ", age = " + student.age);
                }
            }
        }
        classRooms.add(room);
    }
}
