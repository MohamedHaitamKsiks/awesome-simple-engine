#ifndef ASENGINE_SHADER_PROGRAM_MANAGER_H
#define ASENGINE_SHADER_PROGRAM_MANAGER_H

#include "Core/Math/vec2.h"
#include "Core/Math/vec3.h"
#include "Core/Math/mat3.h"
#include "Core/Math/mat4.h"
#include "Core/Error/Exception.h"
#include "Core/Error/Assert.h"
#include "Core/Memory/PoolAllocator.h"
#include "Core/Memory/DynamicArray.h"
#include "Core/String/UniqueString.h"

#include "Renderer/Color.h"
#include "Renderer/GraphicsAPI.h"
#include "Renderer/VertexInput.h"

#include "BufferManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include <unordered_map>

namespace ASEngine
{
    // shader progarm info
    struct ShaderProgramInfo
    {
    // opengl specific implementation
    #pragma region OPENGL_SPECIFICATION
        GLint GLProgramID = -1;
    #pragma endregion OPENGL_SPECIFICATION
        // shader params
        ShaderParams Params{};
        std::unordered_map<VertexInputRate, VertexInputLayout> VertexInputLayouts;
    };

    // shader program id
    using ShaderProgramID = ChunkID;
    
    /* Define some exceptions */
    DEFINE_EXCEPTION(ShaderProgramCreateFailException, "Couldn't create shader program");

    // api agnostic manager for shader program
    class ShaderProgramManager
    {
    public:
        ShaderProgramManager() {};
        ~ShaderProgramManager() {};

        /* create shader program from fragment and vertex shader, 
        throws ShaderProgramCreateFailException*/
        ShaderProgramID Create(ShaderID vertexShaderID, ShaderID fragmentShaderID, const std::unordered_map<VertexInputRate, VertexInputLayout>& vertexLayouts);

        // bind shader program
        void Bind(ShaderProgramID shaderProgramID);

        // get shader program info
        inline ShaderProgramInfo& GetShaderProgramInfo(ShaderProgramID shaderProgramID)
        {
            return m_ShaderProgramInfos.Get(shaderProgramID);
        }

        // bind uniform buffer
        void SetUniformBuffer(ShaderProgramID shaderProgramID, UniqueString uniformBufferName, const ByteBuffer& buffer);

        // bind texture to sampler
        void SetSampler(ShaderProgramID shaderProgramID, UniqueString samplerName, TextureID textureID);

        // destroy shader program
        void Destroy(ShaderProgramID shaderProgramID);

        // get current shader
        inline ShaderID CurrentShaderProgramID()
        {
            return m_CurrentShaderProgram;
        };

    private : 
        TPoolAllocator<ShaderProgramInfo> m_ShaderProgramInfos{2};
        // keep track of current chunk
        ShaderProgramID m_CurrentShaderProgram = CHUNK_NULL;
    
    };

} // namespace ASEngine

#endif // ASENGINE_SHADER_PROGRAM_MANAGER_H