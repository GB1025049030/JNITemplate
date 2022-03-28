//
// Created by guobin on 2022/3/7.
//

#ifndef JNITEMPLATE_JSON_UTIL_H
#define JNITEMPLATE_JSON_UTIL_H

#include <nlohmann/json.hpp>

#include "jni_error.h"
#include "jni_log.h"

namespace OHOS {
namespace TEMPLATE {

enum class JsonType {
    NULLABLE,
    BOOLEAN,
    NUMBER,
    OBJECT,
    ARRAY,
    STRING,
};

enum class ArrayType {
    NUMBER,
    OBJECT,
    STRING,
    NOT_ARRAY,
};

template <typename T, typename dataType>
void CheckArrayType(const nlohmann::json &jsonObject, const std::string &key,
                    dataType &data, ArrayType arrayType, int32_t &parseResult) {
    auto arrays = jsonObject.at(key);
    if (arrays.empty()) {
        JNI_LOGD("array is empty");
        return;
    }
    switch (arrayType) {
        case ArrayType::STRING:
            for (const auto &array : arrays) {
                if (!array.is_string()) {
                    JNI_LOGD("array %" LOG_LIMIT "s is not string returnObject",
                             key.c_str());
                    parseResult = ERR_JNI_PARSE_PROFILE_PROP_TYPE_ERROR;
                }
            }
            if (parseResult == 0) {
                data = jsonObject.at(key).get<T>();
            }
            break;
        case ArrayType::OBJECT:
            for (const auto &array : arrays) {
                if (!array.is_object()) {
                    JNI_LOGD("array %" LOG_LIMIT "s is not object returnObject",
                             key.c_str());
                    parseResult = ERR_JNI_PARSE_PROFILE_PROP_TYPE_ERROR;
                    break;
                }
            }
            if (parseResult == 0) {
                data = jsonObject.at(key).get<T>();
            }
            break;
        case ArrayType::NUMBER:
            for (const auto &array : arrays) {
                if (!array.is_number()) {
                    JNI_LOGD("array %" LOG_LIMIT "s is not number returnObject",
                             key.c_str());
                    parseResult = ERR_JNI_PARSE_PROFILE_PROP_TYPE_ERROR;
                }
            }
            if (parseResult == 0) {
                data = jsonObject.at(key).get<T>();
            }
            break;
        case ArrayType::NOT_ARRAY:
            JNI_LOGD("array %" LOG_LIMIT "s is not string returnObject",
                     key.c_str());
            break;
        default:
            JNI_LOGD("array %" LOG_LIMIT "s returnObject error", key.c_str());
            break;
    }
}

template <typename T, typename dataType>
void GetValueIfFindKey(
    const nlohmann::json &jsonObject,
    const nlohmann::detail::iter_impl<const nlohmann::json> &end,
    const std::string &key, dataType &data, JsonType jsonType, bool isNecessary,
    int32_t &parseResult, ArrayType arrayType) {
    if (parseResult) {
        return;
    }
    if (jsonObject.find(key) != end) {
        switch (jsonType) {
            case JsonType::BOOLEAN:
                if (!jsonObject.at(key).is_boolean()) {
                    JNI_LOGD("returnObject is error %" LOG_LIMIT
                             "s is not boolean",
                             key.c_str());
                    parseResult = ERR_JNI_PARSE_PROFILE_PROP_TYPE_ERROR;
                    break;
                }
                data = jsonObject.at(key).get<T>();
                break;
            case JsonType::NUMBER:
                if (!jsonObject.at(key).is_number()) {
                    JNI_LOGD("returnObject is error %" LOG_LIMIT
                             "s is not number",
                             key.c_str());
                    parseResult = ERR_JNI_PARSE_PROFILE_PROP_TYPE_ERROR;
                    break;
                }
                data = jsonObject.at(key).get<T>();
                break;
            case JsonType::OBJECT:
                if (!jsonObject.at(key).is_object()) {
                    JNI_LOGD("returnObject is error %" LOG_LIMIT
                             "s is not object",
                             key.c_str());
                    parseResult = ERR_JNI_PARSE_PROFILE_PROP_TYPE_ERROR;
                    break;
                }
                // JNI_LOGI("returnObject key is %" LOG_LIMIT "s", key.c_str());
                data = jsonObject.at(key).get<T>();
                break;
            case JsonType::ARRAY:
                if (!jsonObject.at(key).is_array()) {
                    JNI_LOGD("returnObject is error %" LOG_LIMIT
                             "s is not array",
                             key.c_str());
                    parseResult = ERR_JNI_PARSE_PROFILE_PROP_TYPE_ERROR;
                    break;
                }
                CheckArrayType<T>(jsonObject, key, data, arrayType,
                                  parseResult);
                break;
            case JsonType::STRING:
                if (!jsonObject.at(key).is_string()) {
                    JNI_LOGD("returnObject is error %" LOG_LIMIT
                             "s is not string",
                             key.c_str());
                    parseResult = ERR_JNI_PARSE_PROFILE_PROP_TYPE_ERROR;
                    break;
                }
                data = jsonObject.at(key).get<T>();
                break;
            case JsonType::NULLABLE:
                JNI_LOGD("returnObject is error %" LOG_LIMIT "s is nullable",
                         key.c_str());
                break;
            default:
                JNI_LOGD("returnObject is error %" LOG_LIMIT
                         "s is not jsonType",
                         key.c_str());
                parseResult = ERR_JNI_PARSE_PROFILE_PROP_TYPE_ERROR;
        }
        return;
    }
    if (isNecessary) {
        JNI_LOGD("profile prop %" LOG_LIMIT "s is mission", key.c_str());
        parseResult = ERR_JNI_PARSE_PROFILE_MISSING_PROP;
    }
}
}  // namespace TEMPLATE
}  // namespace OHOS

#endif  // JNITEMPLATE_JSON_UTIL_H
