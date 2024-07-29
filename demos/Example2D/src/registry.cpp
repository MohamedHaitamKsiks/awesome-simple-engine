#include "ASEngine.h"

#include "BouncingFox/BouncingFox.h"
#include "BouncingFox/BouncingFoxSpawner.h"

#include "CameraController/CameraController.h"
#include "CameraController/CameraControllerSystem.h"

#include "Example2D.h"

// module registry for the game
namespace ASEngine
{
    void Registry()
    {
        Module2D::Init();

        ASENGINE_REGISTER_COMPONENT(CameraController);
        ASENGINE_REGISTER_COMPONENT(BouncingFox);
        ASENGINE_REGISTER_COMPONENT(BouncingFoxSpawner);

        ASENGINE_REGISTER_SYSTEM(Example2D);
        ASENGINE_REGISTER_SYSTEM(CameraControllerSystem);
    }
} // ASEngine
