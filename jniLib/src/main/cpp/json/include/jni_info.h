//
// Created by guobin on 2022/3/9.
//

#ifndef JNITEMPLATE_JNI_INFO_H
#define JNITEMPLATE_JNI_INFO_H

#include <jni.h>

#include <map>
#include <set>
#include <string>
#include <vector>

#include "javaapiheaders/jni_method_flag.h"
#include "nlohmann/json.hpp"

namespace OHOS {
namespace TEMPLATE {

struct ArgumentBase {
    int32_t flag;
    int32_t arrayDimension;
    std::string clsName;
    std::string sign;
};

struct FieldInfo : public ArgumentBase {
    int32_t id;
    std::string name;
};

struct ReturnObject : public ArgumentBase {};

struct Argument : public ArgumentBase {
    int32_t order;
};

struct MethodInfo {
    int32_t id;
    int32_t overloadSN;
    std::string name;
    std::string sign;
    std::vector<Argument> args;
    ReturnObject returnObject;
};

struct ClassInfo {
    std::string pkgName;
    std::string className;
    std::vector<MethodInfo> methods;
    std::vector<FieldInfo> fields;
};

struct JNIInfo {
    std::vector<ClassInfo> classes;
};

struct JNIMethodInfo {
    jmethodID methodID;
    jclass classID;
    ReturnObject returnObject;

    JNIMethodInfo(jmethodID &methodID, jclass &classID,
                  ReturnObject &returnObject)
        : methodID(methodID), classID(classID), returnObject(returnObject) {}
};

struct JNIFieldInfo {
    jfieldID fieldId;
    jclass classID;
    FieldInfo fieldInfo;

    JNIFieldInfo() : fieldId(), classID(), fieldInfo() {}

    JNIFieldInfo(jfieldID &fieldId, jclass &classID, FieldInfo &fieldInfo)
        : fieldId(fieldId), classID(classID), fieldInfo(fieldInfo) {}
};

struct TransformInfo {
    jclass classID;
    std::vector<int32_t> fields;
};

struct JavaMethodResult {
    jobject value;
    ReturnObject returnObject;
};

typedef union {
    uint8_t z;
    int8_t b;
    uint16_t c;
    int16_t s;
    int32_t i;
    int64_t j;
    float f;
    double d;
} cvalue;

void from_json(const nlohmann::json &jsonObject, JNIInfo &jniInfo);
void from_json(const nlohmann::json &jsonObject, ClassInfo &classInfo);
void from_json(const nlohmann::json &jsonObject, MethodInfo &methodInfo);
void from_json(const nlohmann::json &jsonObject, FieldInfo &fieldInfo);
void from_json(const nlohmann::json &jsonObject, ReturnObject &returnObject);
void from_json(const nlohmann::json &jsonObject, Argument &argument);
bool IsStatic(int32_t type);
bool IsNonvirtual(int32_t type);

MethodFlag GetReturnType(int32_t type);
}  // namespace TEMPLATE
}  // namespace OHOS

#endif  // JNITEMPLATE_JNI_INFO_H
