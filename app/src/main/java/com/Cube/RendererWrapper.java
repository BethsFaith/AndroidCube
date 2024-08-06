package com.Cube;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;

public class RendererWrapper implements Renderer {
    public void setShaders(String VertSource, String FragSource) {
        vertSource = VertSource;
        fragSource = FragSource;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        JNIWrapper.compileShaders(vertSource, fragSource);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        JNIWrapper.setUpGraphic(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        JNIWrapper.renderFrame();
    }

    private String vertSource;
    private String fragSource;
}