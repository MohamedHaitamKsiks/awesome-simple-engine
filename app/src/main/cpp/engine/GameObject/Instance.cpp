//
// Created by ksiks_wa3r on 3/24/23.
//

#include "Instance.h"

namespace ASEngine {

	std::vector<GameObject*> Instance::instances = {};

	std::vector<GameObject*> Instance::destroyQueue = {};

	GameObject *Instance::create(GameObjectID name) {
		GameObject* instance = gameObjects[name]();
		instance->objectId = name;
		instance->onCreate();
		return instance;
	}

	void Instance::destroy(GameObject *instance) {
		//find instance index
		destroyQueue.push_back(instance);

	}

	void Instance::destroyAll() {
		for (auto instance: instances) {
			destroy(instance);
		}
	}

	void Instance::update(float delta) {
		for (auto instance: instances) {
			instance->mask.position = instance->position;
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
		for (auto instance: destroyQueue) {
			std::remove(instances.begin(), instances.end(), instance);
			//delete instance;
		}
		destroyQueue.clear();

	}

	//link game object name to object
	std::unordered_map<std::string, GameObject* (*) ()> Instance::gameObjects = {};




} // ASEngine