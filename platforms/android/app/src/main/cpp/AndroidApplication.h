//
// Created by ksiks_wa3r on 5/30/23.
//

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
	AndroidEGLContext* context;
	android_app* app;

};


#endif //ANDROIDSIMPLEENGINE_ANDROIDAPPLICATION_H
