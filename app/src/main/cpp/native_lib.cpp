//
// Created by Administrator on 2017/12/8 0008.
//
#include <jni.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <android/log.h>

#define  LOG_TAG    "test===="
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

/**
 *  将 String 类型转成 char*类型
 */
extern "C"
JNIEXPORT char *Jstring2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);         //new   char[alen+1];
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_sonic_jnidemo1_JniUtil_getStringFromJni(JNIEnv *env, jobject instance) {
    // TODO
    std::string hello = "欢迎来到C的世界!";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_sonic_jnidemo1_JniUtil_getNewStr(JNIEnv *env, jobject thiz, jstring jstr) {
    //把java的字符串转换成c的字符串
    char *str = Jstring2CStr(env, jstr);
    //获取C字符串长度
    int cLength = strlen(str);
    //str每一个字符都+1
    for (int i = 0; i < cLength; i++) {
        *(str + i) += 1;
    }
    return env->NewStringUTF(str);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_sonic_jnidemo1_JniUtil_getSum(JNIEnv *env, jobject thiz, jint x, jint y) {
    return x + y;
}

/**
 * 冒泡排序
 */
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_sonic_jnidemo1_JniUtil_bubbleSort(JNIEnv *env, jobject thiz, jintArray jarr) {
    jboolean *isCopy = NULL;
    //获取数组首地址
    int *arr = env->GetIntArrayElements(jarr, isCopy);
    //获取数组长度
    int len = env->GetArrayLength(jarr);
    LOGE("len=%d",len);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    env->ReleaseIntArrayElements(jarr, arr, 0);
    //由于获取到数组的首地址，通过指针操作了元素过后，数组的每一个元素都已经被修改了
    //所以没有必要创建新的数组，直接返回jarr就可以
    return jarr;
}