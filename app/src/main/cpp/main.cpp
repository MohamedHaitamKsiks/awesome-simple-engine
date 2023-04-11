#define STB_IMAGE_IMPLEMENTATION

#include <jni.h>

#include "engine/asengine.h"
#include "Objects/MyObject/MyObject.h"
#include "Objects/loadGameObject.h"

#include <string>

#include <chrono>
#define SEC_TO_MICRO 1000000.0f;

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

extern "C" {

#include <game-activity/native_app_glue/android_native_app_glue.c>

/*!
 * Handles commands sent to this Android application
 * @param pApp the app the commands are coming from
 * @param cmd the command to handle
 */
void handle_cmd(android_app *pApp, int32_t cmd) {
	//game app
	ASEngine::Application* application;

	//start window
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
			if (pApp->userData != nullptr)
				break;
			//init application
			application = new ASEngine::Application();
			application->init(pApp);
            pApp->userData = application;
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being destroyed. Use this to clean up your userData to avoid leaking
            // resources.
            //
            // We have to check if userData is assigned just in case this comes in really quickly
            if (pApp->userData) {
                auto *application = reinterpret_cast<ASEngine::Application *>(pApp->userData);
                pApp->userData = nullptr;
				application->terminate();
                delete application;
            }
            break;
    }
}

/*!
 * This the main entry point for a native activity
 */
void android_main(struct android_app *pApp) {
	//load game objects
	loadGameObjects();
	//create instance 1000x to test the performance of the engine
	for (int i = 0; i < 10; i++)
		ASEngine::Instance::create("MyObject");

	//compute time
	float delta = 0.0f;

    //log
    ALOG("Starting Game Activity");

    // register an event handler for Android events
    pApp->onAppCmd = handle_cmd;

    // This sets up a typical game/event loop. It will run until the app is destroyed.
    int events;
    android_poll_source *pSource;

    do {
		//get time now
		auto pastTime = std::chrono::high_resolution_clock::now();

        // Process all pending events before running game logic.
        if (ALooper_pollAll(0, nullptr, &events, (void **) &pSource) >= 0) {
            if (pSource) {
                pSource->process(pApp, pSource);
            }
        }

        // Check if any user data is associated. This is assigned in handle_cmd
        if (pApp->userData) {

            // We know that our user data is a Renderer, so reinterpret cast it. If you change your
            // user data remember to change it here

            auto *application = reinterpret_cast<ASEngine::Application *>(pApp->userData);

			//pool application event
			application->poolAndroidInput(pApp);

            //clear
            android_app_clear_motion_events(pApp);

            //update app
			application->update(delta);

			//time
			auto currentTime = std::chrono::high_resolution_clock::now();
			delta = std::chrono::duration_cast<std::chrono::microseconds>( currentTime - pastTime ).count() / SEC_TO_MICRO;
        }
    } while (!pApp->destroyRequested);
}
}