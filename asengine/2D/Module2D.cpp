#include "Module2D.h"
#include "2D/Camera2D/Camera2D.h"
#include "2D/Renderer2D/Renderer2D.h"
#include "2D/Transform2D/Transform2D.h"
#include "ECS/ComponentManager.h"
#include "ECS/SystemManager.h"
#include "Resource/ResourceManager.h"

namespace ASEngine
{
    void Module2D::Init()
    {
        ASENGINE_REGISTER_COMPONENT(Transform2D);
        ASENGINE_REGISTER_COMPONENT(Camera2D);

        ASENGINE_REGISTER_SYSTEM(Renderer2D);

        ASENGINE_REGISTER_RESOURCE_CLASS(Sprite);
        ASENGINE_REGISTER_RESOURCE_CLASS(Font);
    }
} // namespace ASEngine
