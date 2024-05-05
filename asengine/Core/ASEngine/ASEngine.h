
#ifndef ASENGINE_ASENGINE_H
#define ASENGINE_ASENGINE_H

#include <string>
#include <vector>

#include "Core/Singleton/Singleton.h"
#include "Core/String/UniqueStringManager.h"
#include "Module/ModuleManager.h"
#include "ECS/SystemManager.h"

namespace ASEngine 
{

	// asengine context 
	// defines the core of the engine 
	class ASEngine: public Singleton<ASEngine>
	{
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
	
	private:
		// console arguments
		std::vector<std::string> m_Arguments{};

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

#endif // ASENGINE_ASEngine_H
