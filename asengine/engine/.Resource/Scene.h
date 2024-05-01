
#ifndef ASENGINE_SCENE_H
#define ASENGINE_SCENE_H

#include <memory>

#include "Resource.h"
#include "ResourceManager.h"

#include "ECS/EntityBuilder.h"

namespace ASEngine {

	class Scene: public Resource
	{
	public:
		// load scene from list of entities
		bool Load(TDynamicArray<EntityBuilder>& builders);

		// load scene from path
		bool Load(const std::string &path);

		// add entity
		void AddEntityBuilder(const EntityBuilder& builder);

		// get entity buidlers
		inline TDynamicArray<EntityBuilder>& GetEntityBuilders()
		{
			return m_Builders;
		};

		// instantiate a scene to the EntityManager
		void Instantiate(); 

		// load scene
		static void ChangeSceneTo(Scene& scene); 

	private:
		TDynamicArray<EntityBuilder> m_Builders{};
	};

} // ASEngine

#endif // ASENGINE_SCENE_H
