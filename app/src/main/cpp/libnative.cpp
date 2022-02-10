#include <jni.h>

void Crash() {
    volatile int *a = reinterpret_cast<volatile int *>(NULL);
    *a = 1;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_breakpaddemo_jni_NativeCrashDemo_testNativeCrash(JNIEnv *env, jobject thiz) {
    Crash();
}