#ifndef ASENGINE_SHADER_SOURCE_H
#define ASENGINE_SHADER_SOURCE_H

#include <string>

#include "Resource/Resource.h"
#include "ShaderParams.h"

namespace ASEngine
{
    // define spirvbinary as vector of uint32_t
    using SpirvBinary = std::vector<uint32_t>;

    // shader source resource (parsed from spirv binary)
    class ShaderSource: public Resource<ShaderSource>
    {
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
    private:
        ShaderParams m_Params{};
    };
} // namespace ASEngine

#endif // ASENGINE_SHADER_SOURCE_H