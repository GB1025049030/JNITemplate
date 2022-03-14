//
// Created by guobin on 2022/3/10.
//

#ifndef JNITEMPLATE_JNI_TRANSFORM_H
#define JNITEMPLATE_JNI_TRANSFORM_H

#include <jni.h>
#include "jni_info.h"

namespace OHOS {
    template<typename T>
    class Transform {
    public:
        Transform(T *tt);

        virtual void Extract(jobject source, T *target) = 0;

        virtual void Convert(jobject target, T *source) = 0;

    public:
        T* t;
    };

    template<typename T>
    Transform<T>::Transform(T *tt) {
        t = tt;
    }
}

#endif //JNITEMPLATE_JNI_TRANSFORM_H
