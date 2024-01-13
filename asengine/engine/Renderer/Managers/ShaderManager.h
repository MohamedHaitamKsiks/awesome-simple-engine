#ifndef ASENGINE_SHADER_MANAGER_H
#define ASENGINE_SHADER_MANAGER_H

#include "Core/Error/Exception.h"

#include "Core/Memory/PoolAllocator.h"
#include "Renderer/GraphicsAPI.h"

namespace ASEngine
{
    // shader type
    enum class ShaderType
    {
        NONE = 0,
        VERTEX = (1u << 0),
        FRAGMENT = (1u << 1)
    };

    // shader info
    struct ShaderInfo
    {
        // opengl specifenuication
        #ifdef OPENGL
            GLint GLShaderID = -1;
        #endif // OPENGL

        ShaderType Type = ShaderType::NONE;
    };

    // shader creation fail exception
    DEFINE_EXCEPTION(ShaderCreateFailException, "Couldn't create shader!");
    
    // shader id
    using ShaderID = ChunkID;

    // abstract manager for shaders
    class ShaderManager
    {
    public:
        ShaderManager() {};
        ~ShaderManager() {};

        // create shader from code throws ShaderCreateFailException if error
        ShaderID Create(const std::string& shaderCode, ShaderType type);

        // get shader info
        inline ShaderInfo& GetShaderInfo(ShaderID shaderID)
        {
            return m_ShaderInfos.Get(shaderID);
        };

        // delete shader
        void Delete(ShaderID shaderID);

    private:
        TPoolAllocator<ShaderInfo> m_ShaderInfos{2};
    };

} // namespace ASEngine

#endif // ASENGINE_SHADER_PROGRAM_MANAGER_H