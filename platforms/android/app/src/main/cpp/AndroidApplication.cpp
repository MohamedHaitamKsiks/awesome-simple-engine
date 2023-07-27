
#include "AndroidApplication.h"

void AndroidApplication::init(android_app* _app) {
	app = _app;

	ASEngine::File::SetAssetManager(app->activity->assetManager);

	context = new AndroidEGLContext(app);

	ASEngine::Application::Create(ASEngine::Platform::ANDROID_DEVICES);
	ASEngine::Application::LoadProjectSettings();

	androidInputManager = new AndroidInputManager(app);
}

void AndroidApplication::update(float delta) {
	androidInputManager->processAndroidInput();

	context->updateRenderArea();
	ASEngine::Application::Update(delta);
	context->flush();
}

void AndroidApplication::terminate() {
	ASEngine::Application::Terminate();
	delete context;
	delete androidInputManager;
}