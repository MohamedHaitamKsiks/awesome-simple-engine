#ifndef ASENGINE_GRAPHICS_API_H
#define ASENGINE_GRAPHICS_API_H

#ifdef __ANDROID__
#include <GLES3/gl32.h>
#include <GLES3/gl3ext.h>

#else
#include <GL/glew.h>

#endif

#endif // ASENGINE_GRAPHICS_API_H