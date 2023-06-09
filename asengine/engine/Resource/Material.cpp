//
// Created by ksiks_wa3r on 3/18/23.
//

#include "Material.h"

namespace ASEngine
{

    // load shader
    GLuint Material::loadShader(GLenum shaderType, const char *shaderCode)
    {
        GLuint shader = glCreateShader(shaderType);
        // compile shader
        glShaderSource(shader, 1, &shaderCode, NULL);
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
            Log::out(message);
        }
        return shader;
    }
    // load material
    Material Material::load(const std::string &name, std::string vertexCode, std::string fragmentCode)
    {
// add precision mediump float for platform devices
#ifdef __ANDROID__
        fragmentCode = "precision mediump float;\n" + fragmentCode;
#endif

        // load shaders
        GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexCode.c_str());
        GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
        // create gl es program for shaders
        GLuint glProgram = glCreateProgram();
        // attach shaders
        glAttachShader(glProgram, vertexShader);
        glAttachShader(glProgram, fragmentShader);
        // creates OpenGL ES program executables
        glLinkProgram(glProgram);
        Log::out("glProgram created");
        // create material
        Material material{};
        material.id = name;
        material.glProgram = glProgram;
        // add default unifroms
        // transforms
        material.addShaderParam("view", MATERIAL_PARAM_MAT3);
        material.addShaderParam("camera", MATERIAL_PARAM_MAT3);
        // fragment
        material.addShaderParam("texture", MATERIAL_PARAM_TEXTURE);
        material.addShaderParam("modulate", MATERIAL_PARAM_COLOR);
        material.addShaderParam("isSolidColor", MATERIAL_PARAM_INT);
        // add material
        Material::add(name, material);
        return material;
    };

    // use material
    void Material::use(Material &material)
    {
        current = material;
        glUseProgram(material.glProgram);
        // pass view
        Material::current.setShaderParam("view", Screen::getView());
        // pass camera
        Material::current.setShaderParam("camera", Camera::current->getMatrix());
    };

    void Material::use(const MaterialID &materialId)
    {
        Material material = materialId;
        use(material);
    }

    std::unordered_map<ResourceID, Material> Material::materials = {};

    void Material::add(const MaterialID &materialId, Material &material)
    {
        Material::materials[materialId] = material;
    }

    Material Material::current = {};

    // set shader params
    void Material::setShaderParam(const std::string &param, int value)
    {
        glUniform1i(params[id][param].uniformLocation, value);
    }

    void Material::setShaderParam(const std::string &param, float value)
    {
        glUniform1f(params[id][param].uniformLocation, value);
    }

    void Material::setShaderParam(const std::string &param, vec2 value)
    {
        GLfloat values[] = {value.x, value.y};
        glUniform2fv(params[id][param].uniformLocation, 1, values);
    }

    void Material::setShaderParam(const std::string &param, Color value)
    {
        GLfloat values[] = {value.r, value.g, value.b, value.a};
        glUniform4fv(params[id][param].uniformLocation, 1, values);
    }

    void Material::setShaderParam(const std::string &param, mat3 value)
    {
        glUniformMatrix3fv(params[id][param].uniformLocation, 1, GL_TRUE, value.data);
    }

    void Material::setShaderParam(const std::string &param, Texture value)
    {
        // bind texture
        if (lastBindedTexture.id == value.id)
            return;
        lastBindedTexture = value;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, value.glTexture());
        glUniform1i(params[id][param].uniformLocation, 0);
    }

    void Material::addShaderParam(const std::string &param, MaterialParamType type)
    {
        int uniformLocation = glGetUniformLocation(glProgram, param.c_str());
        params[id][param] = MaterialParam{uniformLocation, type};
    }

    // params
    std::unordered_map<MaterialID, MaterialParamsMap> Material::params = {};
    // last binded texture
    Texture Material::lastBindedTexture = Texture{UINT32_MAX};

    // load from import
    void Material::importAll()
    {
        // load json file
        std::string importMaterialsString = Resource::loadAsText("materials/import.materials.json");
        // parse to json
        nlohmann::json importMaterials = nlohmann::json::parse(importMaterialsString);
        // import all materials
        for (int i = 0; i < importMaterials.size(); i++)
        {
            // get material info
            std::string materialName = importMaterials[i]["name"];
            std::string materialVertexFile = importMaterials[i]["vertex"];
            std::string materialFragmentFile = importMaterials[i]["fragment"];
            // load material
            std::string vertexCode = ASEngine::Resource::loadAsText("materials/" + materialVertexFile);
            std::string fragmentCode = ASEngine::Resource::loadAsText("materials/" + materialFragmentFile);
            ASEngine::Material::load(materialName, vertexCode, fragmentCode);
            Log::out("new material loaded");
        }
    }

    // terminate
    void Material::terminate()
    {
        // delete all materials
        for (auto material : materials)
        {
            material.second.destroy();
        }
        // clear all materials
        materials.clear();
        // clear all params
        params.clear();
    }

    // destroy
    void Material::destroy()
    {
        glDeleteProgram(glProgram);
    }

} // ASEngine