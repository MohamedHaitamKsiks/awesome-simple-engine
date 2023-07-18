
#ifndef ASENGINE_APPLICATION_H
#define ASENGINE_APPLICATION_H

#include "engine/Singleton/Singleton.h"

#include "engine/Window/Window.h"

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

	enum class Platform {
		ANDROID,
		DESKTOP
	};

	//application
	class Application:public Singleton<Application> {
	public:
		// constructors
		Application(){};
		Application(Platform platform);

		// destructor
		~Application();

		// create application for given platform
		static void Create(Platform platform);

		// get apllication running platform
		static inline Platform GetPlatform() { return GetSingleton()->m_Platform; };

		// get project setting
		static void LoadProjectSettings();

		// update application
		static void Update(float delta);
		
		// application on event
		static inline void OnInputEvent(InputEvent &inputEvent) { GetSingleton()->IOnInputEvent(inputEvent); };

	private:
		void IOnInputEvent(InputEvent &inputEvent);

		//application platform
		Platform m_Platform = Platform::ANDROID;

	};


} // ASEngine

#endif // ASENGINE_APPLICATION_H
