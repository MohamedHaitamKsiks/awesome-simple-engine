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


    void Material::Create(ResourceID shaderID)
    {
        // get shader
        m_ShaderID = shaderID;
        auto &shader = ResourceManager<Shader>::Get(m_ShaderID);

        // allocate uniform buffer
        m_UniformBuffer = new uint8_t[shader.m_UniformBufferSize];
    }

    const ShaderUniformInfo& Material::GetShaderParamInfo(UniqueString param) const
    {
        auto &shader = ResourceManager<Shader>::Get(m_ShaderID);
        int paramID = shader.m_UniformNames[param];
        return shader.m_Uniforms[paramID];
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
            case ShaderUniformType::MAT4:
                info.Location.SetMat4((float *)value);
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
        // get shader
        std::string shaderPath = object["ShaderName"];
        ResourceID shaderID = ResourceManager<Shader>::GetResourceID(UniqueString(shaderPath));

        // create material
        dest.Create(shaderID);

        auto paramList = object["Params"];
        for (auto& item: paramList.items())
        {
            auto& paramName = item.key();
            auto& paramValue = item.value();

            UniqueString param = UniqueString(std::string(paramName));
            const auto& info = dest.GetShaderParamInfo(param);

            switch (info.Type)
            {
            case ShaderUniformType::INT:
                dest.DeserializeAndSet<int>(param, paramValue);
                break;
            case ShaderUniformType::FLOAT:
                dest.DeserializeAndSet<float>(param, paramValue);
                break;
            case ShaderUniformType::VEC2:
                dest.DeserializeAndSet<vec2>(param, paramValue);
                break;
            case ShaderUniformType::VEC3:
                break;
            case ShaderUniformType::VEC4:
                dest.DeserializeAndSet<Color>(param, paramValue);
                break;
            case ShaderUniformType::MAT3:
                break;
            case ShaderUniformType::SAMPLER_2D:
                // load texture and add it to material
                std::string imagePath;
                Serializer<std::string>::Deserialize(paramValue, imagePath);

                Image image{};
                image.Load(imagePath);

                Texture texture = Texture::LoadFromImage(image);

                // set texture
                dest.SetShaderParam(param, texture);
                break;
            }
        }
    }

    bool Material::Load(const std::string &path)
    {
        File materialFile;
        if (!materialFile.Open(path, FileOpenMode::READ)) return false;
        std::string materialContent = materialFile.ReadText();
        materialFile.Close();

        Json materialObject = Json::parse(materialContent);
        Serializer<Material>::Deserialize(materialObject, *this);

        return true;
    }

} // ASEngine