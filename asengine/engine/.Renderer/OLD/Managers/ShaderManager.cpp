#include "ShaderManager.h"
#include "spirv_glsl.hpp"

namespace ASEngine
{
    void ShaderParams::Add(const ShaderParams &params)
    {
        this->Samplers.insert(params.Samplers.begin(), params.Samplers.end());
        this->UniformBuffers.insert(params.UniformBuffers.begin(), params.UniformBuffers.end());
    }

    // this functions is defined here and cannot be used by other files
    // I did this so that spirv_glsl do not get included  
    void ShaderManagerLoadShaderParams(const spirv_cross::CompilerGLSL &glsl, ShaderParams &params)
    {
        spirv_cross::ShaderResources resources = glsl.get_shader_resources();

        // get uniform buffers
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


            params.UniformBuffers[UniqueString(uniformBuffer.name)] = ubInfo;
        }

        // get samplers
        for (auto& sampler: resources.sampled_images)
        {
            ShaderSamplerInfo samplerInfo{};
            samplerInfo.Name = UniqueString(sampler.name);
            samplerInfo.Binding = glsl.get_decoration(sampler.id, spv::DecorationBinding);

            params.Samplers[samplerInfo.Name] = samplerInfo;
        }
    }

    ShaderID ShaderManager::Create(const SpirvBinary &spirv, ShaderStage type)
    {
        // get spirv data
        ShaderInfo info{};
        info.Type = type;
        info.Params = ShaderParams{};

        // create spirv_compiler
        spirv_cross::CompilerGLSL glsl(spirv);
        
        // load shader params
        ShaderManagerLoadShaderParams(glsl, info.Params);


    // create opengl shader
    #pragma region OPENGL_SPECIFICATION
        // compile glsl
        spirv_cross::CompilerGLSL::Options options;
        options.version = 310;
        options.es = true;
        glsl.set_common_options(options);

        std::string glSource = glsl.compile();
        const GLchar* glSourceCString = glSource.c_str();
        
        //create opengl shader
        
        GLuint shader;
        switch(type)
        {
            case ShaderStage::VERTEX:
                shader = glCreateShader(GL_VERTEX_SHADER);
                break;
            case ShaderStage::FRAGMENT:
                shader = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            default:
                throw ShaderCreateFailException("Invalid shader type");
        }
        // compile shader
        glShaderSource(shader, 1, &glSourceCString, NULL);
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
            throw ShaderCreateFailException();
        }

        info.GLShaderID = shader;
    #pragma endregion OPENGL_SPECIFICATION // OPENGL

        // add info and return ID
        return m_ShaderInfos.Push(info);
    }

    void ShaderManager::Delete(ShaderID shaderID)
    {
    // delete opengl shader
    #pragma region OPENGL_SPECIFICATION
        glDeleteShader(GetShaderInfo(shaderID).GLShaderID);
    #pragma endregion OPENGL_SPECIFICATION
        // delete shader id
        m_ShaderInfos.Free(shaderID);
    }


} // namespace ASEngine
