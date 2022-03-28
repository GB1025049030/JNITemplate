#ifndef JNI_OHOS_APP_H
#define JNI_OHOS_APP_H

namespace OHOS {
namespace APP {

#define JSON_FILE_OHOS_APP "ohos_app.json"

enum class MethodCode_OHOS_APP {

    /**
     * sign: ()Ljava/util/List;
     * isStaticMethod: false
     * isNonvirtualMethod: false
     */
    AbilityManager_getAllRunningProcesses_1 = 1,

    /**
     * sign: (Ljava/lang/String;)V
     * isStaticMethod: false
     * isNonvirtualMethod: false
     */
    AbilityManager_killProcessesByBundleName_1 = 2,

    /**
     * sign: (II)Ljava/util/List;
     * isStaticMethod: false
     * isNonvirtualMethod: false
     */
    AbilityManager_queryRecentAbilityMissionInfo_1 = 3,

    /**
     * sign: (I)Ljava/util/List;
     * isStaticMethod: false
     * isNonvirtualMethod: false
     */
    AbilityManager_queryRunningAbilityMissionInfo_1 = 4,
};

} // namespace APP
} // namespace OHOS

#endif //JNI_OHOS_APP_H
