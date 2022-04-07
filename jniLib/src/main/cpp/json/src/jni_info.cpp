//
// Created by guobin on 2022/3/9.
//

#include "jni_info.h"

#include "jni_json_util.h"

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
    fieldInfo.id = jsonObject.at("id").get<int32_t>();
    fieldInfo.name = jsonObject.at("name").get<std::string>();
    int32_t parseResult = 0;
    GetValueIfFindKey<BaseType>(jsonObject, jsonObjectEnd, "baseType",
                                fieldInfo.baseType, JsonType::OBJECT, false,
                                parseResult, ArrayType::NOT_ARRAY);
    JNI_LOGI("from_json : FieldInfo end");
}

void from_json(const nlohmann::json &jsonObject, ReturnObject &returnObject) {
    JNI_LOGI("from_json : ReturnObject begin");
    const auto &jsonObjectEnd = jsonObject.end();
    int32_t parseResult = 0;
    GetValueIfFindKey<BaseType>(jsonObject, jsonObjectEnd, "baseType",
                                returnObject.baseType, JsonType::OBJECT, false,
                                parseResult, ArrayType::NOT_ARRAY);
    JNI_LOGI("from_json : ReturnObject end");
}

void from_json(const nlohmann::json &jsonObject, Argument &argument) {
    JNI_LOGI("from_json : Argument begin");
    const auto &jsonObjectEnd = jsonObject.end();
    argument.order = jsonObject.at("order").get<int32_t>();
    int32_t parseResult = 0;
    GetValueIfFindKey<BaseType>(jsonObject, jsonObjectEnd, "baseType",
                                argument.baseType, JsonType::OBJECT, false,
                                parseResult, ArrayType::NOT_ARRAY);
    JNI_LOGI("from_json : Argument end");
}

void from_json(const nlohmann::json &jsonObject, BaseType &baseType) {
    JNI_LOGI("from_json : BaseType begin");
    int32_t parseResult = 0;
    const auto &jsonObjectEnd = jsonObject.end();
    baseType.flag = jsonObject.at("flag").get<int32_t>();
    baseType.arrayDimension = jsonObject.at("arrayDimension").get<int32_t>();
    baseType.clsName = jsonObject.at("clsName").get<std::string>();
    baseType.sign = jsonObject.at("sign").get<std::string>();
    if (jsonObject.find("additionalKey") != jsonObjectEnd) {
        parseResult = 0;
        baseType.additionalKey = new BaseType();
        GetValueIfFindKey<BaseType>(jsonObject, jsonObjectEnd, "additionalKey",
                                    (*baseType.additionalKey), JsonType::OBJECT,
                                    true, parseResult, ArrayType::NOT_ARRAY);
    }
    if (jsonObject.find("additionalValue") != jsonObjectEnd) {
        parseResult = 0;
        baseType.additionalValue = new BaseType();
        GetValueIfFindKey<BaseType>(
            jsonObject, jsonObjectEnd, "additionalValue",
            (*baseType.additionalValue), JsonType::OBJECT, true, parseResult,
            ArrayType::NOT_ARRAY);
    }
    JNI_LOGI("from_json : BaseType end");
}

bool JNIInfoUtil::IsStatic(int32_t type) {
    auto flag = static_cast<int32_t>(MethodFlag::FLAG_JNI_METHOD_IS_STATIC);
    return (type & flag) == flag;
}

bool JNIInfoUtil::IsNonvirtual(int32_t type) {
    auto flag = static_cast<int32_t>(MethodFlag::FLAG_JNI_METHOD_IS_NONVIRTUAL);
    return (type & flag) == flag;
}

bool JNIInfoUtil::CheckIsType(BaseType *type, MethodFlag targetFlag,
                              int32_t *result) {
    MethodFlag flag = GetReturnType(type->flag);
    (*result) = static_cast<int32_t>(flag);
    return flag == targetFlag && type->arrayDimension == 0;
}

bool JNIInfoUtil::CheckIsTypeArray(BaseType *type, MethodFlag targetFlag,
                                   int32_t *result) {
    MethodFlag flag = GetReturnType(type->flag);
    (*result) = static_cast<int32_t>(flag);
    return flag == targetFlag && type->arrayDimension == 1;
}

bool JNIInfoUtil::CheckIsTypeList(BaseType *type, MethodFlag targetFlag,
                                  int32_t *result) {
    auto flag = static_cast<int32_t>(GetReturnType(type->flag));
    (*result) = static_cast<int32_t>(flag);
    if (IsList(flag)) {
        if (type->additionalValue) {
            JNI_LOGW("CheckIsTypeList: additionalValue.flag = %" LOG_LIMIT "d",
                     type->additionalValue->flag);
            auto additionalValueFlag = static_cast<int32_t>(
                GetReturnType(type->additionalValue->flag));
            return additionalValueFlag == static_cast<int32_t>(targetFlag);
        }
    }
    return false;
}

bool JNIInfoUtil::NeedTransform(int32_t type) {
    return type ==
           static_cast<int32_t>(MethodFlag::FLAG_JNI_METHOD_RETURN_OBJECT);
}

bool JNIInfoUtil::IsList(int32_t type) {
    auto flag = static_cast<int32_t>(MethodFlag::FLAG_JNI_METHOD_RETURN_LIST);
    return (type & flag) == flag;
}

bool JNIInfoUtil::IsMap(int32_t type) {
    auto flag = static_cast<int32_t>(MethodFlag::FLAG_JNI_METHOD_RETURN_MAP);
    return (type & flag) == flag;
}

MethodFlag JNIInfoUtil::GetReturnType(int32_t type) {
    int32_t flag =
        static_cast<int32_t>(MethodFlag::FLAG_JNI_METHOD_RETURN_VOID) - 1;
    return static_cast<MethodFlag>(type & (~flag));
}
}  // namespace TEMPLATE
}  // namespace OHOS