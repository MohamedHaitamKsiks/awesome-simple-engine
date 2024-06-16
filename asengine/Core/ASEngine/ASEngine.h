
#ifndef __ASENGINE_ASENGINE_H
#define __ASENGINE_ASENGINE_H

#include <string>
#include <vector>

#include "Core/Singleton/Singleton.h"
#include "Core/String/UniqueStringManager.h"
#include "Class/ClassManager.h"


#include "Module/ModuleManager.h"

#include "ECS/SystemManager.h"
#include "ECS/ComponentManager.h"

#include "Resource/ResourceManager.h"

#include "Core/Settings/Settings.h"

namespace ASEngine 
{

	// asengine context 
	// defines the core of the engine 
	class ASEngine
	{
	ASENGINE_DEFINE_SINGLETON(ASEngine);
	public:
		// setup application before init and user registry
		void Setup();

		// setup application with args 
		void Setup(int argc, char* argv[]);

		// init application systems ...
		void Init();

		// application cleanup
		void Terminate();

		// update application
		void Update(float delta);

		// queue event
		inline void QueueInputEvent(const InputEvent& event)
		{
			m_InputEventQueue.push_back(event);
		};

		// get arguments
		inline const std::vector<std::string>& GetArguments() const
		{
			return m_Arguments;
		}

		// get settings
		inline const Settings& GetSettings() const
		{
			return m_Settings;
		}

		// set time scale
		inline void SetTimeScale(float timeScale)
		{
			m_TimeScale = timeScale;
		}

		// get time scale
		inline float GetTimeScale() const
		{
			return m_TimeScale;
		}

	private:
		// console arguments
		std::vector<std::string> m_Arguments{};

		// event queue
		std::vector<InputEvent> m_InputEventQueue{};

		// time
		float m_FixedTimer = 0.0f;
		float m_TimeScale = 1.0f;

		// default managers
		ComponentManager m_ComponentManager{};
		ResourceManager m_ResourceManager{};
		UniqueStringManager m_UniqueStringManager{};
		ClassManager m_ClassManager{};
		ModuleManager m_ModuleManager{};
		SystemManager m_SystemManager{};

		// settings
		Settings m_Settings;

		// register all builtin systems before any user system
		void RegisterBuiltInSystems();

		// get project setting
		void LoadProjectSettings();
	};


} // ASEngine

#endif // __ASENGINE_ASEngine_H
