#include "VertexInputDescriptor.h"

#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "Resource/ResourceRefSerialization.h"

ASENGINE_SERIALIZE_RESOURCE_REF(VertexInputDescriptor);

namespace ASEngine
{
    template<>
    void Serializer::Deserialize(const Json& object, VertexInputDescriptor& dest)
    {
        Serializer::Deserialize(object.at("VertexInputLayouts"), dest.m_VertexInputLayouts);
    }

    template<>
    Json Serializer::Serialize(const VertexInputDescriptor& src)
    {
        return Serializer::Serialize(src.m_VertexInputLayouts);
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(VertexInputDescriptor);
} // namespace ASEngine
