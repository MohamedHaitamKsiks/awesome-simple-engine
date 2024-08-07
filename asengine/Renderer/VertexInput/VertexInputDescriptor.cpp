#include "VertexInputDescriptor.h"

#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "Resource/ResourceRefSerialization.h"

ASENGINE_SERIALIZE_RESOURCE_REF(VertexInputDescriptor);

namespace ASEngine
{
    template<>
    void  Serializer::Deserialize(const Json& object, VertexInputDescriptor& dest)
    {
        std::vector<VertexInputLayout> layouts;
        Serializer::Deserialize(object.at("VertexInputLayouts"), layouts);

        dest.Create(layouts);
    }

    template<>
    Json  Serializer::Serialize(const VertexInputDescriptor& src)
    {
        return Serializer::Serialize(src.m_VertexInputLayouts);
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(VertexInputDescriptor);
    
    void VertexInputDescriptor::Create(const std::vector<VertexInputLayout> &layouts)
    {
        m_VertexInputLayouts = layouts;

        CreateImp(layouts);
    }
} // namespace ASEngine
