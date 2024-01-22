#ifndef ASENGINE_RENDERER_2D_H
#define ASENGINE_RENDERER_2D_H

#include <cmath>
#include <vector>
#include <functional>

#include "Core/Singleton/Singleton.h"
#include "Core/Math/mat3.h"
#include "Core/Window/Window.h"

#include "Resource/Shader.h"
#include "Resource/Material.h"

#include "Renderer/GraphicsAPI.h"
#include "Renderer/Viewport.h"

#include "Camera2D.h"
#include "VertexBufferObject2D.h"

namespace ASEngine
{
    // renderer 2D
    class Renderer2D: public Singleton<Renderer2D>
    {
        public:
            Renderer2D();
            ~Renderer2D();

            // get camera 2D
            inline Camera2D& GetCamera2D()
            {
                return m_Camera2D;
            };

            // draw quad
            void DrawQuad(const Quad2D &quad2D, ResourceID materialID);
            
            // begin rendering context
            void Begin();

            // end rendering context
            void End();

            // begin ui
            void BeginUI();

            // end ui
            inline void EndUI() 
            {
                End();
            }
        private:
            // camera2D
            Camera2D m_Camera2D{};

            // cache matrices
            mat3 m_ViewMatrix = mat3::IDENTITY();
            mat3 m_ProjectionMatrix = mat3::IDENTITY();

            // cache projection matrices names
            UniqueString m_RenderUniformBufferName;
            UniqueString m_ViewParamName;
            UniqueString m_ProjectionParamName;

            // current shader
            ResourceID m_CurrentShaderID = CHUNK_NULL;
            // current material
            ResourceID m_CurrentMaterialID = CHUNK_NULL;

            // vertex buffer to batch render
            VertexBufferObject2D m_Vbo2D{};
    };
} // namespace ASEngine


#endif // ASENGINE_RENDERE_2D_H