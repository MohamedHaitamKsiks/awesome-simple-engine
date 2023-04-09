//
// Created by ksiks_wa3r on 3/24/23.
//

#ifndef MY_APPLICATION_INSTANCE_H
#define MY_APPLICATION_INSTANCE_H

#include <string>
#include <vector>
#include <unordered_map>

#include "GameObject.h"
#include "../InputEvent/InputEvent.h"
#include "../log.h"

namespace ASEngine {

    class Instance {
    public:
        //craete and return pointer to new instance
        static GameObject* create(GameObjectID name);
        //destroy instance
        static void destroy(GameObject* instance);
        //destroy all
        static void destroyAll();

        //instance update
        static void update(float delta);
		//instance draw
		static void draw();
        //create object instance from typename
        template<class T> static GameObject* createTemplate() {
			GameObject* instance = new T;
			instances.push_back(instance);
			return instance;
		};
        //add game object
        template<class T> static void addGameObject(std::string name) {
			gameObjects[name] = &createTemplate<T>;
		};
		//instances
		static std::vector<GameObject*> instances;

    private:
        //game objects
        static std::unordered_map<std::string, GameObject* (*)()> gameObjects;

        //queue to clean at the end of the frame
        static std::vector<int> destroyQueue;
        //clean destroy queue
        static void cleanDestroyQueue();

    };

} // ASEngine

#endif //MY_APPLICATION_INSTANCE_H
