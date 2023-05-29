//
// Created by ksiks_wa3r on 3/13/23.
//

#ifndef MY_APPLICATION_MATERIAL_H
#define MY_APPLICATION_MATERIAL_H

#include "Resource.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/Texture.h"
#include "../Renderer/Color.h"
#include "../log.h"
#include "../Math/mat3.h"
#include "../Math/vec2.h"
#include "../Thirdparty/json.hpp"

#include <unordered_map>
#include <sstream>
#include <vector>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

namespace ASEngine {

    //material id
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

    typedef std::unordered_map<MaterialParamID, MaterialParam> MaterialParamsMap;


    //material is only the glProgam put it in a class makes it easier for abstraction
    class Material: public Resource {
    public:
        int glProgram;
        static Material current;
        //load material
        static Material load(const std::string& name, std::string vertexCode, std::string fragmentCode);
        static void importAll();
        //termiante materials
        static void terminate();
        //destroy
        void destroy();
        //use material
        static void use(const MaterialID& materialId);
        static void use(Material& material);

        //add params
        void addShaderParam(const std::string& param, MaterialParamType type);

        //set params
        void setShaderParam(const std::string& param, int value);
        void setShaderParam(const std::string& param, float value);
        void setShaderParam(const std::string& param, vec2 value);
        void setShaderParam(const std::string& param, mat3 value);
        void setShaderParam(const std::string& param, Texture value);
        void setShaderParam(const std::string& param, Color value);


        //add material
        static void add(const MaterialID& materialId, Material& material);

        //equiv between ResourceID and Resource
        //= operator
        Material& operator=(const MaterialID& materialId) {
            return Material::materials[materialId];
        };

        //constructors
        Material() {};
        Material(int _glProgram) {
            glProgram = _glProgram;
        };

        Material(const MaterialID& materialId) {
            *this = Material::materials[materialId];
        };


    private:
        //materials
        static std::unordered_map<ResourceID, Material> materials;
        //load shader
        static GLuint loadShader(GLenum shaderType, const char* shaderCode);
        //shader params
        //link param id to data
        static std::unordered_map<MaterialID, MaterialParamsMap> params;
        //last binded texture
        static Texture lastBindedTexture;
    };

} //ASEngine


#endif //MY_APPLICATION_MATERIAL_H
