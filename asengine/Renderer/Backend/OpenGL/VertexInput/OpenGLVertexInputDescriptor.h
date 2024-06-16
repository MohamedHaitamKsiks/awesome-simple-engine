#ifndef __ASENGINE_OPENGL_VERTEX_INPUT_DESCRIPTOR_H
#define __ASENGINE_OPENGL_VERTEX_INPUT_DESCRIPTOR_H

#include <unordered_map>

#include "Renderer/Backend/OpenGL/OpenGL.h"
#include "Renderer/VertexInput/VertexInputDescriptor.h"

namespace ASEngine
{
    class OpenGLVertexInputDescriptor: public VertexInputDescriptor
    {
    public:
        ~OpenGLVertexInputDescriptor();

    private:
        void CreateImp(const std::vector<VertexInputLayout>& layouts) override;
    };
} // namespace ASEngine


#endif // __ASENGINE_OPENGL_VERTEX_INPUT_DESCRIPTOR_H