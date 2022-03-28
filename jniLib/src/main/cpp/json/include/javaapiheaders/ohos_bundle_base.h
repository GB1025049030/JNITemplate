#ifndef JNI_OHOS_BUNDLE_BASE_H
#define JNI_OHOS_BUNDLE_BASE_H

#include "jni_transform.h"
#include <string>
#include <jni.h>
#include <vector>

namespace OHOS {
namespace BUNDLE {
namespace BASE {

#define JSON_FILE_OHOS_BUNDLE_BASE "ohos_bundle_base.json"

#define JAVA_BEAN_ApplicationInfo "ohos/bundle/base/ApplicationInfo"
#define JAVA_BEAN_ElementName "ohos/bundle/base/ElementName"
#define JAVA_BEAN_ModuleInfo "ohos/bundle/base/ModuleInfo"

using namespace TEMPLATE;

struct ModuleInfo;

struct ApplicationInfo {
    std::string bundleName;
    std::string cacheDir;
    std::string codePath;
    std::string dataBaseDir;
    std::string dataDir;
    std::string description;
    int32_t descriptionId;
    std::string deviceId;
    uint8_t enabled;
    std::string entryDir;
    int32_t flags;
    std::string icon;
    int32_t iconId;
    uint8_t isLauncherApp;
    std::string label;
    int32_t labelId;
    std::vector<ModuleInfo> moduleInfos;
    std::vector<std::string> moduleSourceDirs;
    std::string name;
    std::vector<std::string> permissions;
    std::string process;
    std::string signatureKey;
    int32_t supportedModes;
    uint8_t systemApp;
};

struct ElementName {
    std::string abilityName_;
    std::string bundleName_;
    std::string deviceId_;
};

struct ModuleInfo {
    std::string moduleName;
    std::string moduleSourceDir;
};

class TransformApplicationInfo : public Transform<ApplicationInfo> {
    using Transform::Transform;
    public:
        void Extract(jobject source, ApplicationInfo *target) override;
        void Convert(jobject target, const ApplicationInfo *source) override;
        jobject CreateObject(const ApplicationInfo *source) override;
        void Release() override;
};

class TransformElementName : public Transform<ElementName> {
    using Transform::Transform;
    public:
        void Extract(jobject source, ElementName *target) override;
        void Convert(jobject target, const ElementName *source) override;
        jobject CreateObject(const ElementName *source) override;
        void Release() override;
};

class TransformModuleInfo : public Transform<ModuleInfo> {
    using Transform::Transform;
    public:
        void Extract(jobject source, ModuleInfo *target) override;
        void Convert(jobject target, const ModuleInfo *source) override;
        jobject CreateObject(const ModuleInfo *source) override;
        void Release() override;
};

enum class ApplicationInfo_FIELD_CODE {
    bundleName = 1,
    cacheDir = 2,
    codePath = 3,
    dataBaseDir = 4,
    dataDir = 5,
    description = 6,
    descriptionId = 7,
    deviceId = 8,
    enabled = 9,
    entryDir = 10,
    flags = 11,
    icon = 12,
    iconId = 13,
    isLauncherApp = 14,
    label = 15,
    labelId = 16,
    moduleInfos = 17,
    moduleSourceDirs = 18,
    name = 19,
    permissions = 20,
    process = 21,
    signatureKey = 22,
    supportedModes = 23,
    systemApp = 24,
};

enum class ElementName_FIELD_CODE {
    abilityName_ = 25,
    bundleName_ = 26,
    deviceId_ = 27,
};

enum class ModuleInfo_FIELD_CODE {
    moduleName = 28,
    moduleSourceDir = 29,
};

} // namespace BASE
} // namespace BUNDLE
} // namespace OHOS

#endif //JNI_OHOS_BUNDLE_BASE_H
