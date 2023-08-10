
#ifndef ASENGINE_SCENE_H
#define ASENGINE_SCENE_H

#include <memory>

#include "Resource.h"
#include "ResourceManager.h"

#include "engine/ECS/World.h"
#include "engine/ECS/EntityBuilder.h"
#include "engine/ECS/ComponentManager.h"
#include "engine/ECS/Component.h"

#include "engine/Memory/DynamicArray.h"
#include "engine/Serialization/Serializer.h"
#include "engine/FileSystem/File.h"
#include "engine/Log/Log.h"

namespace ASEngine {

	class Scene: public Resource
	{
	public:
		// load scene from list of entities
		bool Load(TDynamicArray<EntityBuilder>& builders);

		// add entity
		void AddEntityBuilder(const EntityBuilder& builder);

		// instantiate a scene to the world
		void Instantiate(); 

	private:
		TDynamicArray<EntityBuilder> m_Builders{};
	};

} // ASEngine

#endif // ASENGINE_SCENE_H
