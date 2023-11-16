#include "GraphicsAPI.h"

namespace ASEngine
{
    void GraphicsAPI::Init()
    { 
        // init glew for desktop devices
        #ifndef __ANDROID__
        glewInit();
        #endif

        // print gpu used
        const GLubyte *renderer = glGetString(GL_RENDERER);
        Debug::Log(renderer);

        // enable blend
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // set clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);
    }

} // namespace ASEngine
