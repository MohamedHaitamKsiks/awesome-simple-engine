#ifndef ASENGINE_GRAPHICS_API_H
#define ASENGINE_GRAPHICS_API_H

#ifdef __ANDROID__
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#else
#include "GL/glew.h"

#endif

#include "Core/Log/Log.h"

namespace ASEngine
{
    class GraphicsAPI
    {
    public:
        // init opengl
        static void Init();

        // clear screen 
        static inline void Clear()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    };
} // namespace ASEngine


#endif // ASENGINE_GRAPHICS_API_H