#ifndef ASENGINE_RENDERER_H
#define ASENGINE_RENDERER_H

#include "Core/Signals/Signal.h"
#include "Core/Singleton/Singleton.h"

#include "Managers/ShaderManager.h"
#include "Managers/ShaderProgramManager.h"
#include "Managers/TextureManager.h"
#include "Managers/BufferManager.h"

#include "Color.h"
#include "GraphicsAPI.h"

#include "VertexInput.h"

#include <unordered_map>

namespace ASEngine
{
    // api agnostic rendering API used as the main interface with different rendering managers
    class Renderer: public Singleton<Renderer>
    {
    public:
        Renderer();
        ~Renderer();

        // get texture manager
        static inline TextureManager* GetTextureManager()
        {
            return GetSingleton()->m_TextureManager.get();
        }

        // get shader manager
        static inline ShaderManager *GetShaderManager()
        {
            return GetSingleton()->m_ShaderManager.get();
        }

        // get shader program manager
        static inline ShaderProgramManager *GetShaderProgramManager()
        {
            return GetSingleton()->m_ShaderProgramManager.get();
        }

        // get buffer manager 
        static inline BufferManager* GetBufferManager()
        {
            return GetSingleton()->m_BufferManager.get();
        }

        // bind vertex buffer to an input rate
        void BindVertexBuffer(VertexInputRate inputRate, BufferID vertexBufferID);

        // bind index buffer
        void BindIndexBuffer(BufferID indexBufferID); 

        // draw elements, requires vertex and index buffer to be bounded
        void DrawElements(size_t instanceCount = 1);

        // clear color
        void Clear();

    private:
        // graphics manager
        std::unique_ptr<ShaderManager> m_ShaderManager;
        std::unique_ptr<ShaderProgramManager> m_ShaderProgramManager;
        std::unique_ptr<TextureManager> m_TextureManager;
        std::unique_ptr<BufferManager> m_BufferManager;

        // signals
        SignalConnection m_ResizeSignalConnection;

        // binded vertex buffers for each input_rate
        std::unordered_map<VertexInputRate, BufferID> m_CurrentVertexBuffers{};
        BufferID m_CurrentIndexBuffer = CHUNK_NULL;

        // init managers
        void InitManagers();

        // On window change size
        void OnWindowChangeSize(int width, int height);
    };

    
} // namespace ASEngine

#endif // ASENGINE_RENDERER_H