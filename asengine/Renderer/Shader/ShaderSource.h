#ifndef __ASENGINE_SHADER_SOURCE_H
#define __ASENGINE_SHADER_SOURCE_H

#include <string>
#include "ShaderParams.h"

#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"

namespace ASEngine
{
    // define spirvbinary as vector of uint32_t
    using SpirvBinary = std::vector<uint32_t>;

    // shader source resource (parsed from spirv binary)
    class ShaderSource: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(ShaderSource);
    public:
        ~ShaderSource() {};

        // create shader from spirv binary
        void Create(const SpirvBinary& spirv);

        // load shader (use path to shader it is converted to spirv automatically)
        bool Load(const std::string& path) override;
        
        // get shader params
        inline const ShaderParams& GetShaderParams() const
        {
            return m_Params;
        }

        // get spirv 
        inline const SpirvBinary& GetSpirv() const
        {
            return m_Spirv;
        }
    private:
        ShaderParams m_Params{};
        SpirvBinary m_Spirv{};
    };
} // namespace ASEngine

#endif // __ASENGINE_SHADER_SOURCE_H