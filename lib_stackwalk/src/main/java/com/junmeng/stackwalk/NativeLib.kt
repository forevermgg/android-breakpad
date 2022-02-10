package com.junmeng.stackwalk

class NativeLib {

    /**
     * A native method that is implemented by the 'stackwalk' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'stackwalk' library on application startup.
        init {
            System.loadLibrary("stackwalk")
        }
    }
}