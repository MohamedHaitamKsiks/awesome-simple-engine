//
// Created by ksiks_wa3r on 5/30/23.
//

#include "AndroidApplication.h"

void AndroidApplication::init(android_app* _app) {
	app = _app;

	ASEngine::Resource::init(app->activity->assetManager);

	context = new AndroidEGLContext(app);

	ASEngine::Application::create(ASEngine::PLATFORM_ANDROID);
	ASEngine::Application::getSingleton()->init();

	androidInputManager = new AndroidInputManager(app);
}

void AndroidApplication::update(float delta) {
	androidInputManager->processAndroidInput();

	context->updateRenderArea();
	ASEngine::Application::getSingleton()->update(delta);
	context->flush();
}

void AndroidApplication::terminate() {
	ASEngine::Application::getSingleton()->terminate();
	delete context;
	delete androidInputManager;
}