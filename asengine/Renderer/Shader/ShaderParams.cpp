#include "ShaderParams.h"

namespace ASEngine
{
    ShaderParams ShaderParams::Combine(const ShaderParams &a, const ShaderParams &b)
    {
        ShaderParams params{};

        params.Samplers.insert(a.Samplers.begin(), a.Samplers.end());
        params.Samplers.insert(b.Samplers.begin(), b.Samplers.end());

        params.UniformBuffers.insert(a.UniformBuffers.begin(), a.UniformBuffers.end());
        params.UniformBuffers.insert(b.UniformBuffers.begin(), b.UniformBuffers.end());
    
        return params;
    }

} // namespace ASEngine
