#ifndef LIBBREAKPAD_GJVM_H
#define LIBBREAKPAD_GJVM_H


#include <jni.h>

void setJvm(JavaVM * jvm);

JavaVM* getJvm();

#endif //LIBBREAKPAD_GJVM_H