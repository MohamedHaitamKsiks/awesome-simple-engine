#include "LuaComponent.h"

namespace ASEngine
{
    LuaComponent::~LuaComponent()
    {
    }

    void LuaComponent::OnCreate(EntityID entityID)
    {
    }

    void LuaComponent::OnDestroy()
    {
    }

    void LuaComponent::Copy()
    {
    }

    void LuaComponent::Deserialize(const Json &object)
    {
    }

    Json LuaComponent::Serialize()
    {
        return Json({});
    }

} // namespace ASEngine
