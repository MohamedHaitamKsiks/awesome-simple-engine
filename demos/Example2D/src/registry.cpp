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
        ASENGINE_REGISTER_COMPONENT(Transform2D);
        ASENGINE_REGISTER_COMPONENT(Camera2D);
        ASENGINE_REGISTER_SYSTEM(Renderer2D);

        ASENGINE_REGISTER_RESOURCE_CLASS(Sprite);
        ASENGINE_REGISTER_RESOURCE_CLASS(Font);

        ASENGINE_REGISTER_COMPONENT(CameraController);
        ASENGINE_REGISTER_COMPONENT(BouncingFox);
        ASENGINE_REGISTER_COMPONENT(BouncingFoxSpawner);

        ASENGINE_REGISTER_SYSTEM(Example2D);
        ASENGINE_REGISTER_SYSTEM(CameraControllerSystem);
    }
} // ASEngine
