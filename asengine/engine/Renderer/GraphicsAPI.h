#ifndef ASENGINE_GRAPHICS_API_H
#define ASENGINE_GRAPHICS_API_H

// include opengl
#ifdef OPENGL
    #ifdef __ANDROID__
        #include <GLES3/gl3.h>
        #include <GLES3/gl3ext.h>

    #else
        #include "GL/glew.h"
    #endif
#endif


#endif // ASENGINE_GRAPHICS_API_H