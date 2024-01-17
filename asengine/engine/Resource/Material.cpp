#include "Material.h"

namespace ASEngine
{
    Material::~Material()
    {
        
    }


    void Material::Create(ResourceID shaderID)
    {
        // get shader
        m_ShaderID = shaderID;
        auto &shader = ResourceManager<Shader>::Get(m_ShaderID);

        // get shader program info
        ShaderProgramManager* shaderProgramManager = Renderer::GetShaderProgramManager();
        auto& shaderProgramInfo = shaderProgramManager->GetShaderProgramInfo(shader.m_ShaderProgramID);

        // init uniform buffers
        for (auto& [uniformBufferName, uniformBufferInfo]: shaderProgramInfo.Params.UniformBuffers)
        {
            ByteBuffer buffer(uniformBufferInfo.Size);
            SetUniformBuffer(buffer);
        }

        // init samplers
        for (auto& [samplerName, samplerInfo]: shaderProgramInfo.Params.Samplers)
        {
            SetSampler(samplerName, 0);
        }
    }

    void Material::Bind()
    {
        auto& shader = ResourceManager<Shader>::Get(m_ShaderID);
        ShaderProgramID shaderProgramID = shader.m_ShaderProgramID;

        // bind params
        ShaderProgramManager *shaderProgramManager = Renderer::GetShaderProgramManager();
        
        // 1. bind uniform buffers
        for (auto& [uniformBufferName, uniformBuffer]: m_UniformBuffers)
        {
            shaderProgramManager->SetUniformBuffer(shaderProgramID, uniformBufferName, uniformBuffer);
        }

        // 2. bind samplers
        for (auto& [samplerName, textureID]: m_Samplers)
        {
            shaderProgramManager->SetSampler(shaderProgramManager, samplerName, textureID);
        }
    }

    void Material::SetUniformBuffer(UniqueString uniformBufferName, const ByteBuffer &buffer)
    {
        m_UniformBuffers[uniformBufferName] = buffer;
    }

    void Material::SetSampler(UniqueString samplerName, TextureID textureID)
    {
        m_Samplers[samplerName] = textureID;
    }

    // material
    template <>
    Json Serializer<Material>::Serialize(const Material &value)
    {
        /*Json materialObject = Json({});
        return materialObject;*/
    }
    template <>
    void Serializer<Material>::Deserialize(const Json &object, Material &dest)
    {
        /*assert(object.is_object());
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
        }*/
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