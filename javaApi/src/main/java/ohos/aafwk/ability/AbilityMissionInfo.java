package ohos.aafwk.ability;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

import ohos.bundle.base.ElementName;

@JNIClass
public class AbilityMissionInfo {
    @JNIField(sign = "Lohos/bundle/base/ElementName;")
    private /*final*/ ElementName mAbilityBaseBundleName;
    @JNIField(sign = "I")
    private /*final*/ int mAbilityMissionId;
    @JNIField(sign = "I")
    private /*final*/ int mAbilityStackId;
    @JNIField(sign = "Lohos/bundle/base/ElementName;")
    private /*final*/ ElementName mAbilityTopBundleName;
}
