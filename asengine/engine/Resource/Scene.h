//
// Created by ksiks_wa3r on 4/15/23.
//

#ifndef ANDROIDSIMPLEENGINE_SCENE_H
#define ANDROIDSIMPLEENGINE_SCENE_H

#include "Resource.h"
#include "ResourceManager.h"
#include "../FileSystem/File.h"
#include "../Log/Log.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/Instance.h"

namespace ASEngine {

	//scene instance descritor
	struct SceneInstanceDescriptor {
		GameObjectID objectId;
		vec2 position;
	};

	class Scene: public Resource {
	public:
		//load scene from file
		bool load(const std::string& sceneFilePath);

		static void importAll();

	private:
		//scene content
		std::vector<SceneInstanceDescriptor> instances = {};
		
	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_SCENE_H
