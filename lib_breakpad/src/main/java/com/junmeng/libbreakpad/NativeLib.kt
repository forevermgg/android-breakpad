package com.junmeng.libbreakpad

class NativeLib {

    /**
     * A native method that is implemented by the 'libbreakpad' native library,
     * which is packaged with this application.
     */
    external fun testNativeCrash()

    external fun init(path:String)
    external fun uninit()

    companion object {
        // Used to load the 'libbreakpad' library on application startup.
        init {
            System.loadLibrary("libbreakpad")
        }
    }
}