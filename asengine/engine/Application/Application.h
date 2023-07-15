
#ifndef ASENGINE_APPLICATION_H
#define ASENGINE_APPLICATION_H

#include "engine/Renderer/Renderer.h"
#include "engine/Renderer/Graphics.h"

#include "engine/Resource/ResourceManager.h"
#include "engine/Resource/Font.h"
#include "engine/Resource/Sprite.h"
#include "engine/Resource/Image.h"
#include "engine/Resource/Scene.h"

#include "engine/String/UniqueString.h"
#include "engine/String/UniqueStringManager.h"

#include "engine/InputEvent/InputEvent.h"

#include "engine/ECS/World.h"

#include "engine/Thirdparty/json.hpp"


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
