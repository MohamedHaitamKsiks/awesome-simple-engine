//
// Created by ksiks_wa3r on 3/1/23.
//

#ifndef MY_APPLICATION_GAMEOBJECT_H
#define MY_APPLICATION_GAMEOBJECT_H

#include "../Math/vec2.h"

#include <string>

namespace ASEngine {

    typedef std::string GameObjectID;

    class GameObject {
    public :
        //game object id
        GameObjectID objectId;

        //game object attributes
        vec2 position = vec2::zero();
        vec2 scale = vec2::one();
        float rotation = 0.0f;
        float z_index = 0.0f;
        bool visible = true;

        //functions for the different events for a game object (similar to gamemaker's events)
        virtual void onCreate();
        virtual void onUpdate(float delta);
        virtual void onDraw();
        virtual void onInputEvent();

    };

} // ASEngine

#endif //MY_APPLICATION_GAMEOBJECT_H
