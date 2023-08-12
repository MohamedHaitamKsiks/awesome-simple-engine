
#include "AndroidApplication.h"
#include "ecs/registry.h"

void AndroidApplication::init(android_app* _app) {
	app = _app;

	ASEngine::File::SetAssetManager(app->activity->assetManager);

	context = new AndroidEGLContext(app);

	ASEngine::Application::Create(ASEngine::Platform::ANDROID_DEVICES);
	ECSRegistry();

	ASEngine::Application::InitResourceManagers();
	ASEngine::Application::LoadProjectSettings();
}

void AndroidApplication::update(float delta) {
	context->updateRenderArea();
	ASEngine::Application::Update(delta);
	context->flush();
}

void AndroidApplication::terminate() {
	ASEngine::Application::Terminate();
	delete context;
}