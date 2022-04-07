package ohos.apitest;

import android.util.Log;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIMethod;

import java.awt.print.Book;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import ohos.bundlemgr.BundleMgrAdapter;

@JNIClass
public class SchoolManager {
    private static final Object INSTANCE_LOCK = new Object();
    public static List<ClassRoom> classRooms = new ArrayList<>();
    public static SchoolManager mSchoolManager;

    private SchoolManager() {}

    @JNIMethod(sign = "()Lohos/apitest/SchoolManager;", isStaticMethod = true)
    public static SchoolManager getInstance() {
        if (mSchoolManager == null) {
            synchronized (INSTANCE_LOCK) {
                if (mSchoolManager == null) {
                    mSchoolManager = new SchoolManager();
                }
            }
        }
        return mSchoolManager;
    }

    @JNIMethod(sign = "()Lohos/apitest/ClassRoom;")
    public ClassRoom getClassRoomFirst() {
        if (!classRooms.isEmpty()) {
            return classRooms.get(0);
        }
        return null;
    }

    @JNIMethod(sign = "()Ljava/util/List;", isStaticMethod = true)
    public static List<ClassRoom> getClassRooms() {
        Log.d("guobin_tag", "JAVA: getClassRooms: ");
        return classRooms;
    }

    @JNIMethod(sign = "()Ljava/util/Map;", isStaticMethod = true)
    public static Map<Integer, Books> getFirstBooks() {
        Log.d("guobin_tag", "JAVA: getFirstBooks: ");
        for (ClassRoom room : classRooms) {
            if (room.books != null && !room.books.isEmpty()) {
                return room.books;
            }
        }
        return null;
    }

    @JNIMethod(sign = "(Lohos/apitest/ClassRoom;)V", isStaticMethod = true)
    public static void addClassRoom(ClassRoom room) {
        Log.d("guobin_tag", "JAVA: addClassRoom: ");
        if (room != null) {
            Log.d("guobin_tag", "JAVA: addClassRoom: room = " + room);
        }
        classRooms.add(room);
    }

    @JNIMethod(sign = "(Ljava/util/List;)V", isStaticMethod = true)
    public static void addClassRooms(List<ClassRoom> rooms) {
        Log.d("guobin_tag", "JAVA: addClassRooms: ");
        if (rooms != null) {
            for (ClassRoom room : rooms) {
                Log.d("guobin_tag", "JAVA: addClassRooms: room = " + room);
            }
            classRooms.addAll(rooms);
        }
    }
}
