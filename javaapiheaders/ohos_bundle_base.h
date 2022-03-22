#ifndef JNI_OHOS_BUNDLE_BASE_H
#define JNI_OHOS_BUNDLE_BASE_H

#include "jni_transform.h"
#include <string>
#include <jni.h>

namespace OHOS {
    namespace BUNDLE {
        namespace BASE {

            #define JSON_FILE_OHOS_BUNDLE_BASE "ohos_bundle_base.json"

            #define JAVA_BEAN_ElementName "ohos/bundle/base/ElementName"

            using namespace TEMPLATE;

            struct ElementName {
                std::string abilityName_;
                std::string bundleName_;
                std::string deviceId_;
            };

            class TransformElementName : public Transform<ElementName> {
                using Transform::Transform;
                public:
                    void Extract(jobject source, ElementName *target) override;
                    void Convert(jobject target, ElementName *source) override;
            };

            enum class ElementName_FIELD_CODE {
                abilityName_ = 1,
                bundleName_ = 2,
                deviceId_ = 3,
            };
        }
    }
}

#endif //JNI_OHOS_BUNDLE_BASE_H
