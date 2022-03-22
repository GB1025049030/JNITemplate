//
// Created by guobin on 2022/3/10.
//

#ifndef JNITEMPLATE_JNI_ERROR_H
#define JNITEMPLATE_JNI_ERROR_H

namespace OHOS {
namespace TEMPLATE {
using ErrCode = int;

constexpr ErrCode ErrCodeOffset(unsigned int subsystem,
                                unsigned int module = 0) {
    constexpr int SUBSYSTEM_BIT_NUM = 21;
    constexpr int MODULE_BIT_NUM = 16;
    return (subsystem << SUBSYSTEM_BIT_NUM) | (module << MODULE_BIT_NUM);
}

constexpr ErrCode JNI_BUNDLEMGR_ERR_OFFSET = ErrCodeOffset(0, 0x02);

enum {
    ERR_JNI_PARSE_PROFILE_PROP_TYPE_ERROR = JNI_BUNDLEMGR_ERR_OFFSET + 0x0001,
    ERR_JNI_PARSE_PROFILE_MISSING_PROP,
};
}  // namespace TEMPLATE
}  // namespace OHOS

#endif  // JNITEMPLATE_JNI_ERROR_H
