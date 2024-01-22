#ifndef ASENGINE_GRAPHICS_API_H
#define ASENGINE_GRAPHICS_API_H

// include opengl
#pragma region OPENGL_SPECIFICATION
    #ifdef __ANDROID__
        #include <GLES3/gl3.h>
        #include <GLES3/gl3ext.h>

    #else
        #include "GL/glew.h"
    #endif
#pragma endregion OPENGL_SPECIFICATION

#endif // ASENGINE_GRAPHICS_API_H