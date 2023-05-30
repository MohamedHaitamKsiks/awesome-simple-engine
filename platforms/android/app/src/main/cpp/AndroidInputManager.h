//
// Created by ksiks_wa3r on 5/30/23.
//

#ifndef ANDROIDSIMPLEENGINE_ANDROIDINPUTMANAGER_H
#define ANDROIDSIMPLEENGINE_ANDROIDINPUTMANAGER_H

#include "engine/asengine.h"

#include <game-activity/native_app_glue/android_native_app_glue.h>


class AndroidInputManager {
public:
	AndroidInputManager(android_app* _app);
	void processAndroidInput();

private:
	android_app* app;
	ASEngine::InputEvent bake(int eventIndex);

};


#endif //ANDROIDSIMPLEENGINE_ANDROIDINPUTMANAGER_H
