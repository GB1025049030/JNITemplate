//
// Created by guobin on 2021/12/14.
//

#ifndef RECENTDEMO_LOG_H
#define RECENTDEMO_LOG_H

#include"android/log.h"

#define LOG_TAG "System.out"
#define JNI_LOGF(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define JNI_LOGE(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define JNI_LOGW(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define JNI_LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define JNI_LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#endif //RECENTDEMO_LOG_H
