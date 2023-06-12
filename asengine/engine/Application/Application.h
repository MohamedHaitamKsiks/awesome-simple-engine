
#ifndef ASENGINE_APPLICATION_H
#define ASENGINE_APPLICATION_H


#include "../Renderer/Renderer.h"
#include "../Renderer/Graphics.h"

#include "../Resource/ResourceManager.h"
#include "../Resource/Font.h"
#include "../Resource/Sprite.h"
#include "../Resource/Image.h"
#include "../Resource/Scene.h"

#include "../GameObject/GameObject.h"
#include "../GameObject/Instance.h"

#include "../InputEvent/InputEvent.h"

#include "../Thirdparty/json.hpp"


namespace ASEngine {

	enum Platform {
		PLATFORM_ANDROID,
		PLATFORM_DESKTOP
	};

	//application
	class Application {
	public:
		static void create(Platform _platform);
		static Application* getSingleton();
		Application(Platform _platform);

		Platform getPlatform();

		void init();
		void update(float delta);
		void onInputEvent(InputEvent& inputEvent);
		void terminate();
	private:
		//application platform
		Platform platform = PLATFORM_ANDROID;
		//graphics objects
		Renderer renderer{};
		Graphics graphics{};
		//get project setting
		void loadProjectSettings();
		//singleton
		static Application* application;

	};


} // ASEngine

#endif // ASENGINE_APPLICATION_H
