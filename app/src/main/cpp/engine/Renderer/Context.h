//
// Created by ksiks_wa3r on 3/26/23.
//

#ifndef ANDROIDSIMPLEENGINE_CONTEXT_H
#define ANDROIDSIMPLEENGINE_CONTEXT_H

#include "../log.h"
#include "Screen.h"
#include <assert.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <memory>
#include <algorithm>

#include <game-activity/native_app_glue/android_native_app_glue.h>

namespace ASEngine {

	class Context {

	public:

		inline Context(android_app* pApp):
			app(pApp),
			display(EGL_NO_DISPLAY),
			surface(EGL_NO_SURFACE),
			context(EGL_NO_CONTEXT),
			width(0),
			height(0) {
			init();
		}

		//destroy context
		~Context();

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

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_CONTEXT_H
