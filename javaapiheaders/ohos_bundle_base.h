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
        jobject CreateJavaObject(const ApplicationInfo *source) override;
        void Release() override;
};

class TransformElementName : public Transform<ElementName> {
    using Transform::Transform;
    public:
        void Extract(jobject source, ElementName *target) override;
        void Convert(jobject target, const ElementName *source) override;
        jobject CreateJavaObject(const ElementName *source) override;
        void Release() override;
};

class TransformModuleInfo : public Transform<ModuleInfo> {
    using Transform::Transform;
    public:
        void Extract(jobject source, ModuleInfo *target) override;
        void Convert(jobject target, const ModuleInfo *source) override;
        jobject CreateJavaObject(const ModuleInfo *source) override;
        void Release() override;
};

enum class ApplicationInfo_FIELD_CODE {
    bundleName = 20,
    cacheDir = 21,
    codePath = 22,
    dataBaseDir = 23,
    dataDir = 24,
    description = 25,
    descriptionId = 26,
    deviceId = 27,
    enabled = 28,
    entryDir = 29,
    flags = 30,
    icon = 31,
    iconId = 32,
    isLauncherApp = 33,
    label = 34,
    labelId = 35,
    moduleInfos = 36,
    moduleSourceDirs = 37,
    name = 38,
    permissions = 39,
    process = 40,
    signatureKey = 41,
    supportedModes = 42,
    systemApp = 43,
};

enum class ElementName_FIELD_CODE {
    abilityName_ = 44,
    bundleName_ = 45,
    deviceId_ = 46,
};

enum class ModuleInfo_FIELD_CODE {
    moduleName = 47,
    moduleSourceDir = 48,
};

} // namespace BASE
} // namespace BUNDLE
} // namespace OHOS

#endif //JNI_OHOS_BUNDLE_BASE_H
