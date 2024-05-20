#include "Shader.h"

#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "Resource/ResourceRefSerialization.h"

ASENGINE_SERIALIZE_RESOURCE_REF(Shader);

namespace ASEngine
{
    template<>
    void Serializer<Shader>::Deserialize(const Json& object, Shader& dest)
    {
        
    }

    template<>
    Json <Shader>::Serialize(const Shader& value)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Shader);
} // namespace ASEngine
