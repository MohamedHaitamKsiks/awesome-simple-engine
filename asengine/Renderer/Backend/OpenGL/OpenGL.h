#ifndef __ASENGINE_OPENGL_H
#define __ASENGINE_OPENGL_H

#ifdef ASENGINE_WEB
  #include <GLES3/gl3.h>
#else
  #include "GL/glew.h"
  #define ASENGINE_USING_GLEW
#endif

#endif // __ASENGINE_OPENGL_H