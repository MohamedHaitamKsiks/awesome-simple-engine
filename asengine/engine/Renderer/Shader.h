#ifndef ASENGINE_SHADER_H
#define ASENGINE_SHADER_H

#include "GraphicsAPI.h"

#include "Texture.h"
#include "Color.h"
#include "engine/Math/mat3.h"
#include "engine/Math/vec2.h"

namespace ASEngine
{

    
    class ShaderParam {
        public:
            ShaderParam(int _uniformLocation);
            //set value
            void setValue(int _value);
            void setValue(float _value);
            void setValue(const vec2& _value);
            void setValue(const Color& _value);
            void setValue(const mat3& _value);
            void setValue(Texture _value);
        private:
            int uniformLocation = -1;
    };

    // shader can be used by materials
    class Shader {
    public:
        //should be private
        GLuint glProgram;
        //create shader from vertex code and fragment code
        bool create(const std::string &vertexCode, const std::string& fragmentCode);
        //use shader 
        void use();
        //get shader param by name
        ShaderParam getShaderParam(const std::string& param);
        //destroy this shader
        void destroy();
        //current shader
        static Shader getCurrent();


    private:
        GLuint loadShader(GLenum shaderType, const char* shaderCode);
        static Shader current;
    };

} // namespace ASEngine

#endif