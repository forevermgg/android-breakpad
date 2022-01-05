#include <jni.h>
#include <string>
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"
#include "android/log.h"

google_breakpad::ExceptionHandler *exceptionHandler = nullptr;

bool DumpCallback(const google_breakpad::MinidumpDescriptor &descriptor,
                  void *context,
                  bool succeeded) {
    __android_log_print(ANDROID_LOG_INFO, "123456", "DumpCallback Dump path: %s", descriptor.path());
    return succeeded;
}

void Crash() {
    volatile int *a = reinterpret_cast<volatile int *>(NULL);
    *a = 1;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libbreakpad_NativeLib_uninit(JNIEnv *env, jobject thiz) {
    if (exceptionHandler != nullptr) {
        delete exceptionHandler;
        exceptionHandler = nullptr;
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libbreakpad_NativeLib_init(JNIEnv *env, jobject thiz, jstring _path) {
    const char *path = env->GetStringUTFChars(_path, 0);
    __android_log_print(ANDROID_LOG_INFO, "123456", "init Dump path: %s", path);
    if (exceptionHandler == nullptr) {
        google_breakpad::MinidumpDescriptor descriptor(path);
        exceptionHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, DumpCallback,
                                                                 NULL, true, -1);
    }
    env->ReleaseStringUTFChars(_path, path);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libbreakpad_NativeLib_testNativeCrash(JNIEnv *env, jobject thiz) {
    Crash();
}