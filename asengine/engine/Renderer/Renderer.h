#ifndef ASENGINE_RENDERER_H
#define ASENGINE_RENDERER_H

#include "GraphicsAPI.h"

#include "engine/FileSystem/File.h"

#include "Camera.h"
#include "Color.h"
#include "Screen.h"
#include "Shader.h"
#include "VertexBufferObject.h"

namespace ASEngine {

    class Renderer {
    public:
        //initiate the renderer
        void init();
        //draw renderer
        void draw();
        //deconstructor
        ~Renderer();

    private:
        // default shader will be used 
        Shader defaultShader;

        // 

    };  

} // ASEngine

#endif //ASENGINE_RENDERER_H
