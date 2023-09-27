
#ifndef ASENGINE_SCENE_H
#define ASENGINE_SCENE_H

#include <memory>

#include "Resource.h"
#include "ResourceManager.h"

#include "ECS/World.h"
#include "ECS/EntityBuilder.h"
#include "ECS/ComponentManager.h"
#include "ECS/Component.h"

#include "Core/Memory/DynamicArray.h"
#include "Core/Serialization/Serializer.h"
#include "Core/FileSystem/File.h"
#include "Core/Log/Log.h"

namespace ASEngine {

	class Scene: public Resource
	{
	public:
		// load scene from list of entities
		bool Load(TDynamicArray<EntityBuilder>& builders);

		// add entity
		void AddEntityBuilder(const EntityBuilder& builder);

		// get entity buidlers
		inline TDynamicArray<EntityBuilder>& GetEntityBuilders()
		{
			return m_Builders;
		};

		// instantiate a scene to the world
		void Instantiate(); 

		// load scene
		static void ChangeSceneTo(Scene& scene); 

	private:
		TDynamicArray<EntityBuilder> m_Builders{};
	};

} // ASEngine

#endif // ASENGINE_SCENE_H
