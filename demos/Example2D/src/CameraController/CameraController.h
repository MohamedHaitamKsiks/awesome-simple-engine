#ifndef __ASENGINE_CAMERA_CONTROLLER_H
#define __ASENGINE_CAMERA_CONTROLLER_H

#include "ASEngine.h"
using namespace ASEngine;

struct CameraController: public Component<CameraController>
{
    bool IsLeftPressed = false;
    bool IsRightPressed = false;
    bool IsDownPressed = false;
    bool IsUpPressed = false;

    void OnCreate(EntityID entityID) override;
    void OnDestroy() override;
};

#endif // __ASENGINE_CONTROLLER_H