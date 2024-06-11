#ifndef __ASENGINE_OPENGL_H
#define __ASENGINE_OPENGL_H
// include opengl
#ifdef __ANDROID__
    #include <GLES3/gl3.h>
    #include <GLES3/gl3ext.h>

#else
    #include "GL/glew.h"
    #define ASENGINE_USING_GLEW
#endif

#endif // __ASENGINE_OPENGL_H