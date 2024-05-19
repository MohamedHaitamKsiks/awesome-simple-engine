#ifndef ASENGINE_SHADER_H
#define ASENGINE_SHADER_H

#include "Resource/Resource.h"

namespace ASEngine
{
    // define spirvbinary as vector of uint32_t
    using SpirvBinary = std::vector<uint32_t>;

    // shader stage
    enum class ShaderStage
    {
        NONE = 0,
        VERTEX,
        FRAGMENT
    };

    

    // abstract shader class
    // 
    class Shader: public Resource<Shader>
    {
    public:
        virtual ~Shader() {};

        // create shader from spirv binary
        void Create(const SpirvBinary& spirv, ShaderStage stage);
        
        // 
    private:
        ShaderStage m_Stage = ShaderStage::NONE;
        // std::unordered_map<UniqueString, ShaderUniformBufferInfo> m_UniformBuffers = {};
        // std::unordered_map<UniqueString, ShaderSamplerInfo> m_Samplers = {};
    };
} // namespace ASEngine

#endif // ASENGINE_SHADER_H