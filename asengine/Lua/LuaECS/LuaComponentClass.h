#ifndef __ASENGINE_LUA_COMPONENT_CLASS
#define __ASENGINE_LUA_COMPONENT_CLASS

#include "Lua/LuaTypes/LuaTypes.h"
#include "ECS/ComponentClass.h"

namespace ASEngine
{
    class LuaComponentClass: public IComponentClass
    {
    public:
        ~LuaComponentClass();

        AbstractComponent* New() override;

        IComponentCollection* CreateComponentCollection() override;

    private:
        UniqueString m_Name{};
        

    };
} // namespace ASEngine


#endif // __ASENGINE_LUA_COMPONENT_CLASS