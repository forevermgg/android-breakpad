package com.junmeng.libbreakpad

import androidx.annotation.Keep

@Keep
class BreakpadCore {
    companion object {
        init {
            System.loadLibrary("breakpad")
        }
    }


    /**
     * 初始化
     */
    external fun init(
        dumpStorePath: String,//dump文件存储目录，需用户自己保证存在
        debug: Boolean = false //是否debug模式，是的话有日志打印
    )

    /**
     * 释放资源
     */
    external fun uninit()

    /**
     * 产生奔溃，测试用
     */
    external fun testNativeCrash()


}