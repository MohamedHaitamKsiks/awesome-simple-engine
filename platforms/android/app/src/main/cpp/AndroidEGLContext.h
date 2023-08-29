
#ifndef ANDROIDSIMPLEENGINE_ANDROIDEGLCONTEXT_H
#define ANDROIDSIMPLEENGINE_ANDROIDEGLCONTEXT_H

#include "ASEngine.h"

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include <assert.h>
#include <memory>
#include <algorithm>

#include <game-activity/native_app_glue/android_native_app_glue.h>


class AndroidEGLContext {

public:
	inline AndroidEGLContext(android_app* pApp):
	app(pApp),
			display(EGL_NO_DISPLAY),
			surface(EGL_NO_SURFACE),
			context(EGL_NO_CONTEXT),
			width(0),
	height(0) {
		init();
	}

	//destroy context
	~AndroidEGLContext();

	//update area
	void updateRenderArea();
	//flush
	void flush();

private:
	void init();

	//context data
	android_app* app;
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	EGLint width;
	EGLint height;

};


#endif //ANDROIDSIMPLEENGINE_ANDROIDEGLCONTEXT_H
