//
// Created by ksiks_wa3r on 3/24/23.
//

#ifndef MY_APPLICATION_INSTANCE_H
#define MY_APPLICATION_INSTANCE_H

#include <string>
#include <vector>

#include "GameObject.h"

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

    private:
        //instances
        static std::vector<GameObject*> instances;
        //queue to clean at the end of the frame
        static std::vector<int> destroyQueue;
        //clean destroy queue
        static void cleanDestroyQueue();
    };

} // ASEngine

#endif //MY_APPLICATION_INSTANCE_H
