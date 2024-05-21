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
        // load vertex source
        ResourceRef<ShaderSource> vertexSource;
        Serializer<ResourceRef<ShaderSource>>::Deserialize(object.at("Vertex"), vertexSource);
        
        // load fragment source
        ResourceRef<ShaderSource> fragmentSource;
        Serializer<ResourceRef<ShaderSource>>::Deserialize(object.at("Fragment"), fragmentSource);
    
        // create shader
        
    }

    template<>
    Json <Shader>::Serialize(const Shader& value)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Shader);

    void Shader::Create(ResourceRef<ShaderSource> vertexSource, ResourceRef<ShaderSource> fragmentSource)
    {

    }
} // namespace ASEngine
