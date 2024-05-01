
#ifndef ASENGINE_APPLICATION_H
#define ASENGINE_APPLICATION_H

#include <vector>

#include "Core/Singleton/Singleton.h"
#include "Core/String/UniqueStringManager.h"
#include "Module/ModuleManager.h"
#include "ECS/SystemManager.h"

namespace ASEngine 
{

	//application 
	class Application: Singleton<Application>
	{
	public:
		// init application systems ...
		void Init();

		// setup application before init and user registry
		void Setup(); 

		// application cleanup
		void Terminate();

		// update application
		void Update(float delta);

		// queue event
		inline void QueueInputEvent(const InputEvent& event)
		{
			m_InputEventQueue.push_back(event);
		};
	
	private:
		// event queue
		std::vector<InputEvent> m_InputEventQueue{};

		// fixed time step
		float m_FixedTimer = 0.0f;

		// default managers
		UniqueStringManager m_UniqueStringManager{};
		ModuleManager m_ModuleManager{};
		SystemManager m_SystemManager{};

		// register all builtin systems before any user system
		void RegisterBuiltInSystems();

		// get project setting
		void LoadProjectSettings();
	};


} // ASEngine

#endif // ASENGINE_APPLICATION_H
