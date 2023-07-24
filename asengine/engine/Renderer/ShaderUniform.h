#ifndef ASEGINE_SHADER_UNIFORM_H
#define ASEGINE_SHADER_UNIFORM_H

#include "engine/String/UniqueString.h"

#include "GraphicsAPI.h"
#include "Texture.h"
#include "Color.h"

#define SHADER_UNIFORM_NAME_LENGTH 15

namespace ASEngine
{
    // shader unifrom location
    class ShaderUniform
    {
    public:
        // shader param type
        ShaderUniform() {};
        ShaderUniform(int uniformLocation) { m_UniformLocation = uniformLocation; };

        void SetInt(const int* value);
        void SetFloat(const float* value);

        void SetVec2(const float* value);
        void SetVec3(const float* value);
        void SetVec4(const float* value);
        
        void SetMat3(const float* value);

    private:
        int m_UniformLocation = -1;
    };

    // shadaer uniform variable type
    enum class ShaderUniformType
    {
        UNDEFINED,
        INT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4,
        MAT3,
        SAMPLER_2D
    };

    // shader uniform informations
    struct ShaderUniformInfo
    {
        // uniform location
        ShaderUniform Location;
        // uniform name
        UniqueString Name;
        // unifrom type
        ShaderUniformType Type = ShaderUniformType::UNDEFINED;
        // uniform size
        size_t Size = 0;
        // uniform index
        int Index;
        // uniform offset
        int Offset;

        // constructor
        ShaderUniformInfo(ShaderUniform location)
        {
            Location = location;
        };
    };
} // namespace ASEngine

#endif // ASEGINE_SHADER_UNIFORM_H