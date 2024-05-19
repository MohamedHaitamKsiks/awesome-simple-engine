#include "Shader.h"

#include "Resource/ResourceRefSerialization.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

namespace ASEngine
{
    ASENGINE_SERIALIZE_RESOURCE_REF(Shader);

    template <>
    void Serializer<Shader>::Deserialize(const Json &object, Shader &dest)
    {
    }

    template <>
    Json Serializer<Shader>::Serialize(const Shader &value)
    {
        return Json({});
    }

    
} // namespace ASEngine
