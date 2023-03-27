//
// Created by ksiks_wa3r on 3/24/23.
//

#include "Instance.h"

namespace ASEngine {

	std::vector<GameObject*> Instance::instances = {};

	std::vector<int> Instance::destroyQueue = {};

	GameObject *Instance::create(GameObjectID name) {
		GameObject* instance = gameObjects[name]();
		instance->objectId = name;
		instance->onCreate();
		return instance;
	}

	void Instance::destroy(GameObject *instance) {
		//find instance index
		int index = 0;
		for (int i = 0; i < instances.size(); i++) {
			if (instance == instances[i]) {
				index = i;
				break;
			}
		}
		//queue index for delete
		destroyQueue.push_back(index);
	}

	void Instance::destroyAll() {
		for (auto instance: instances) {
			destroy(instance);
		}
	}

	void Instance::update(float delta) {
		for (auto instance: instances) {
			instance->onUpdate(delta);
		}
		cleanDestroyQueue();
	}

	void Instance::draw() {
		for (auto instance: instances) {
			instance->onDraw();
		}
	}


	void Instance::cleanDestroyQueue() {
		//free all
		for (auto instanceIndex: destroyQueue) {
			GameObject* instance = instances[instanceIndex];
			std::remove(instances.begin(), instances.end(), instance);
			delete instance;
		}


	}

	//link game object name to object
	std::unordered_map<std::string, GameObject* (*) ()> Instance::gameObjects = {};




} // ASEngine