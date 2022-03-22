#ifndef JNI_OHOS_APITEST_H
#define JNI_OHOS_APITEST_H

#include "jni_transform.h"
#include <string>
#include <jni.h>
#include <vector>

namespace OHOS {
    namespace APITEST {

        #define JSON_FILE_OHOS_APITEST "ohos_apitest.json"

        #define JAVA_BEAN_ClassRoom "ohos/apitest/ClassRoom"
        #define JAVA_BEAN_Student "ohos/apitest/Student"

        using namespace TEMPLATE;

        struct Student;

        struct ClassRoom {
            std::string name;
            std::vector<Student> students;
        };

        struct Student {
            int32_t age;
            std::string name;
        };

        class TransformClassRoom : public Transform<ClassRoom> {
            using Transform::Transform;
            public:
                void Extract(jobject source, ClassRoom *target) override;
                void Convert(jobject target, ClassRoom *source) override;
        };

        class TransformStudent : public Transform<Student> {
            using Transform::Transform;
            public:
                void Extract(jobject source, Student *target) override;
                void Convert(jobject target, Student *source) override;
        };

        enum class ClassRoom_FIELD_CODE {
            name = 1,
            students = 2,
        };

        enum class Student_FIELD_CODE {
            age = 3,
            name = 4,
        };

        enum class MethodCode_OHOS_APITEST {
            // sign: (Lohos/apitest/ClassRoom;)V
            SchoolManager_addClassRoom_1 = 1,
        };
    }
}

#endif //JNI_OHOS_APITEST_H
