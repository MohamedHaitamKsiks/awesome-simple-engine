#ifndef ASENGINE_RENDERER_2D_H
#define ASENGINE_RENDERER_2D_H

#include <cmath>
#include <vector>

#include "Core/Singleton/Singleton.h"
#include "Core/Math/mat3.h"
#include "Core/Window/Window.h"

#include "Resource/Shader.h"
#include "Resource/Material.h"

#include "Renderer/GraphicsAPI.h"
#include "Renderer/Viewport.h"
#include "Renderer/ShaderUniform.h"
#include "Renderer/ShaderProgram.h"

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
            static inline Camera2D& GetCamera2D()
            {
                return GetSingleton()->m_Camera2D;
            };

            // draw a quad with a given material
            static inline void DrawQuad(const Quad2D &quad2D, ResourceID materialID)
            {
                GetSingleton()->IDrawQuad(quad2D, materialID);
            };

            // begin rendering context
            static inline void Begin() { GetSingleton()->IBegin(); };

            // end rendering context
            static inline void End() { GetSingleton()->IEnd(); };
        private:
            // resize signal connection
            SignalConnection m_ResizeSignalConnection;

            // camera2D
            Camera2D m_Camera2D{};

            // cache projection matrices
            mat3 m_CameraProjectionMatrix = mat3::IDENTITY();
            mat3 m_ViewProjectionMatrix = mat3::IDENTITY();

            // cache projection matrices names
            UniqueString m_CameraParamName;
            UniqueString m_ViewParamName;

            // current shader
            ResourceID m_CurrentShaderID = CHUNK_NULL;
            // current material
            ResourceID m_CurrentMaterialID = CHUNK_NULL;

            // vertex buffer to batch render
            VertexBufferObject2D m_Vbo2D{};

            // On window change size
            void OnWindowChangeSize(int width, int height);

            // begin rendering context internal
            void IBegin();

            // end renderering context internal
            void IEnd();

            // draw quad internal
            void IDrawQuad(const Quad2D &quad2D, ResourceID materialID);
    };
} // namespace ASEngine


#endif // ASENGINE_RENDERE_2D_H