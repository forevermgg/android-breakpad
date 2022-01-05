package com.junmeng.breakpaddemo

import android.Manifest
import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import com.junmeng.libbreakpad.NativeLib

class MainActivity : AppCompatActivity() {
    private var mBreakPad: NativeLib? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        mBreakPad = NativeLib()
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
        mBreakPad?.init(path)
    }

    fun onClickUninit(view: View) {
        mBreakPad?.uninit()
    }

    fun onClickNativeCrash(view: View) {
        mBreakPad?.testNativeCrash()
    }
}