//
// Created by ksiks_wa3r on 3/27/23.
//

#include "NewObject.h"

void NewObject::onCreate() {

}

void NewObject::onUpdate(float delta) {

}

void NewObject::onDraw(Graphics& graphics) {
    graphics.drawSprite("spr_run", 0, position);
}

void NewObject::onInputEvent(InputEvent event) {

}
