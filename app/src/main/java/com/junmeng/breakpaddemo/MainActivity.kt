package com.junmeng.breakpaddemo

import android.Manifest
import android.os.Bundle
import android.view.View
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import com.junmeng.breakpaddemo.jni.NativeCrashDemo
import com.junmeng.libbreakpad.BreakpadCore
import com.junmeng.libbreakpad.BreakpadUtil

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    fun onClickPermission(view: View) {
        ActivityCompat.requestPermissions(
            this,
            arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE),
            123
        )
    }

    fun onClickInit(view: View) {
        val path = externalCacheDir?.absolutePath ?: ""
        findViewById<TextView>(R.id.filePath).text = "日志存储路径：$path"
        BreakpadUtil.init("$path/crash", BuildConfig.DEBUG)
    }

    fun onClickUninit(view: View) {
        BreakpadUtil.uninit()
    }

    /**
     * 验证breakpad内部奔溃能否成功dump
     */
    fun onClickNativeCrash(view: View) {
        BreakpadUtil.testNativeCrash()
    }

    /**
     * 验证breakpad外部so奔溃能否成功dump
     */
    fun onClickNativeCrash2(view: View) {
        NativeCrashDemo().testNativeCrash()
    }
}