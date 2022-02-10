#include "GJvm.h"


static JavaVM* gJvm=nullptr;

void setJvm(JavaVM * jvm){
    gJvm=jvm;
}

JavaVM* getJvm(){
    return gJvm;
}