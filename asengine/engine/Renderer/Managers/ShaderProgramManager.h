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

#include "ShaderManager.h"

namespace ASEngine
{
    // uniform 
    using UniformName = UniqueString;

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
        MAT4,
        SAMPLER_2D
    };

    // shader params info
    struct ShaderParamInfo
    {
    // opengl specification
    #ifdef OPENGL
        GLint GLUniformLocation = -1;
    #endif // OPENGL
        // uniform name
        UniformName Name = UNIQUE_STRING_NULL;
        // unifrom type
        ShaderUniformType Type = ShaderUniformType::UNDEFINED;
        // uniform size
        size_t Size = 0;
        // uniform index
        int Index = 0;
        // uniform offset
        int Offset = 0;
    };

    // shader progarm info
    struct ShaderProgramInfo
    {
    // opengl specific implementation
    #ifdef OPENGL
        GLint GLProgramID = -1;
    #endif
        std::unordered_map<UniformName, ShaderUniformInfo> UniformInfos; 
        ShaderType Type = ShaderType::NONE;

    private: 
        void FetchUniforms();
        friend class ShaderProgramManager;
    };

    // shader program id
    using ShaderProgramID = ChunkID;
    
    /* Define some exceptions */
    DEFINE_EXCEPTION(ShaderProgramCreateFailException, "Couldn't create shader program");

    // api agnostic manager for shader program
    class ShaderProgramManager
    {
    public:
        ShaderProgramManager(ShaderManager* shaderManager);
        ~ShaderProgramManager() {};

        /* create shader program from fragment and vertex shader, 
        throws ShaderProgramCreateFailException*/
        ShaderProgramID Create(ShaderID vertexShaderID, ShaderID fragmentShaderID);

        // bind shader program
        void Bind(ShaderProgramID shaderProgramID);

        // get shader program info
        inline ShaderProgramInfo& GetShaderProgramInfo(ShaderProgramID shaderProgramID)
        {
            return m_ShaderProgramInfos.Get(shaderProgramID);
        }

        inline ShaderUniformInfo GetUniformInfo(ShaderProgramID shaderProgramID, UniqueString uniformName)
        {
            return GetShaderProgramInfo(shaderProgramID).UniformInfos[uniformName];
        }

        // destroy shader program
        void Destroy(ShaderProgramID shaderProgramID);

    private : 
        TPoolAllocator<ShaderProgramInfo> m_ShaderProgramInfos{2};
        // keep track of current chunk
        ShaderProgramID m_CurrentShaderProgram = CHUNK_NULL;
        // shader manager dependencie
        ShaderManager* m_ShaderManager;    
    };

} // namespace ASEngine

#endif // ASENGINE_SHADER_PROGRAM_MANAGER_H