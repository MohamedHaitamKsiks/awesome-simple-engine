#include "LuaComponentClass.h"
#include "LuaComponent.h"

namespace ASEngine
{
    LuaComponentClass::~LuaComponentClass()
    {
    }

    AbstractComponent *LuaComponentClass::New()
    {
        return new LuaComponent();
    }

    IComponentCollection *LuaComponentClass::CreateComponentCollection()
    {
        return new ComponentCollection<LuaComponent>();
    }

} // namespace ASEngine
