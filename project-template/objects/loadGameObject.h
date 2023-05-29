//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ASENGINE_LOADGAMEOBJECT_H
#define ASENGINE_LOADGAMEOBJECT_H

#include "NewObject/NewObject.h"
#include "../engine/asengine.h"
#include <string>


//add every game object here
static void loadGameObjects() {
	ASEngine::Instance::addGameObject<NewObject>("NewObject");
}

#endif //ASENGINE_LOADGAMEOBJECT_H
