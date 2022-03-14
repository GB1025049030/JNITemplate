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

#include "jkit.h"

namespace OHOS {

    JavaVM *Jkit::javaVm_ = nullptr;

    Jkit::Jkit() {
        attach = 0;
        if (Jkit::javaVm_) {
            if (JNI_EDETACHED == javaVm_->GetEnv((void **) (&jniEnv), JNI_VERSION_1_4)) {
                javaVm_->AttachCurrentThread(&jniEnv, nullptr);
                attach = 1;
            }
        }
    }

    Jkit::~Jkit() {
        if (attach) {
            javaVm_->DetachCurrentThread();
        }
    }

    JavaVM *Jkit::nativeInit(JavaVM *vm) {
        if (!Jkit::javaVm_) {
            javaVm_ = vm;
        }
        return vm;
    }

    bool Jkit::IsNativeInited() {
        return (Jkit::javaVm_ != 0);
    }

    JNIEnv *Jkit::operator->() {
        return jniEnv;
    }

    bool Jkit::IsValidEnv() {
        return jniEnv != nullptr;
    }
} // namespace OHOS
