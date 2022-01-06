#include <jni.h>
#include <string>
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"
#include "android/log.h"

#define LOG_TAG "libbreakpad"

google_breakpad::ExceptionHandler *exceptionHandler = nullptr;
bool debug = false;

void LOGI(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    if (debug) __android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, fmt, arg);
    va_end(arg);
}


bool DumpCallback(const google_breakpad::MinidumpDescriptor &descriptor,
                  void *context,
                  bool succeeded) {
    LOGI("DumpCallback Dump path: %s", descriptor.path());
    return succeeded;
}

void Crash() {
    volatile int *a = reinterpret_cast<volatile int *>(NULL);
    *a = 1;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_junmeng_libbreakpad_BreakpadCore_init(JNIEnv *env, jobject thiz, jstring _path,
                                               jboolean _debug) {
    debug = _debug;
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