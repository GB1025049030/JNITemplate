#ifndef JNI_OHOS_AAFWK_ABILITY_H
#define JNI_OHOS_AAFWK_ABILITY_H

#include "jni_transform.h"
#include <string>
#include "ohos_bundle_base.h"
#include <jni.h>
#include <vector>

namespace OHOS {
namespace AAFWK {
namespace ABILITY {

#define JSON_FILE_OHOS_AAFWK_ABILITY "ohos_aafwk_ability.json"

#define JAVA_BEAN_AbilityMissionInfo "ohos/aafwk/ability/AbilityMissionInfo"
#define JAVA_BEAN_RunningProcessInfo "ohos/aafwk/ability/RunningProcessInfo"

using namespace TEMPLATE;

struct AbilityMissionInfo {
    ElementName mAbilityBaseBundleName;
    int32_t mAbilityMissionId;
    int32_t mAbilityStackId;
    ElementName mAbilityTopBundleName;
};

struct RunningProcessInfo {
    int32_t mLastMemoryLevel;
    int32_t mPid;
    std::vector<std::string> mPkgList;
    std::string mProcessName;
    int32_t mUid;
    int32_t mWeight;
    int32_t mWeightReasonCode;
};

class TransformAbilityMissionInfo : public Transform<AbilityMissionInfo> {
    using Transform::Transform;
    public:
        void Extract(jobject source, AbilityMissionInfo *target) override;
        void Convert(jobject target, const AbilityMissionInfo *source) override;
        jobject CreateObject(const AbilityMissionInfo *source) override;
        void Release() override;
};

class TransformRunningProcessInfo : public Transform<RunningProcessInfo> {
    using Transform::Transform;
    public:
        void Extract(jobject source, RunningProcessInfo *target) override;
        void Convert(jobject target, const RunningProcessInfo *source) override;
        jobject CreateObject(const RunningProcessInfo *source) override;
        void Release() override;
};

enum class AbilityMissionInfo_FIELD_CODE {
    mAbilityBaseBundleName = 1,
    mAbilityMissionId = 2,
    mAbilityStackId = 3,
    mAbilityTopBundleName = 4,
};

enum class RunningProcessInfo_FIELD_CODE {
    mLastMemoryLevel = 5,
    mPid = 6,
    mPkgList = 7,
    mProcessName = 8,
    mUid = 9,
    mWeight = 10,
    mWeightReasonCode = 11,
};

} // namespace ABILITY
} // namespace AAFWK
} // namespace OHOS

#endif //JNI_OHOS_AAFWK_ABILITY_H
