#ifndef JNI_OHOS_AAFWK_ABILITY_H
#define JNI_OHOS_AAFWK_ABILITY_H

#include <string>
#include <jni.h>
#include "ohos_bundle_base.h"
#include <vector>

#define JSON_CONFIG_FILE_OHOS_AAFWK_ABILITY "ohos_aafwk_ability.json"

struct AbilityMissionInfo {
    ElementName mAbilityBaseBundleName;
    int32_t mAbilityMissionId;
    int32_t mAbilityStackId;
    ElementName mAbilityTopBundleName;
};

void convertC2JAbilityMissionInfo(AbilityMissionInfo data, jobject* obj);
void convertJ2CAbilityMissionInfo(jobject obj, AbilityMissionInfo* data);

enum class AbilityMissionInfo_FIELD_CODE {
    mAbilityBaseBundleName = 1,
    mAbilityMissionId = 2,
    mAbilityStackId = 3,
    mAbilityTopBundleName = 4,
};
struct RunningProcessInfo {
    int32_t mLastMemoryLevel;
    int32_t mPid;
    int32_t mUid;
    std::vector<std::string> mPkgList;
    std::string mProcessName;
    int32_t mWeight;
    int32_t mWeightReasonCode;
};

void convertC2JRunningProcessInfo(RunningProcessInfo data, jobject* obj);
void convertJ2CRunningProcessInfo(jobject obj, RunningProcessInfo* data);

enum class RunningProcessInfo_FIELD_CODE {
    mLastMemoryLevel = 5,
    mPid = 6,
    mUid = 7,
    mPkgList = 8,
    mProcessName = 9,
    mWeight = 10,
    mWeightReasonCode = 11,
};

#endif //JNI_OHOS_AAFWK_ABILITY_H
