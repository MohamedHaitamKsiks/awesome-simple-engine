//
// Created by ksiks_wa3r on 3/13/23.
//

#ifndef MY_APPLICATION_MATERIAL_H
#define MY_APPLICATION_MATERIAL_H

#include "../Renderer/Renderer.h"
#include "../Renderer/Texture.h"
#include "../Renderer/Color.h"
#include "../log.h"
#include "Resource.h"
#include "../Math/mat3.h"
#include "../Math/vec2.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

namespace ASEngine {

    typedef std::string MaterialID;

    class Material: public Resource {
    public:
        int glProgram;
        static Material current;
        //load material
        static Material load(std::string name, std::string vertexCode, std::string fragmentCode);
        //use material
        static void use(MaterialID materialId);
        static void use(Material& material);

        //set params
        void setShaderParam(std::string param, int value);
        void setShaderParam(std::string param, float value);
        void setShaderParam(std::string param, vec2 value);
        void setShaderParam(std::string param, mat3 value);
        void setShaderParam(std::string param, Texture value);
        void setShaderParam(std::string param, Color value);

        //add material
        static void add(MaterialID materialId, Material& material);

        //equiv between ResourceID and Resource
        //= operator
        Material& operator=(MaterialID materialId) {
            return Material::materials[materialId];
        };

        //constructors
        Material() {};
        Material(int _glProgram) {
            glProgram = _glProgram;
        };

        Material(MaterialID materialId) {
            *this = Material::materials[materialId];
        };

        static std::unordered_map<ResourceID, Material> materials;
    private:
        //load shader
        static GLuint loadShader(GLenum shaderType, const char* shaderCode);
        //init quad for graphics
        static void quadInit();
    };

} //ASEngine


#endif //MY_APPLICATION_MATERIAL_H
