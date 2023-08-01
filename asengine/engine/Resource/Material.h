

#ifndef ASENGINE_MATERIAL_H
#define ASENGINE_MATERIAL_H

#include <unordered_map>
#include <string>
#include <vector>
#include <cstring>

#include "engine/Renderer/Color.h"
#include "engine/Renderer/ShaderProgram.h"

#include "engine/Math/mat3.h"
#include "engine/Math/vec2.h"
#include "engine/Thirdparty/json.hpp"
#include "engine/Log/Log.h"

#include "ResourceManager.h"
#include "Resource.h"
#include "Shader.h"

namespace ASEngine {

    using MaterialID = ResourceID;

    class Material : public Resource
    {
    public:
        Material(){}
        ~Material();

        // create material based on file
        bool Load(const std::string& materialPath);
    
        // create material based on shade
        void Create(ShaderID shaderId);

        // bind material before drawing
        void Bind();

        // set shader param
        template<typename T>
        void SetShaderParam(const UniqueString& param, const T& value)
        {
            // get shader
            auto &shader = ResourceManager<Shader>::Get(m_ShaderID);
            // get shader info
            int paramIndex = shader.m_UniformNames[param];
            ShaderUniformInfo info = shader.m_Uniforms[paramIndex];

            // check if sizeof T is the same as param info
            if (info.Size != sizeof(T))
            {
                return;
            }

            // copy value to buffer
            CopyToUniformBuffer(&value, info.Offset, sizeof(T));
        }

        // get shader
        inline ShaderID GetShaderID() const
        {
            return m_ShaderID;
        };


    private:
        // copy buffer to material's uniform buffer
        void CopyToUniformBuffer(const void *buffer, size_t offset, size_t size);

        // shader
        ShaderID m_ShaderID = CHUNK_NULL;
        // buffer of all uniforms values
        uint8_t* m_UniformBuffer = nullptr;

    };

} //ASEngine

#endif //ASENGINE_MATERIAL_H
