#include "Scriptable.h"
#include "LuaScript/LuaScript.h"

namespace ASEngine
{
    void Scriptable::OnCreate(EntityID ownerID)
    {
    }

    void Scriptable::OnDestroy()
    {
    }

    void Scriptable::AddScript(UniqueString script)
    {
        ResourceRef<LuaScript> luaScript = LuaScript::GetResourceClass().Load(script);
        luaScript->New(m_OwnerID);
    }

    // add serialization
    template<>
    void Serializer::Deserialize(const Json& object, Scriptable& dest)
    {
    }

    template<>
    Json Serializer::Serialize(const Scriptable& src)
    {
        return Json({});
    }

} // namespace ASEngine
