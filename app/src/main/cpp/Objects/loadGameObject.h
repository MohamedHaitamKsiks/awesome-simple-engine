//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_LOADGAMEOBJECT_H
#define ANDROIDSIMPLEENGINE_LOADGAMEOBJECT_H

#include "MyObject/MyObject.h"
#include "../engine/asengine.h"
#include <string>


//add every game object here
static void loadGameObjects() {
	ASEngine::Instance::addGameObject<MyObject>("MyObject");
}

#endif //ANDROIDSIMPLEENGINE_LOADGAMEOBJECT_H
