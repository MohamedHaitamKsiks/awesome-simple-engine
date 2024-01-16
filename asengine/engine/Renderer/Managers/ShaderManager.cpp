#include "ShaderManager.h"
#include "spirv_glsl.hpp"

namespace ASEngine
{
    // this functions is defined here and cannot be used by other files
    // I did this so that spirv_glsl do not get included  
    void ShaderManagerLoadShaderInfo(const spirv_cross::CompilerGLSL &glsl, ShaderInfo &info)
    {
        spirv_cross::ShaderResources resources = glsl.get_shader_resources();

        for (auto& uniformBuffer: resources.uniform_buffers) 
        {
            ShaderUniformBufferInfo ubInfo{};
            ubInfo.Binding = glsl.get_decoration(uniformBuffer.id, spv::DecorationBinding);
            
            // get type
            const auto &uniformBufferType = glsl.get_type(uniformBuffer.type_id);
            ubInfo.Size = glsl.get_declared_struct_size(uniformBufferType);

            // get uniform buffer members
            const auto &memberTypes = uniformBufferType.member_types;
            for (uint32_t i = 0; i < memberTypes.size(); i++)
            {
                ShaderUniformBufferIdentifier ubIdentifier{};
                
                // process type
                const auto& memberType = glsl.get_type(memberTypes[i]);
                const auto& baseMemberType = memberType.basetype;
                
                // adapt base member type to ShaderIdentifierType
                switch(baseMemberType)
                {
                    case spirv_cross::SPIRType::Boolean:
                        ubIdentifier.Type = ShaderIdentifierType::BOOLEAN;
                        break;
                    case spirv_cross::SPIRType::Int:
                        ubIdentifier.Type = ShaderIdentifierType::INT;
                        break;
                    case spirv_cross::SPIRType::UInt:
                        ubIdentifier.Type = ShaderIdentifierType::UINT;
                        break;
                    case spirv_cross::SPIRType::Float:
                        ubIdentifier.Type = ShaderIdentifierType::FLOAT;
                        break;
                    default:
                        ubIdentifier.Type = ShaderIdentifierType::UNDEFINED;
                }

                // get vector and cols
                ubIdentifier.VectorSize = static_cast<size_t>(memberType.vecsize);
                ubIdentifier.Columns = static_cast<size_t>(memberType.columns);
                
                // get array dimentions
                for (auto dimention: memberType.array)
                {
                    ubIdentifier.ArrayDimentions.Push(dimention);
                }

                // add name and offset
                ubIdentifier.Name = UniqueString(glsl.get_member_name(uniformBufferType.self, i));
                ubIdentifier.Offset = glsl.type_struct_member_offset(uniformBufferType, i);

                // push identifier
                ubInfo.Identifiers[ubIdentifier.Name] = ubIdentifier;
            }


            info.UniformBuffers[UniqueString(uniformBuffer.name)] = ubInfo;
        }

    }

    ShaderID ShaderManager::Create(const SpirvBinary &spirv, ShaderType type)
    {
        // get spirv data
        ShaderInfo info{};
        info.Type = type;
        info.UniformBuffers = {};

        // create spirv_compiler
        spirv_cross::CompilerGLSL glsl(spirv);
        
        // load shader infos
        ShaderManagerLoadShaderInfo(glsl, info);


    // create opengl shader
    #ifdef OPENGL
        // compile glsl
        spirv_cross::CompilerGLSL::Options options;
        options.version = 310;
        options.es = true;
        glsl.set_common_options(options);

        std::string glSource = glsl.compile();
        
        //create opengl shader
        
        GLuint shader;
        switch(ShaderType)
        {
            ShaderType::VERTEX:
                shader = glCreateShader(GL_VERTEX_SHADER);
                break;
            ShaderType::FRAGMENT:
                shader = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            default:
                throw ShaderCreateFailException("Invalid shader type");
        }
        // compile shader
        glShaderSource(shader, 1, glSource.c_str(), NULL);
        glCompileShader(shader);

        // error
        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetShaderInfoLog(shader, 1024, &log_length, message);
            // Write the error to a log
            Debug::Error(message);
            throw ShaderCompileFailException();
        }

        info.GLShaderID = shader;
    #endif // OPENGL

        // add info and return ID
        return m_ShaderInfos.Push(info);
    }

    void ShaderManager::Delete(ShaderID shaderID)
    {
    // delete opengl shader
    #ifdef OPENGL
        glDeleteShader(GetShaderInfo(shaderID).GLShaderID);
    #endif
        // delete shader id
        m_ShaderInfos.Free(shaderID);
    }


} // namespace ASEngine
