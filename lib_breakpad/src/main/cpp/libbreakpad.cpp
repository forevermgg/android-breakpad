#include <jni.h>
#include <string>
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"
#include "ALog.h"
#include "GJvm.h"

#define  LOG_TAG    "libbreakpad"

google_breakpad::ExceptionHandler *exceptionHandler = nullptr;

bool DumpCallback(const google_breakpad::MinidumpDescriptor &descriptor,
                  void *context,
                  bool succeeded) {
    LOGI(LOG_TAG, "DumpCallback Dump path: %s", descriptor.path());
    return succeeded;
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI(LOG_TAG, "JNI_OnLoad");
    //当Android的VM(Virtual Machine)执行到C组件(即so)里的System.loadLibrary()函数时便会执行JNI_OnLoad函数

    //因此可以在此执行一些初始化的工作，比如函数动态注册等


    //先保存jvm
    setJvm(vm);

    LOGI("JNI_OnLoad end");
    //返回值告诉vm使用的jni版本，如果没有JNI_OnLoad函数，那么默认是最旧的1.1版本
    //由于新版的JNI做了许多扩充，如果需要使用JNI的新版功能，
    //例如JNI 1.4的java.nio.ByteBuffer,就必须藉由JNI_OnLoad()函数来告知VM
    return JNI_VERSION_1_4;

}

void Crash() {
    volatile int *a = reinterpret_cast<volatile int *>(NULL);
    *a = 1;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libbreakpad_BreakpadCore_init(JNIEnv *env, jobject thiz, jstring _path,
                                               jboolean _debug) {
    setLogSwitch(_debug);
    const char *path = env->GetStringUTFChars(_path, 0);
    LOGI("init Dump path: %s", path);
    if (exceptionHandler == nullptr) {
        google_breakpad::MinidumpDescriptor descriptor(path);
        exceptionHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, DumpCallback,
                                                                 NULL, true, -1);
    }
    env->ReleaseStringUTFChars(_path, path);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libbreakpad_BreakpadCore_uninit(JNIEnv *env, jobject thiz) {
    if (exceptionHandler != nullptr) {
        delete exceptionHandler;
        exceptionHandler = nullptr;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libbreakpad_BreakpadCore_testNativeCrash(JNIEnv *env, jobject thiz) {
    Crash();
}