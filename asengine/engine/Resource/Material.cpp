#include "Material.h"

namespace ASEngine
{
    Material::~Material()
    {
        if (!IsOwner())
            return;
            
        if (m_UniformBuffer)
        {
            delete[] m_UniformBuffer;
            m_UniformBuffer = nullptr;
        }
    }

    bool Material::Load(const std::string &materialPath)
    {
        return true;
    }

    void Material::Create(ResourceID shaderID)
    {
        // get shader
        m_ShaderID = shaderID;
        auto &shader = ResourceManager<Shader>::Get(m_ShaderID);

        // allocate uniform buffer
        m_UniformBuffer = new uint8_t[shader.m_UniformBufferSize];
    }

    void Material::CopyToUniformBuffer(const void *buffer, size_t offset, size_t size)
    {
        memcpy(m_UniformBuffer + offset, buffer, size);
    }

    void Material::Bind()
    {
        auto& shader = ResourceManager<Shader>::Get(m_ShaderID);

        for (auto info : shader.m_Uniforms)
        {
            // get value adress
            uint8_t *value = m_UniformBuffer + info.Offset;

            // sampler counter
            SamplerSlot currentSlot = 0;

            switch (info.Type)
            {
            case ShaderUniformType::INT:
                info.Location.SetInt((int *)value);
                break;
            case ShaderUniformType::FLOAT:
                info.Location.SetFloat((float *)value);
                break;
            case ShaderUniformType::VEC2:
                info.Location.SetVec2((float *)value);
                break;
            case ShaderUniformType::VEC3:
                info.Location.SetVec3((float *)value);
                break;
            case ShaderUniformType::VEC4:
                info.Location.SetVec4((float *)value);
                break;
            case ShaderUniformType::MAT3:
                info.Location.SetMat3((float *)value);
                break;
            case ShaderUniformType::SAMPLER_2D:
                Texture texture = *((Texture *)value);
                texture.BindSampler(currentSlot);
                info.Location.SetInt(&currentSlot);
                currentSlot++;
                break;
            }
        }
    }

    // material
    template <>
    Json Serializer<Material>::Serialize(const Material &value)
    {
        Json materialObject = Json({});
        return materialObject;
    }
    template <>
    void Serializer<Material>::Deserialize(const Json &object, Material &dest)
    {
        assert(object.is_object());
    }

} // ASEngine