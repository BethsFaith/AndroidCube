package com.Cube;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;

public class RendererWrapper implements Renderer {
    public void setShaders(String VertSource, String FragSource) {
        vertSource = VertSource;
        fragSource = FragSource;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        if (!JNIWrapper.compileShaders(vertSource, fragSource)) {
            Log.w("RendererWrapper", String.format("error shaders %s", JNIWrapper.err()));
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        if (!JNIWrapper.setUpGraphic(width, height)) {
            Log.w("RendererWrapper", String.format("error setUp graphic %s", JNIWrapper.err()));
        }
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        JNIWrapper.renderFrame();
    }

    private String vertSource;
    private String fragSource;
}