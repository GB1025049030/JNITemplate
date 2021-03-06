//
// Created by guobin on 2022/3/10.
//

#ifndef JNITEMPLATE_JNI_TRANSFORM_H
#define JNITEMPLATE_JNI_TRANSFORM_H

#include <jni.h>

#include "jni_info.h"

namespace OHOS {
namespace TEMPLATE {

template <typename T>
class Transform {
public:
    Transform(std::string name);

    virtual void Extract(jobject source, T *target) = 0;

    virtual void Convert(jobject target, const T *source) = 0;

    virtual jobject CreateObject(const T *source) = 0;

    virtual std::string GetClassName();

    virtual void Release();

private:
    std::string className;
};

template <typename T>
Transform<T>::Transform(std::string name) {
    className = name;
}

template <typename T>
std::string Transform<T>::GetClassName() {
    return className;
}

template <typename T>
void Transform<T>::Release() {}
}  // namespace TEMPLATE
}  // namespace OHOS

#endif  // JNITEMPLATE_JNI_TRANSFORM_H
