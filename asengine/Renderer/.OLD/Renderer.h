#ifndef ASENGINE_RENDERER_H
#define ASENGINE_RENDERER_H

#include "Core/Signals/Signal.h"
#include "ECS/System.h"
#include "Core/Singleton/Singleton.h"

#include "Managers/BufferManager.h"

#include "Color.h"
#include "GraphicsAPI.h"

#include "VertexInput.h"

#include <unordered_map>

namespace ASEngine
{
    // api agnostic rendering API used as the main interface with different rendering managers
    class Renderer : public ISystem, public Singleton<Renderer>
    {
    public:
        // bind vertex buffer to an input rate
        void BindVertexBuffer(VertexInputRate inputRate, BufferID vertexBufferID);

        // bind index buffer
        void BindIndexBuffer(BufferID indexBufferID); 

        // draw elements, requires vertex and index buffer to be bounded
        void DrawElements(uint32_t indexCount, size_t instanceCount = 1);

        // clear color
        void Clear();

    private:
        // signals
        SignalConnection m_ResizeSignalConnection;

        // binded vertex buffers for each input_rate
        std::unordered_map<VertexInputRate, BufferID> m_CurrentVertexBuffers{};
        BufferID m_CurrentIndexBuffer = CHUNK_NULL;

        // On window change size
        void OnWindowChangeSize(int width, int height);
    };

    
} // namespace ASEngine

#endif // ASENGINE_RENDERER_H