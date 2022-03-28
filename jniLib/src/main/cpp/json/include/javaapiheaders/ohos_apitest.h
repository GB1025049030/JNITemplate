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

#define JAVA_BEAN_ClassRoom "ohos/apitest/ClassRoom"
#define JAVA_BEAN_Student "ohos/apitest/Student"

        using namespace TEMPLATE;

        struct Books;
        struct Student;

        struct ClassRoom {
            std::map<int32_t, Books> *books;
            std::string name;
            std::vector<Student> students;
        };

        struct Student {
            int32_t age;
            int32_t id;
            std::string name;
        };

        class TransformClassRoom : public Transform<ClassRoom> {
            using Transform::Transform;
        public:
            void Extract(jobject source, ClassRoom *target) override;

            void Convert(jobject target, ClassRoom *source) override;

            jobject CreateObject(ClassRoom *source) override;
        };

        class TransformStudent : public Transform<Student> {
            using Transform::Transform;
        public:
            void Extract(jobject source, Student *target) override;

            void Convert(jobject target, Student *source) override;

            jobject CreateObject(Student *source) override;
        };

        enum class ClassRoom_FIELD_CODE {
            books = 1,
            name = 2,
            students = 3,
        };

        enum class Student_FIELD_CODE {
            age = 4,
            id = 5,
            name = 6,
        };

        enum class MethodCode_OHOS_APITEST {

            /**
             * sign: (Lohos/apitest/ClassRoom;)V
             * isStaticMethod: true
             * isNonvirtualMethod: false
             */
            SchoolManager_addClassRoom_1 = 1,
        };

    } // namespace APITEST
} // namespace OHOS

#endif //JNI_OHOS_APITEST_H
