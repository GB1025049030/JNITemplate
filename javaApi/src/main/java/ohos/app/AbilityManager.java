package ohos.app;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIMethod;

import ohos.aafwk.ability.AbilityMissionInfo;
import ohos.aafwk.ability.RunningProcessInfo;

@JNIClass
public class AbilityManager {
    @JNIMethod(sign = "()[Lohos/aafwk/ability/RunningProcessInfo;")
    public RunningProcessInfo[] getAllRunningProcesses() {
        return null;
    }

    @JNIMethod(sign = "(I)[Lohos/aafwk/ability/AbilityMissionInfo;")
    public AbilityMissionInfo[] queryRunningAbilityMissionInfo(int num) {
        return null;
    }

    @JNIMethod(sign = "(II)[Lohos/aafwk/ability/AbilityMissionInfo;")
    public AbilityMissionInfo[] queryRecentAbilityMissionInfo(int maxNum, int flags) {
        return null;
    }

    @JNIMethod(sign = "(Ljava/lang/String;)V")
    public void killProcessesByBundleName(String str) {
    }
}
