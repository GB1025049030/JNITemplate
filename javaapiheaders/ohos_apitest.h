#ifndef JNI_OHOS_APITEST_H
#define JNI_OHOS_APITEST_H

#include "jni_transform.h"
#include <string>
#include <jni.h>
#include <vector>
#include <map>

namespace OHOS {
namespace APITEST {

#define JSON_FILE_OHOS_APITEST "ohos_apitest.json"

#define JAVA_BEAN_Books "ohos/apitest/Books"
#define JAVA_BEAN_ClassRoom "ohos/apitest/ClassRoom"
#define JAVA_BEAN_Student "ohos/apitest/Student"

using namespace TEMPLATE;

struct Books;
struct Student;

struct Books {
    int32_t chinese;
    int32_t math;
};

struct ClassRoom {
    std::map<int32_t, Books> books;
    std::string name;
    std::vector<Student> students;
};

struct Student {
    int32_t age;
    int32_t id;
    std::string name;
};

class TransformBooks : public Transform<Books> {
    using Transform::Transform;
    public:
        void Extract(jobject source, Books *target) override;
        void Convert(jobject target, const Books *source) override;
        jobject CreateJavaObject(const Books *source) override;
        void Release() override;
};

class TransformClassRoom : public Transform<ClassRoom> {
    using Transform::Transform;
    public:
        void Extract(jobject source, ClassRoom *target) override;
        void Convert(jobject target, const ClassRoom *source) override;
        jobject CreateJavaObject(const ClassRoom *source) override;
        void Release() override;
};

class TransformStudent : public Transform<Student> {
    using Transform::Transform;
    public:
        void Extract(jobject source, Student *target) override;
        void Convert(jobject target, const Student *source) override;
        jobject CreateJavaObject(const Student *source) override;
        void Release() override;
};

enum class Books_FIELD_CODE {
    chinese = 12,
    math = 13,
};

enum class ClassRoom_FIELD_CODE {
    books = 14,
    name = 15,
    students = 16,
};

enum class Student_FIELD_CODE {
    age = 17,
    id = 18,
    name = 19,
};

enum class MethodCode_OHOS_APITEST {

    /**
     * sign: (Lohos/apitest/ClassRoom;)V
     * isStaticMethod: true
     * isNonvirtualMethod: false
     */
    SchoolManager_addClassRoom_1 = 1,

    /**
     * sign: (Ljava/util/List;)V
     * isStaticMethod: true
     * isNonvirtualMethod: false
     */
    SchoolManager_addClassRooms_1 = 2,

    /**
     * sign: ()Lohos/apitest/ClassRoom;
     * isStaticMethod: false
     * isNonvirtualMethod: false
     */
    SchoolManager_getClassRoomFirst_1 = 3,

    /**
     * sign: ()Ljava/util/List;
     * isStaticMethod: true
     * isNonvirtualMethod: false
     */
    SchoolManager_getClassRooms_1 = 4,

    /**
     * sign: ()Ljava/util/Map;
     * isStaticMethod: true
     * isNonvirtualMethod: false
     */
    SchoolManager_getFirstBooks_1 = 5,

    /**
     * sign: ()Lohos/apitest/SchoolManager;
     * isStaticMethod: true
     * isNonvirtualMethod: false
     */
    SchoolManager_getInstance_1 = 6,
};

} // namespace APITEST
} // namespace OHOS

#endif //JNI_OHOS_APITEST_H
