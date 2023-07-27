#include "Material.h"

namespace ASEngine
{
    Material::~Material()
    {
        if (m_UniformBuffer)
            delete[] m_UniformBuffer;
    }

    bool Material::Load(const std::string &materialPath)
    {
        return true;
    }

    void Material::Create(ShaderID shaderId)
    {
        // get shader
        m_ShaderID = shaderId;
        m_Shader = ResourceManager<Shader>::Get(shaderId);

        // allocate uniform buffer
        m_UniformBuffer = new uint8_t[m_Shader->m_UniformBufferSize];
    }

    void Material::CopyToUniformBuffer(const void *buffer, size_t offset, size_t size)
    {
        memcpy(m_UniformBuffer + offset, buffer, size);
    }

    void Material::Bind()
    {
        for (auto info : m_Shader->m_Uniforms)
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

} // ASEngine