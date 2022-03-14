package com.pandon.jnilib;

public class NativeLib {

    // Used to load the 'jnilib' library on application startup.
    static {
        System.loadLibrary("jnilib");
    }

    public static native void nativeInit();
}