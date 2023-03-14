package com.example.myapplication;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class SurfaceView extends GLSurfaceView {
    private MyRenderer renderer;
    public SurfaceView(Context context) {
        super(context);
        setEGLContextClientVersion(2);
        renderer = new MyRenderer(context, this);

        setRenderer(renderer);
    }

    public MyRenderer getRenderer() {
        return renderer;
    }
}
