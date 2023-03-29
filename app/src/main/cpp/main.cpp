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
    ASEngine::Image image;
    ASEngine::Texture texture;
	std::string vertexCode;
    std::string fragmentCode;

    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
			if (pApp->userData != nullptr)
				break;
            //init input event
            ASEngine::InputEvent::init(pApp);

			//init renderer
            pApp->userData = new ASEngine::Context(pApp);
			ASEngine::Renderer::init();

            //init resource manager
            ASEngine::Resource::init(pApp->activity->assetManager);

			//load game objects
			loadGameObjects();

			//craete instance
			for (int i = 0; i < 1000; i++)
				ASEngine::Instance::create("MyObject");

            //load spr_run
            image = ASEngine::Image::load("sprites/spr_run.png");
            texture = ASEngine::Texture::load(image);
            ASEngine::Sprite::load("spr_run", texture, 6, ASEngine::vec2{24.0f, 24.0f});
			image.destroy();
            ALOG("spr_run loaded");

			//load default material
			vertexCode = ASEngine::Resource::loadAsText("materials/default.vert");
			fragmentCode = ASEngine::Resource::loadAsText("materials/default.frag");
			ASEngine::Material::load("mt_default", vertexCode, fragmentCode);
			ALOG("mt_default loaded");

			//load font
			ASEngine::Font::load("ft_pixel", 16, "fonts/joystix_monospace.otf", 4, 4, 16);


            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being destroyed. Use this to clean up your userData to avoid leaking
            // resources.
            //
            // We have to check if userData is assigned just in case this comes in really quickly
            if (pApp->userData) {
                //
                auto *context = reinterpret_cast<ASEngine::Context *>(pApp->userData);
                pApp->userData = nullptr;
                delete context;
            }
            break;
        default:
            break;
    }
}

/*!
 * This the main entry point for a native activity
 */
void android_main(struct android_app *pApp) {
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

            auto *context = reinterpret_cast<ASEngine::Context *>(pApp->userData);
            context->updateRenderArea();

            //update instance
            ASEngine::Instance::update(delta);

            //pool every input on queue
            for(size_t i = 0; i < pApp->motionEventsCount; ++i) {
                //pool event
                ASEngine::InputEvent event = ASEngine::InputEvent::poolEvent(i);
                //process event for each instance
                for (auto instance: ASEngine::Instance::instances) {
                    instance->onInputEvent(event);
                }
            }
            //clear
            android_app_clear_motion_events(pApp);

            // Render a frame
            ASEngine::Renderer::draw();

            //draw instance
            ASEngine::Instance::draw();

            //flush context
            context->flush();

			//time
			auto currentTime = std::chrono::high_resolution_clock::now();
			delta = std::chrono::duration_cast<std::chrono::microseconds>( currentTime - pastTime ).count() / SEC_TO_MICRO;
        }
    } while (!pApp->destroyRequested);
}
}