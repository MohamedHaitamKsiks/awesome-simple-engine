//
// Created by ksiks_wa3r on 4/15/23.
//

#include "Scene.h"

namespace ASEngine {

	std::unordered_map<ResourceID, Scene> Scene::scenes = {};
	//current scene
	SceneID Scene::current = "";

	SceneID Scene::getCurrentScene() {
		return current;
	}

	Scene Scene::load(const std::string &sceneName, const std::string &sceneFilePath) {
		//create scene
		Scene scene{};
		scene.id = sceneName;
		//load json file
		std::string sceneDataString = Resource::loadAsText(sceneFilePath);
		//parse to json
		nlohmann::json sceneData = nlohmann::json::parse(sceneDataString);
		//add instances
		for (int i = 0; i < sceneData["instances"].size(); i++) {
			GameObjectID instanceObjectId = sceneData["instances"][i]["name"];
			float instancePositionX = sceneData["instances"][i]["position"]["x"];
			float instancePositionY = sceneData["instances"][i]["position"]["y"];
			vec2 instancePosition = vec2{
				instancePositionX,
				instancePositionY
			};
			//create instance descriptor
			SceneInstanceDescriptor descriptor{
				instanceObjectId,
				instancePosition
			};
			//add to scene instances
			scene.instances.push_back(descriptor);
		}
		//add scene to scenes
		scenes[sceneName] = scene;
		return scene;
	}

	void Scene::importAll() {
		//load json file
		std::string importedScenesString = Resource::loadAsText("scenes/import.scenes.json");
		//parse to json
		nlohmann::json importedScenes = nlohmann::json::parse(importedScenesString);
		//add instances
		for (int i = 0; i < importedScenes.size(); i++) {
			std::string sceneName = importedScenes[i]["name"];
			std::string sceneFilePath = importedScenes[i]["file"] ;
			Scene::load(sceneName, "scenes/" + sceneFilePath);
		}
	}

	void Scene::terminate() {
		scenes.clear();
	}

	void Scene::changeSceneTo(const std::string &sceneId) {
		//change current scene
		current = sceneId;
		Scene scene = sceneId;
		//destroy all instances
		Instance::destroyAll();
		//instance create
		for(const auto& instanceDescriptor: scene.instances) {
			GameObject* instance = Instance::create(instanceDescriptor.objectId);
			instance->position = instanceDescriptor.position;
		}
		Log::out("change scene");
	}

	void Scene::reloadCurrentScene() {
		changeSceneTo(current);
	}


} // ASEngine