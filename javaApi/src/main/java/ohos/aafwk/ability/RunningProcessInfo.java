package ohos.aafwk.ability;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

@JNIClass
public class RunningProcessInfo {
    @JNIField(sign = "I")
    private int mLastMemoryLevel;
    @JNIField(sign = "I")
    private int mPid;
    @JNIField(sign = "I")
    private int mUid;
    @JNIField(sign = "[Ljava/lang/String;")
    private String[] mPkgList;
    @JNIField(sign = "Ljava/lang/String;")
    private String mProcessName;
    @JNIField(sign = "I")
    private int mWeight;
    @JNIField(sign = "I")
    private int mWeightReasonCode;
}
