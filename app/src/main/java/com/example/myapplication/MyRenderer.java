package com.example.myapplication;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.view.Surface;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyRenderer implements GLSurfaceView.Renderer {
    Context applicationContext;
    SurfaceView surface;
    // Used to load the 'nativetest' library on application startup.
    static {
        System.loadLibrary("myapplication");
    }

    MyRenderer(Context applicationContext, SurfaceView surface) {
        this.surface = surface;
        this.applicationContext = applicationContext;
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        init(applicationContext.getAssets(), surface.getHolder().getSurface());
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {
        surfaceChange(i, i1);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        update();
    }

    /**
     * A native method that is implemented by the 'myapplication' native library,
     * which is packaged with this application.
     */
    public native void init(AssetManager assetManager, Surface surface);
    public native void surfaceChange(int width, int height);
    public native void update();
}
