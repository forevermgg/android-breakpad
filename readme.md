# android--breakpad
* [![](https://www.jitpack.io/v/com.gitee.hijunmeng/android-breakpad.svg)](https://www.jitpack.io/#com.gitee.hijunmeng/android-breakpad)
* 一个捕获native奔溃的库

## 如何引用此库
* 本工程通过[JitPack | Publish JVM and Android libraries](https://www.jitpack.io/)进行发布
* 引用此库详见[https://www.jitpack.io/#com.gitee.hijunmeng/android-breakpad](https://www.jitpack.io/#com.gitee.hijunmeng/android-breakpad)

## so说明
去除符号表的so路径（此so作为release对外发布）:build/intermediates/stripped_native_libs
保留符号表的so路径（此so作为debug对内保存，切不可向外泄漏）：build/intermediates/cxx/Debug/472n6u65/obj

