package com.junmeng.breakpaddemo

import android.Manifest
import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import com.junmeng.breakpaddemo.jni.NativeCrashDemo
import com.junmeng.libbreakpad.BreakpadCore

class MainActivity : AppCompatActivity() {
    private var mBreakPad: BreakpadCore? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        mBreakPad = BreakpadCore()
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
        mBreakPad?.init(path, BuildConfig.DEBUG)
    }

    fun onClickUninit(view: View) {
        mBreakPad?.uninit()
    }

    /**
     * 验证breakpad内部奔溃能否成功dump
     */
    fun onClickNativeCrash(view: View) {
        mBreakPad?.testNativeCrash()
    }

    /**
     * 验证breakpad外部so奔溃能否成功dump
     */
    fun onClickNativeCrash2(view: View) {
        NativeCrashDemo().testNativeCrash()
    }
}