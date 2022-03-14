/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UTILS_JNIKIT_JKIT_H
#define UTILS_JNIKIT_JKIT_H

#include <jni.h>

namespace OHOS {
    class Jkit {
    public:
        Jkit();

        ~Jkit();

        static JavaVM *nativeInit(JavaVM *vm);

        static bool IsNativeInited();

        JNIEnv *operator->();

        bool IsValidEnv();

    private:
        static JavaVM *javaVm_;

        JNIEnv *jniEnv{};
        int attach;
    };
} // namespace OHOS
#endif // UTILS_JNIKIT_JKIT_H
