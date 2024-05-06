#ifndef ASENGINE_RENDERER_H
#define ASENGINE_RENDERER_H

#include "ECS/System.h"
#include "Core/Singleton/Singleton.h"

namespace ASEngine
{
    /*
        Abstract class of the renderer
        It is the main interface between the user and the gpu
        You can create multiple classes inheriting from this class with specifications 
        For example: OpenGLRenderer, VulkanRenderer...
    */
    class IRenderer: public ISystem, public Singleton<IRenderer>
    {
    public:
        virtual void BindVertexBuffer() = 0;
    };
} // namespace ASEngine


#endif // ASENGINE_RENDERER_H