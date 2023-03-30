//
// Created by ksiks_wa3r on 3/18/23.
//

#include "Material.h"


namespace ASEngine {

    void Material::quadInit() {
        //get position attribute
        int vPosition = glGetAttribLocation(Material::current.glProgram, "vPosition");
        glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(vPosition);
        //get texture coordinates attribute
        int vTextureCoord = glGetAttribLocation(Material::current.glProgram, "vTextureCoord");
        glVertexAttribPointer(vTextureCoord, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(vTextureCoord);
        //pass view
        Material::current.setShaderParam("view", Screen::getView());
        //pass camera
        Material::current.setShaderParam("camera", Camera::current->getMatrix());
    }


    //load shader
    GLuint Material::loadShader(GLenum shaderType, const char* shaderCode) {
        GLuint shader = glCreateShader(shaderType);
        //compile shader
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        //error
        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetShaderInfoLog(shader, 1024, &log_length, message);
            // Write the error to a log
            ALOG("%s", message);
        }


        return shader;
    }
    //load material
    Material Material::load(std::string name, std::string vertexCode, std::string fragmentCode) {
        //load shaders
        GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexCode.c_str());
        GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
        //create gl es program for shaders
        GLuint glProgram = glCreateProgram();
        //attach shaders
        glAttachShader(glProgram, vertexShader);
        glAttachShader(glProgram, fragmentShader);
        // creates OpenGL ES program executables
        glLinkProgram(glProgram);
        ALOG("glProgram created : %d", glProgram);
        //create material
        Material material{};
        material.glProgram = glProgram;
		//add default unifroms
		//transforms
		material.addShaderParam("view", MATERIAL_PARAM_MAT3);
		material.addShaderParam("camera", MATERIAL_PARAM_MAT3);
		material.addShaderParam("transform", MATERIAL_PARAM_MAT3);
		material.addShaderParam("zIndex", MATERIAL_PARAM_FLOAT);
		//frames
		material.addShaderParam("hframe", MATERIAL_PARAM_INT);
		material.addShaderParam("hframes", MATERIAL_PARAM_INT);
		material.addShaderParam("vframe", MATERIAL_PARAM_INT);
		material.addShaderParam("vframes", MATERIAL_PARAM_INT);
		//fragment
		material.addShaderParam("texture", MATERIAL_PARAM_TEXTURE);
		material.addShaderParam("modulate", MATERIAL_PARAM_COLOR);
		material.addShaderParam("isSolidColor", MATERIAL_PARAM_INT);
        //add material
        Material::add(name, material);
        return material;
    };

    //use material
    void Material::use(Material& material) {
        current = material;
        glUseProgram(material.glProgram);
        quadInit();
    };

    void Material::use(MaterialID materialId) {
        Material material = materialId;
        use(material);
    }

    std::unordered_map<ResourceID, Material> Material::materials = {};

    void Material::add(MaterialID materialId, Material &material) {
        material.id = materialId;
        Material::materials[materialId] = material;
    }

    Material Material::current = {};

    //set shader params
    void Material::setShaderParam(std::string param, int value) {
		//get param index
		MaterialParamID paramId = getParamID(param);
        glUniform1i(params[paramId].uniformLocation, value);
    }

    void Material::setShaderParam(std::string param, float value) {
		//get param index
		MaterialParamID paramId = getParamID(param);
        glUniform1f(params[paramId].uniformLocation, value);
    }

    void Material::setShaderParam(std::string param, vec2 value) {
		//get param index
		MaterialParamID paramId = getParamID(param);
        GLfloat values[] = {value.x, value.y};
        glUniform2fv(params[paramId].uniformLocation, 1, values);
    }

    void Material::setShaderParam(std::string param, Color value) {
		//get param index
		MaterialParamID paramId = getParamID(param);
        GLfloat values[] = {value.r, value.g, value.b, value.a};
        glUniform4fv(params[paramId].uniformLocation, 1, values);
    }

    void Material::setShaderParam(std::string param, mat3 value) {
		//get param index
		MaterialParamID paramId = getParamID(param);
        glUniformMatrix3fv(params[paramId].uniformLocation, 1, GL_TRUE, value.data);
    }


    void Material::setShaderParam(std::string param, Texture value) {
		//bind texture
		if (lastBindedTexture.id == value.id)
			return;
		//get param index
		MaterialParamID paramId = getParamID(param);
		lastBindedTexture = value;
		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, value.glTexture());
        glUniform1i(params[paramId].uniformLocation, 0);
    }

    void Material::addShaderParam(std::string param, MaterialParamType type) {
		MaterialParamID paramId = getParamID(param);
		int uniformLocation = glGetUniformLocation(glProgram, param.c_str());
        params[paramId] = MaterialParam{uniformLocation, type};
    }

	MaterialParamID Material::getParamID(std::string& param) {
		//std::stringstream ss;
		//ss << glProgram << "_" << param;
		return param;
	}

	//params
	std::unordered_map<MaterialParamID, MaterialParam> Material::params = {};

	//last binded texture
	Texture Material::lastBindedTexture = Texture{!0};


} // ASEngine