package com.junmeng.breakpaddemo.jni

class NativeCrashDemo {
    companion object {
        init {
            System.loadLibrary("crashdemo")
        }
    }

    /**
     * 测试产生奔溃
     */
    external fun testNativeCrash()
}