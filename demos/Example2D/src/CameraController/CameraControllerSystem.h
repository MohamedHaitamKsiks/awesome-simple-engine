#ifndef __ASENGINE_CAMERA_CONTROLLER_SYSTEM_H
#define __ASENGINE_CAMERA_CONTROLLER_SYSTEM_H

#include "ASEngine.h"
using namespace ASEngine;

class CameraControllerSystem: public ISystem
{
public:
    CameraControllerSystem() {}
    ~CameraControllerSystem() {}
private:
    void Update(float delta) override;
    void OnInputEvent(const InputEvent& event) override;
};

#endif // __ASENGINE_CAMERA_CONTROLLER_SYSTEM_H