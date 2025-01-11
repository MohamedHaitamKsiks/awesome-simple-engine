#ifndef __ASENGINE_LUA_SCRIPT_CLASS_H
#define __ASENGINE_LUA_SCRIPT_CLASS_H

#include "ECS/Entity.h"
#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"

namespace ASEngine
{
    class LuaScript: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(LuaScript);
    public:
        virtual ~LuaScript() {}

        // create lua script from source 
        void Create(const std::string& luaSource);

        // load from file
        bool Load(const std::string& path) override;
    private:
        UniqueString m_ClassName;
    };
} // namespace ASEngine


#endif // __ASENGINE_LUA_SCRIPT_CLASS_H
