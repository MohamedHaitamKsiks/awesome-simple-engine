#include "VertexInputDescriptor.h"

#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "Resource/ResourceRefSerialization.h"

ASENGINE_SERIALIZE_RESOURCE_REF(VertexInputDescriptor);

namespace ASEngine
{
    template<>
    void Serializer<VertexInputDescriptor>::Deserialize(const Json& object, VertexInputDescriptor& dest)
    {
        // 
    }

    template<>
    Json Serializer<VertexInputDescriptor>::Serialize(const VertexInputDescriptor& src)
    {
        return Json{};
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(VertexInputDescriptor);
} // namespace ASEngine
