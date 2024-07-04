
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
#include "Core/Memory/ByteBuffer.h"

#include "API/API.h"

namespace ASEngine 
{

	// asengine context 
	// defines the core of the engine
	class ASENGINE_API ASEngine
	{
	ASENGINE_DEFINE_SINGLETON(ASEngine);
	public:
		~ASEngine() = default;

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

		// set global attribute (needs to have a copy constructor)
		template<typename T>
		void SetGlobalAttribute(const std::string& name, const T& value)
		{
			// clean up any left attribute
			DestroyGlobalAttribute(name);

			// copy new dadta
			T* copy = new T(value);

			// create data
			GlobalAttribute& newAttribute = m_GlobalAttributes[name];
			newAttribute.Data = reinterpret_cast<void*>(copy);
			newAttribute.DestroyFunction = [](void* data)
			{
				delete reinterpret_cast<T*>(data);
			};
		}

		// get global attribute (make sure you get the correct type)
		template <typename T>
		const T& GetGlobalAttribute(const std::string& name) const
		{
			const T* data = reinterpret_cast<const T*>(m_GlobalAttributes.at(name).Data);
			return *data;
		}

	private:
		// console arguments
		std::vector<std::string> m_Arguments{};

		// global attributes (usefull to pass data from applications to asengine core)
		struct GlobalAttribute
		{
			void* Data = nullptr;
			
			// destroy function
			inline void Destroy()
			{
				DestroyFunction(Data);
			}

			std::function<void(void*)> DestroyFunction;

		};

		std::unordered_map<std::string, GlobalAttribute> m_GlobalAttributes{};

		// destroy attribute
		void DestroyGlobalAttribute(const std::string& name);

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
