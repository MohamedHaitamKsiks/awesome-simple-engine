//
// Created by ksiks_wa3r on 3/26/23.
//



#include "Context.h"

namespace ASEngine {

	void Context::init() {

		// Choose your render attributes
		constexpr EGLint attribs[] = {
				EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
				EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
				EGL_BLUE_SIZE, 8,
				EGL_GREEN_SIZE, 8,
				EGL_RED_SIZE, 8,
				EGL_DEPTH_SIZE, 24,
				EGL_NONE
		};

		// The default display is probably what you want on Android
		auto newDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		eglInitialize(newDisplay, nullptr, nullptr);

		// figure out how many configs there are
		EGLint numConfigs;
		eglChooseConfig(newDisplay, attribs, nullptr, 0, &numConfigs);

		// get the list of configurations
		std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
		eglChooseConfig(newDisplay, attribs, supportedConfigs.get(), numConfigs, &numConfigs);

		// Find a config we like.
		// Could likely just grab the first if we don't care about anything else in the config.
		// Otherwise hook in your own heuristic
		auto config = *std::find_if(
				supportedConfigs.get(),
				supportedConfigs.get() + numConfigs,
				[&newDisplay](const EGLConfig &config) {
					EGLint red, green, blue, depth;
					if (eglGetConfigAttrib(newDisplay, config, EGL_RED_SIZE, &red)
						&& eglGetConfigAttrib(newDisplay, config, EGL_GREEN_SIZE, &green)
						&& eglGetConfigAttrib(newDisplay, config, EGL_BLUE_SIZE, &blue)
						&& eglGetConfigAttrib(newDisplay, config, EGL_DEPTH_SIZE, &depth)) {

						return red == 8 && green == 8 && blue == 8 && depth == 24;
					}
					return false;
				});


		// create the proper window surface
		EGLint format;
		eglGetConfigAttrib(newDisplay, config, EGL_NATIVE_VISUAL_ID, &format);
		EGLSurface newSurface = eglCreateWindowSurface(newDisplay, config, app->window, nullptr);

		// Create a GLES 2 context
		EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
		EGLContext newContext = eglCreateContext(newDisplay, config, nullptr, contextAttribs);

		// get some window metrics
		auto madeCurrent = eglMakeCurrent(newDisplay, newSurface, newSurface, newContext);
		assert(madeCurrent);

		display = newDisplay;
		surface = newSurface;
		context = newContext;

		// make width and height invalid so it gets updated the first frame in @a updateRenderArea()
		width = -1;
		height = -1;

		ALOG("Context initialized");

	}


	void Context::updateRenderArea() {
		EGLint width_;
		eglQuerySurface(display, surface, EGL_WIDTH, &width_);

		EGLint height_;
		eglQuerySurface(display, surface, EGL_HEIGHT, &height_);

		if (width != width_ || height != height_) {
			width = width_;
			height = height_;
			glViewport(0, 0, width, height);
			Screen::setWindowSize(width, height);
		}
	}

	void Context::flush() {
		// Present the rendered image. This is an implicit glFlush.
		auto swapResult = eglSwapBuffers(display, surface);
		assert(swapResult == EGL_TRUE);
	}

} // ASEngine