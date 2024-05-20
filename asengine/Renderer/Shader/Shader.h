#ifndef ASENGINE_SHADER_H
#define ASENGINE_SHADER_H

#include "ShaderSource.h"

#include "Resource/ResourceRef.h"
#include "Resource/Resource.h"

namespace ASEngine
{
    // abstarct class represention of a shader
    // shader is created with a vertex shader code and a fragment shader code
    class Shader: public Resource<Shader>
    {
    ASENGINE_SERIALIZE_RESOURCE(Shader);

    public:
        virtual ~Shader() {};

        void Create();

    private:
        ResourceRef<ShaderSource> m_VertexSource;
        ResourceRef<ShaderSource> m_FragmentSource;

    };
} // namespace ASEngien


#endif // ASENGINE_SHADER_H