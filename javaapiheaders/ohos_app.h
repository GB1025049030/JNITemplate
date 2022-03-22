#ifndef JNI_OHOS_APP_H
#define JNI_OHOS_APP_H

namespace OHOS {
    namespace APP {

        #define JSON_FILE_OHOS_APP "ohos_app.json"

        enum class MethodCode_OHOS_APP {
            // sign: ()[Lohos/aafwk/ability/RunningProcessInfo;
            AbilityManager_getAllRunningProcesses_1 = 1,
            // sign: (Ljava/lang/String;)V
            AbilityManager_killProcessesByBundleName_1 = 2,
            // sign: (II)[Lohos/aafwk/ability/AbilityMissionInfo;
            AbilityManager_queryRecentAbilityMissionInfo_1 = 3,
            // sign: (I)[Lohos/aafwk/ability/AbilityMissionInfo;
            AbilityManager_queryRunningAbilityMissionInfo_1 = 4,
        };
    }
}

#endif //JNI_OHOS_APP_H
