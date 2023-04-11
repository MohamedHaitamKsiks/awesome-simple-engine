//d+
// Created by ksiks_wa3r on 3/1/23.
//

#include "GameObject.h"
#include "Instance.h"

namespace ASEngine {

	bool GameObject::collideWithInstance(GameObject *object, vec2 offset) {
		CollisionMask offsetMask = mask;
		offsetMask.position = offsetMask.position + offset;
		return offsetMask.collideWithMask(object->mask);
	}

	GameObject* GameObject::collideWithObject(GameObjectID gameObjectId, vec2 offset) {
		for (auto instance: Instance::instances) {
			//exclude self
			if (instance == this)
				continue;
			if (instance->objectId == gameObjectId && collideWithInstance(instance, offset))
				return instance;
		}
		return nullptr;
	}

	GameObject* GameObject::collideWithSolid(vec2 offset) {
		for (auto instance: Instance::instances) {
			//exclude self
			if (instance == this)
				continue;
			if (collideWithInstance(instance, offset) && instance->solid)
				return instance;
		}
		return nullptr;
	}

	GameObject* GameObject::collideWithAll(vec2 offset) {
		for (auto instance: Instance::instances) {
			//exclude self
			if (instance == this)
				continue;
			if (collideWithInstance(instance, offset))
				return instance;
		}
		return nullptr;
	}
} // ASEngine