#ifndef JNI_OHOS_BUNDLE_BASE_H
#define JNI_OHOS_BUNDLE_BASE_H

#include <string>
#include <jni.h>

#define JSON_CONFIG_FILE_OHOS_BUNDLE_BASE "ohos_bundle_base.json"

struct ElementName {
    std::string deviceId_;
    std::string bundleName_;
    std::string abilityName_;
};

void convertC2JElementName(ElementName data, jobject* obj);
void convertJ2CElementName(jobject obj, ElementName* data);

enum class ElementName_FIELD_CODE {
    deviceId_ = 1,
    bundleName_ = 2,
    abilityName_ = 3,
};

#endif //JNI_OHOS_BUNDLE_BASE_H
