package ohos.app;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIMethod;

import java.util.List;
import java.util.Map;

import ohos.aafwk.ability.AbilityMissionInfo;
import ohos.aafwk.ability.RunningProcessInfo;

@JNIClass
public class AbilityManager {
    @JNIMethod(sign = "()Ljava/util/List;")
    public List<RunningProcessInfo> getAllRunningProcesses() {
        return null;
    }

    @JNIMethod(sign = "(I)Ljava/util/List;")
    public List<AbilityMissionInfo> queryRunningAbilityMissionInfo(int num) {
        return null;
    }

    @JNIMethod(sign = "(II)Ljava/util/List;")
    public List<AbilityMissionInfo> queryRecentAbilityMissionInfo(int maxNum, int flags) {
        return null;
    }

    @JNIMethod(sign = "(Ljava/lang/String;)V")
    public void killProcessesByBundleName(String str) {
    }
}
