#ifndef __ASENGINE_CAMERA_2D_H
#define __ASENGINE_CAMERA_2D_H

#include <unordered_set>

#include "ECS/Component.h"
#include "Renderer/Viewport/Viewport.h"

#include "API/API.h"

namespace ASEngine
{
    struct ASENGINE_API Camera2D: public Component<Camera2D>
    {
        ResourceRef<Viewport> Target = ResourceRef<Viewport>::NONE();
        std::unordered_set<UniqueString> Layers = {};

        void OnCreate(EntityID entityID);
        void OnDestroy();
    };
} // namespace ASEngine

#endif // __ASENGINE_CAMERA_2D_H
