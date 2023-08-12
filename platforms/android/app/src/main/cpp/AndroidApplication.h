
#ifndef ANDROIDSIMPLEENGINE_ANDROIDAPPLICATION_H
#define ANDROIDSIMPLEENGINE_ANDROIDAPPLICATION_H

#include "AndroidEGLContext.h"

#include "engine/asengine.h"

class AndroidApplication {

public:
	void init(android_app* _app);
	void update(float delta);
	void terminate();

private:
	AndroidEGLContext* context = nullptr;
	android_app* app = nullptr;

	void ProcessAndroidInputEvent(const GameActivityMotionEvent *motionEvent, uint32_t ptrIndex);
};


#endif //ANDROIDSIMPLEENGINE_ANDROIDAPPLICATION_H
