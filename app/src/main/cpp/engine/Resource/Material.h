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

#include <unordered_map>
#include <sstream>
#include <vector>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

namespace ASEngine {

    typedef std::string MaterialID;


    //param index
    typedef std::string MaterialParamID;

    enum MaterialParamType {
        MATERIAL_PARAM_INT,
        MATERIAL_PARAM_FLOAT,
        MATERIAL_PARAM_VEC2,
        MATERIAL_PARAM_MAT3,
        MATERIAL_PARAM_TEXTURE,
        MATERIAL_PARAM_COLOR,
        //number of param type
        MATERIAL_PARAM_TYPE_NUMBER
    };

    //material param
    struct MaterialParam {
        int uniformLocation;
        MaterialParamType type;
    };

    //material is only the glProgam put it in a class makes it easier for abstraction
    class Material: public Resource {
    public:
        int glProgram;
        static Material current;
        //load material
        static Material load(std::string name, std::string vertexCode, std::string fragmentCode);
        //use material
        static void use(MaterialID materialId);
        static void use(Material& material);

        //add params
        void addShaderParam(std::string param, MaterialParamType type);

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

        //get  MaterialParamID
        MaterialParamID getParamID(std::string& param);

        //load shader
        static GLuint loadShader(GLenum shaderType, const char* shaderCode);
        //init quad for graphics
        static void quadInit();

        //shader params
        //link param id to data
        static std::unordered_map<MaterialParamID, MaterialParam> params;
        //last binded texture
        static Texture lastBindedTexture;
    };

} //ASEngine


#endif //MY_APPLICATION_MATERIAL_H
