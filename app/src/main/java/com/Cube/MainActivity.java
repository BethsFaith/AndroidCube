package com.Cube;

import android.annotation.SuppressLint;
import android.app.ActionBar;
import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.content.res.Resources;
import android.graphics.Color;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class MainActivity extends Activity implements View.OnTouchListener {
    private GLSurfaceView glSurfaceView;
    private boolean rendererSet;
    private Switch swtchB;
    private float lastX;
    private float lastY;

    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityManager activityManager
                = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();

        final boolean supportsEs2 =
                configurationInfo.reqGlEsVersion >= 0x30000 || isProbablyEmulator();

        if (supportsEs2) {
            Resources resources = getResources();

            StringBuilder vertSource = new StringBuilder();
            StringBuilder fragSource = new StringBuilder();

            try (InputStream vertInputStream = resources.openRawResource(R.raw.shader_v)) {
                String str = "";
                BufferedReader reader = new BufferedReader(new InputStreamReader(vertInputStream));
                while ((str = reader.readLine()) != null) {
                    vertSource.append(str).append("\n");
                }
            } catch (IOException e) {
                Toast.makeText(this, "Can't load the vertex shader",
                        Toast.LENGTH_LONG).show();
            }

            try (InputStream fragInputStream = resources.openRawResource(R.raw.shader_f)) {
                String str = "";
                BufferedReader reader = new BufferedReader(new InputStreamReader(fragInputStream));
                while ((str = reader.readLine()) != null) {
                    fragSource.append(str).append("\n");
                }
            }
            catch (IOException e) {
                Toast.makeText(this, "Can't load the fragment shader",
                        Toast.LENGTH_LONG).show();
            }

            RendererWrapper rendererWrapper = new RendererWrapper();
            rendererWrapper.setShaders(vertSource.toString(), fragSource.toString());

            glSurfaceView = new GLSurfaceView(this);

            if (isProbablyEmulator()) {
                // Avoids crashes on startup with some emulator images.
                glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
            }

            glSurfaceView.setEGLContextClientVersion(3);
            glSurfaceView.setRenderer(rendererWrapper);
            glSurfaceView.setOnTouchListener(this);
            rendererSet = true;
            setContentView(glSurfaceView);

            this.swtchB = new Switch(this);
            swtchB.setText("Rotate");
            swtchB.setTranslationX(10);
            swtchB.setTextColor(Color.BLACK);
            addContentView(swtchB, new ActionBar.LayoutParams(ActionBar.LayoutParams.WRAP_CONTENT, ActionBar.LayoutParams.WRAP_CONTENT));
            swtchB.setOnCheckedChangeListener(new Switch.OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(CompoundButton buttonView,
                                             boolean isChecked) {
                    if (isChecked) {
                        Toast.makeText(MainActivity.this,
                                        "Rotate mode", Toast.LENGTH_SHORT)
                                .show();

                    } else {
                        Toast.makeText(MainActivity.this,
                                        "Orbit mode", Toast.LENGTH_SHORT)
                                .show();
                    }
                }
            });
        } else {
            // Should never be seen in production, since the manifest filters
            // unsupported devices.
            Toast.makeText(this, "This device does not support OpenGL ES 3.0.",
                    Toast.LENGTH_LONG).show();
            return;
        }
    }
    private boolean isProbablyEmulator() {
        return Build.FINGERPRINT.startsWith("generic") || Build.FINGERPRINT.startsWith("unknown")
                || Build.MODEL.contains("google_sdk") || Build.MODEL.contains("Emulator")
                || Build.MODEL.contains("Android SDK built for x86");
    }

    @Override
    protected void onPause() {
        super.onPause();

        if (rendererSet) {
            glSurfaceView.onPause();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();

        if (rendererSet) {
            glSurfaceView.onResume();
        }
    }

    @Override
    protected void onStop() {
        super.onStop();

        if (rendererSet) {
            glSurfaceView.onPause();
        }
    }

    @Override
    protected void onRestart() {
        super.onRestart();

        if (rendererSet) {
            glSurfaceView.onResume();
        }
    }

    @Override
    public boolean onTouch(View view, MotionEvent motionEvent) {
        switch (motionEvent.getAction()) {
            case MotionEvent.ACTION_DOWN: // нажатие
                break;
            case MotionEvent.ACTION_MOVE: // движение
                if (swtchB.isChecked()) {
                    if (lastX < motionEvent.getX()) {
                        JNIWrapper.rotate(0, 1, 0);
                    } else if (lastX > motionEvent.getX()) {
                        JNIWrapper.rotate(0, -1, 0);
                    }
                } else {
                    JNIWrapper.orbit(false);
                }
                break;
            case MotionEvent.ACTION_UP: // отпускание
            case MotionEvent.ACTION_CANCEL:
                break;
        }

        lastX = motionEvent.getX();
        lastY = motionEvent.getY();

        return true;
    }
}