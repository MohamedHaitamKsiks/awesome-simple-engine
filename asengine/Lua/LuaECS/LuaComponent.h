#ifndef __ASENGINE_LUA_COMPONENT_H
#define __ASENGINE_LUA_COMPONENT_H

#include "Lua/LuaTypes/LuaTypes.h"
#include "ECS/Component.h"

namespace ASEngine
{
    class LuaComponent: public AbstractComponent
    {
    public: 
        ~LuaComponent();

        /*void OnCreate(EntityID entityID) override;

        void OnDestroy() override;

        void Copy() override;

        void Deserialize(const Json& object) override;

        Json Serialize() override;*/
    private:
        LuaInteger m_ComponentReferenceID = -1;
    };
} // namespace ASEngine


#endif // __ASENGINE_LUA_COMPONENT_H