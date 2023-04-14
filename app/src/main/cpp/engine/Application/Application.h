//
// Created by ksiks_wa3r on 4/10/23.
//

#ifndef ANDROIDSIMPLEENGINE_APPLICATION_H
#define ANDROIDSIMPLEENGINE_APPLICATION_H

#include <game-activity/native_app_glue/android_native_app_glue.h>

#include "../Renderer/Renderer.h"
#include "../Renderer/Context.h"
#include "../Renderer/Graphics.h"

#include "../Resource/Material.h"
#include "../Resource/Font.h"
#include "../Resource/Sprite.h"
#include "../Resource/Image.h"

#include "../GameObject/GameObject.h"
#include "../GameObject/Instance.h"

#include "../InputEvent/InputEvent.h"


namespace ASEngine {

	class Application {
	public:
		//init application
		void init(android_app* app);

		//process android input
		void poolAndroidInput(android_app* app);

		//update
		void update(float delta);

		//terminate
		void terminate();
	private:
		Renderer renderer{};
		Context* context;
		Graphics graphics{};
		//process input
		void onInputEvent(InputEvent& inputEvent);

	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_APPLICATION_H
