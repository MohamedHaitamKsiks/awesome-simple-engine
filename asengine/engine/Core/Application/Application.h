
#ifndef ASENGINE_APPLICATION_H
#define ASENGINE_APPLICATION_H

#include "Core/Singleton/Singleton.h"

#include "Core/Memory/DynamicArray.h"
#include "Core/Window/Window.h"
#include "Core/String/UniqueString.h"
#include "Core/String/UniqueStringManager.h"
#include "Core/InputSystem/InputEvent.h"

#include "Audio/AudioEngine.h"

#include "Renderer/Viewport.h"
#include "Renderer/TextureManager.h"
#include "Renderer/2D/Renderer2D.h"

#include "Resource/ResourceManager.h"
#include "Resource/Font.h"
#include "Resource/Sprite.h"
#include "Resource/Image.h"
#include "Resource/Scene.h"
#include "Resource/Audio.h"

#include "ECS/World.h"

#include "Thirdparty/json.hpp"


namespace ASEngine {

	enum class Platform {
		ANDROID_DEVICES,
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

		// init resource managers
		static void InitResourceManagers();

		// create application for given platform
		static void Create(Platform platform);

		// get apllication running platform
		static inline Platform GetPlatform() { return GetSingleton()->m_Platform; };

		// get project setting
		static void LoadProjectSettings();

		// update application
		static void Update(float delta);

		// queue event
		static inline void QueueInputEvent(InputEvent& event)
		{
			GetSingleton()->m_InputEventQueue.Push(event);
		};
	
	private:
		void TerminateResourceManagers();

		// application platform
		Platform m_Platform = Platform::ANDROID_DEVICES;
		
		// event queue
		TDynamicArray<InputEvent> m_InputEventQueue{};
	};


} // ASEngine

#endif // ASENGINE_APPLICATION_H
