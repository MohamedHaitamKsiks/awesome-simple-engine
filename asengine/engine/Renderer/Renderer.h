#ifndef ASENGINE_RENDERER_H
#define ASENGINE_RENDERER_H

#include "Core/Singleton/Singleton.h"

#include "Managers/ShaderManager.h"
#include "Managers/ShaderProgramManager.h"
#include "Managers/TextureManager.h"
#include "Managers/BufferManager.h"

#include "Color.h"

#include "GraphicsAPI.h"

namespace ASEngine
{
    // api agnostic rendering API used as the main interface with different rendering managers
    class Renderer: public Singleton<Renderer>
    {
    public:
        Renderer();
        ~Renderer() {};

        // get texture manager
        inline TextureManager* GetTextureManager()
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

        // draw elements, requires vertex and index buffer to be bounded
        static void DrawElements(BufferID vertexBufferID, BufferID indexBufferID, size_t indexCount, size_t instanceCount = 1);

        // clear color
        static void Clear();

    private:
        // graphics manager
        std::unique_ptr<ShaderManager> m_ShaderManager;
        std::unique_ptr<ShaderProgramManager> m_ShaderProgramManager;
        std::unique_ptr<TextureManager> m_TextureManager;
        std::unique_ptr<BufferManager> m_BufferManager;

        // init managers
        void InitManagers();
        
    };

    
} // namespace ASEngine

#endif // ASENGINE_RENDERER_H