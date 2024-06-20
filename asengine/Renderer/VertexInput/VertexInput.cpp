#include "VertexInput.h"

#include <vector>

#include "Core/Serialization/SerializeEnum.h"
#include "Core/Serialization/SerializeStruct.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Renderer/Color.h"

namespace ASEngine
{
    ASENGINE_SERIALIZE_ENUM(VertexAttributeType, 
        NONE,
        INT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4
    )

    ASENGINE_SERIALIZE_ENUM(VertexInputRate,
        NONE,
        VERTEX,
        INSTANCE
    )

    ASENGINE_SERIALIZE_STRUCT(VertexAttribute,
        Location,
        Type
    )

    // vertex input serialiazation
    template <>
    void Serializer::Deserialize(const Json& object, VertexInputLayout& dest)
    {
        ASENGINE_DESERIALIZE_STRUCT_FIELD(dest, Binding);
        ASENGINE_DESERIALIZE_STRUCT_FIELD(dest, InputRate);
        
        std::vector<VertexAttribute> vertexAttributes;
        Serializer::Deserialize(object.at("VertexAttributes"), vertexAttributes);

        size_t stride = 0;

        for (auto& attribute: vertexAttributes)
        {
            attribute.Offset = stride;
            dest.VertexAttributes.push_back(attribute);

            // add size of attribute to stride
            switch (attribute.Type)
            {
            case VertexAttributeType::INT:
                stride += sizeof(int);
                break;
            
            case VertexAttributeType::FLOAT:
                stride += sizeof(float);
                break;

            case VertexAttributeType::VEC2:
                stride += sizeof(Vector2);
                break;

            case VertexAttributeType::VEC3:
                stride += sizeof(Vector3);
                break;

            case VertexAttributeType::VEC4:
                stride += sizeof(Color);
                break;

            default:
                break;
            }
        }
        
        dest.Stride = stride;
        dest.VertexAttributes = vertexAttributes;
    }

    template <>
    Json Serializer::Serialize(const VertexInputLayout& value)
    {
        Json object = Json({});
        ASENGINE_SERIALIZE_STRUCT_FIELD(value, Binding);
        ASENGINE_SERIALIZE_STRUCT_FIELD(value, InputRate);
        ASENGINE_SERIALIZE_STRUCT_FIELD(value, VertexAttributes);
        return object;
    }
} // namespace ASEngine
