package com.Cube;

public class JNIWrapper {
    // Used to load the 'Cube' library on application startup.
    static {
        System.loadLibrary("Cube");
    }

    /**
     * A native method that is implemented by the 'Cube' native library,
     * which is packaged with this application.
     */
    public static native String err();

    public static native boolean compileShaders(String vertSource, String fragSource);

    public static native boolean setUpGraphic(int width, int height);

    public static native void renderFrame();
}
