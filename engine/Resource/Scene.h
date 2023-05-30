//
// Created by ksiks_wa3r on 4/15/23.
//

#ifndef ANDROIDSIMPLEENGINE_SCENE_H
#define ANDROIDSIMPLEENGINE_SCENE_H

#include "Resource.h"
#include "../Log/Log.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/Instance.h"

namespace ASEngine {

	//scene instance descritor
	struct SceneInstanceDescriptor {
		GameObjectID objectId;
		vec2 position;
	};

	//scene id
	typedef std::string SceneID;

	class Scene: public Resource {
	public:
		//load scene from file
		static Scene load(const std::string& sceneName, const std::string& sceneFilePath);
		//preload all scenes
		static void importAll();
		//terminate all scenes
		static void terminate();

		//get current scene
		static SceneID getCurrentScene();

		//change scene
		static void changeSceneTo(const SceneID& sceneId);

		//reload current scene
		static void reloadCurrentScene();

		//equiv between ResourceID and Resource
		//= operator
		Scene& operator=(const SceneID& sceneId) {
			return scenes[sceneId];
		};

		//constructors
		Scene() {};
		Scene(const SceneID& sceneId) {
			*this = scenes[sceneId];
		};
	private:
		//scene content
		std::vector<SceneInstanceDescriptor> instances = {};
		//current scene
		static SceneID current;
		//scenes
		static std::unordered_map<ResourceID, Scene> scenes;
	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_SCENE_H
