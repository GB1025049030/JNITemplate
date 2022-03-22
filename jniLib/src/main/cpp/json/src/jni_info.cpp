//
// Created by guobin on 2022/3/9.
//

#include "jni_info.h"

#include "json_util.h"

namespace OHOS {
namespace TEMPLATE {

void from_json(const nlohmann::json &jsonObject, JNIInfo &jniInfo) {
    JNI_LOGI("from_json : JNIInfo begin");
    jniInfo.classes = jsonObject.at("classes").get<std::vector<ClassInfo>>();
    JNI_LOGI("from_json : JNIInfo end");
}

void from_json(const nlohmann::json &jsonObject, ClassInfo &classInfo) {
    JNI_LOGI("from_json : ClassInfo begin");
    const auto &jsonObjectEnd = jsonObject.end();
    classInfo.pkgName = jsonObject.at("pkgName").get<std::string>();
    classInfo.className = jsonObject.at("className").get<std::string>();
    int32_t parseResult = 0;
    GetValueIfFindKey<std::vector<MethodInfo>>(
        jsonObject, jsonObjectEnd, "methods", classInfo.methods,
        JsonType::ARRAY, false, parseResult, ArrayType::OBJECT);
    parseResult = 0;
    GetValueIfFindKey<std::vector<FieldInfo>>(
        jsonObject, jsonObjectEnd, "fields", classInfo.fields, JsonType::ARRAY,
        false, parseResult, ArrayType::OBJECT);
    JNI_LOGI("from_json : ClassInfo end");
}

void from_json(const nlohmann::json &jsonObject, MethodInfo &methodInfo) {
    JNI_LOGI("from_json : MethodInfo begin");
    const auto &jsonObjectEnd = jsonObject.end();
    methodInfo.id = jsonObject.at("id").get<int32_t>();
    methodInfo.overloadSN = jsonObject.at("overloadSN").get<int32_t>();
    methodInfo.name = jsonObject.at("name").get<std::string>();
    methodInfo.sign = jsonObject.at("sign").get<std::string>();
    int32_t parseResult = 0;
    GetValueIfFindKey<std::vector<Argument>>(
        jsonObject, jsonObjectEnd, "args", methodInfo.args, JsonType::ARRAY,
        true, parseResult, ArrayType::OBJECT);
    parseResult = 0;
    GetValueIfFindKey<ReturnObject>(jsonObject, jsonObjectEnd, "returnObject",
                                    methodInfo.returnObject, JsonType::OBJECT,
                                    false, parseResult, ArrayType::NOT_ARRAY);
    JNI_LOGI("from_json : MethodInfo end");
}

void from_json(const nlohmann::json &jsonObject, FieldInfo &fieldInfo) {
    JNI_LOGI("from_json : FieldInfo begin");
    const auto &jsonObjectEnd = jsonObject.end();
    // fieldInfo.id = jsonObject.at("id").get<int32_t>();
    int32_t parseResult = 0;
    GetValueIfFindKey<int32_t>(jsonObject, jsonObjectEnd, "id", fieldInfo.id,
                               JsonType::NUMBER, true, parseResult,
                               ArrayType::NOT_ARRAY);
    fieldInfo.flag = jsonObject.at("flag").get<int32_t>();
    fieldInfo.arrayDimension = jsonObject.at("arrayDimension").get<int32_t>();
    fieldInfo.name = jsonObject.at("name").get<std::string>();
    fieldInfo.clsName = jsonObject.at("clsName").get<std::string>();
    fieldInfo.sign = jsonObject.at("sign").get<std::string>();
    JNI_LOGI("from_json : FieldInfo end");
}

void from_json(const nlohmann::json &jsonObject, ReturnObject &returnObject) {
    JNI_LOGI("from_json : ReturnObject begin");
    returnObject.flag = jsonObject.at("flag").get<int32_t>();
    returnObject.arrayDimension =
        jsonObject.at("arrayDimension").get<int32_t>();
    returnObject.clsName = jsonObject.at("clsName").get<std::string>();
    returnObject.sign = jsonObject.at("sign").get<std::string>();
    JNI_LOGI("from_json : ReturnObject end");
}

void from_json(const nlohmann::json &jsonObject, Argument &argument) {
    JNI_LOGI("from_json : Argument begin");
    argument.order = jsonObject.at("order").get<int32_t>();
    argument.flag = jsonObject.at("flag").get<int32_t>();
    argument.arrayDimension = jsonObject.at("arrayDimension").get<int32_t>();
    argument.clsName = jsonObject.at("clsName").get<std::string>();
    argument.sign = jsonObject.at("sign").get<std::string>();
    JNI_LOGI("from_json : Argument end");
}

bool IsStatic(int32_t type) {
    auto flag = static_cast<int32_t>(MethodFlag::FLAG_JNI_METHOD_IS_STATIC);
    return (type & flag) == flag;
}

bool IsNonvirtual(int32_t type) {
    auto flag = static_cast<int32_t>(MethodFlag::FLAG_JNI_METHOD_IS_NONVIRTUAL);
    return (type & flag) == flag;
}

MethodFlag GetReturnType(int32_t type) {
    int32_t flag =
        static_cast<int32_t>(MethodFlag::FLAG_JNI_METHOD_RETURN_VOID) - 1;
    return static_cast<MethodFlag>(type & (~flag));
}
}  // namespace TEMPLATE
}  // namespace OHOS