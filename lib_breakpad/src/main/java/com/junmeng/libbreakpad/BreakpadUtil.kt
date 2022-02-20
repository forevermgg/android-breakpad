package com.junmeng.libbreakpad

import java.io.File

object BreakpadUtil {
    private val mBreakpadCore: BreakpadCore = BreakpadCore()

    @JvmStatic
    fun init(
        dumpStorePath: String,//dump文件存储目录
        debug: Boolean = false //是否debug模式，是的话有日志打印
    ) {
        val file = File(dumpStorePath)
        if (file.isDirectory && !file.exists()) {
            file.mkdirs()
        }
        mBreakpadCore.init(dumpStorePath, debug)
    }

    @JvmStatic
    fun uninit() {
        mBreakpadCore.uninit()
    }

    @JvmStatic
    fun testNativeCrash() {
        mBreakpadCore.testNativeCrash()
    }
}