#include "RendererBackend.h"

#include "ECS/SystemManager.h"
#include "Resource/ResourceManager.h"

#include "Renderer/VertexInput/VertexInputDescriptor.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Shader/ShaderSource.h"

// opengl
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/Buffer/OpenGLBuffer.h"
#include "OpenGL/Shader/OpenGLShader.h"
#include "OpenGL/Texture/OpenGLTexture.h"
#include "OpenGL/VertexInput/OpenGLVertexInputDescriptor.h"

// vulkan


namespace ASEngine
{
    void RendererBackend::CreateOpenGLRenderer()
    {
        ASENGINE_REGISTER_ABSTRACT_RESOURCE_CLASS(Buffer, OpenGLBuffer);
        ASENGINE_REGISTER_ABSTRACT_RESOURCE_CLASS(Texture, OpenGLTexture);
        ASENGINE_REGISTER_ABSTRACT_RESOURCE_CLASS(VertexInputDescriptor, OpenGLVertexInputDescriptor);
        ASENGINE_REGISTER_RESOURCE_CLASS(ShaderSource);
        ASENGINE_REGISTER_ABSTRACT_RESOURCE_CLASS(Shader, OpenGLShader);
        ASENGINE_REGISTER_RESOURCE_CLASS(Material);

        ASENGINE_REGISTER_SYSTEM(OpenGLRenderer);
    }
} // namespace ASEngine
