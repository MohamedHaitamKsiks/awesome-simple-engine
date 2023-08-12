
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
	// pool touch event
	for (size_t i = 0; i < app->motionEventsCount; ++i)
	{
		// pool event
		GameActivityMotionEvent motionEvent = app->motionEvents[i];
		for (int ptrIndex = 0; ptrIndex < motionEvent.pointerCount; ptrIndex++)
		{
			ProcessAndroidInputEvent(&motionEvent, ptrIndex);
		}
	}
	android_app_clear_motion_events(app);

	// render and update
	context->updateRenderArea();
	ASEngine::Application::Update(delta);
	context->flush();
}

void AndroidApplication::terminate() {
	ASEngine::Application::Terminate();
	delete context;
}

void AndroidApplication::ProcessAndroidInputEvent(const GameActivityMotionEvent *motionEvent, uint32_t ptrIndex)
{
	// create event
	ASEngine::InputEvent event;

	int action = motionEvent->action;
	int actionMasked = action & AMOTION_EVENT_ACTION_MASK;
	int actionPtrIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
	int pointerIndex = motionEvent->pointers[actionPtrIndex].id;

	vec2 pointerPosition;
	pointerPosition.x = GameActivityPointerAxes_getX(&motionEvent->pointers[ptrIndex]);
	pointerPosition.y = GameActivityPointerAxes_getY(&motionEvent->pointers[ptrIndex]);

	if (actionMasked == AMOTION_EVENT_ACTION_DOWN || actionMasked == AMOTION_EVENT_ACTION_POINTER_DOWN)
	{
		ASEngine::InputEventScreenTouch screenTouch;
		screenTouch.PointerIndex = pointerIndex;
		screenTouch.Position = pointerPosition;
		screenTouch.Pressed = true;

		event.Set(screenTouch);
	}
	else if (actionMasked == AMOTION_EVENT_ACTION_UP || actionMasked == AMOTION_EVENT_ACTION_POINTER_UP)
	{
		ASEngine::InputEventScreenTouch screenTouch;
		screenTouch.PointerIndex = pointerIndex;
		screenTouch.Position = pointerPosition;
		screenTouch.Pressed = false;

		event.Set(screenTouch);
	}
	else if (actionMasked == AMOTION_EVENT_ACTION_MOVE)
	{
		ASEngine::InputEventScreenDrag screenDrag;
		screenDrag.PointerIndex = pointerIndex;
		screenDrag.Position = pointerPosition;

		event.Set(screenDrag);
	}

	ASEngine::Application::QueueInputEvent(event);
}