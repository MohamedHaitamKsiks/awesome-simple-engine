//
// Created by ksiks_wa3r on 4/15/23.
//

#include "Scene.h"

namespace ASEngine {

	bool Scene::load(const std::string &sceneFilePath) {
		//load json file
		File sceneFile;
		if(!sceneFile.open(sceneFilePath, FILE_OPEN_MODE_READ))
		{
			Log::out("Couldn't load scene!");
			return false;
		}
		
		
		//parse to json
		std::string sceneDataString = sceneFile.readText();
		nlohmann::json sceneData = nlohmann::json::parse(sceneDataString);
		
		//add instances
		instances.clear();
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
			instances.push_back(descriptor);
		}
		//add scene to scenes
		sceneFile.close();
		return true;
	}

	
	void Scene::importAll() {
		// load json file
		File scenesImportFile;
		if (!scenesImportFile.open("scenes/import.scenes.json", FILE_OPEN_MODE_READ))
		{
			Log::out("Couldn't load scene!");
			return;
		}
		std::string importedScenesString = scenesImportFile.readText();
		scenesImportFile.close();
		//parse to json
		nlohmann::json importedScenes = nlohmann::json::parse(importedScenesString);
		//add instances
		for (int i = 0; i < importedScenes.size(); i++) {
			std::string sceneName = importedScenes[i]["name"];
			std::string sceneFilePath = importedScenes[i]["file"] ;
			ResourceManager<Scene>::getSingleton()
				->add(sceneName)
				->load("scenes/" + sceneFilePath);
		}
	}

	/*
	void Scene::changeSceneTo(const Scene* scene) {
		//destroy all instances
		Instance::destroyAll();
		//instance create
		for(const auto& instanceDescriptor: scene->instances) {
			GameObject* instance = Instance::create(instanceDescriptor.objectId);
			instance->position = instanceDescriptor.position;
		}
		Log::out("change scene");
	}	
	*/

} // ASEngine