#include "Renderer2D.h"

namespace ASEngine
{
    Renderer2D::Renderer2D()
    {

        // create the vbo2D
        m_Vbo2D.Create();

        // cache param names
        m_CameraParamName = UniqueString("u_Camera");
        m_ViewParamName = UniqueString("u_View");

        // connect to on window change signal
        std::function<void(int, int)> callback = [this](int width, int height)
        {
            OnWindowChangeSize(width, height);
        }; 
        m_ResizeSignalConnection = Window::ResizeSignal().Connect(callback);
    }

    Renderer2D::~Renderer2D()
    {
        Window::ResizeSignal().Disconnect(m_ResizeSignalConnection);
    }

    void Renderer2D::OnWindowChangeSize(int width, int height)
    {
        // get aspect ratio of viewport
        float viewportAspectRatio = Viewport::GetSize().x / Viewport::GetSize().y;

        // get aspect ratio of window
        float windowAspectRatio = (float) width / (float) height;
        
        // same aspect ratio
        float precision = 0.0001f;
        if (abs(viewportAspectRatio - windowAspectRatio) < precision)
        {
            // recompute viewport 
            glViewport(0, 0, width, height);
        }
        // window larger than viewport
        else if (windowAspectRatio > viewportAspectRatio)
        {
            // get new width
            int newWidth = (int) (viewportAspectRatio * height);
            int viewportPosition = (width - newWidth) / 2;
            glViewport(viewportPosition, 0, newWidth, height);
        }
        // window longuer than viewport
        else
        {
            // get new height
            int newHeight = (int)(width / viewportAspectRatio);
            int viewportPosition = (height - newHeight) / 2;
            glViewport(0, viewportPosition, width, newHeight);
        }
    }

    void Renderer2D::IBegin()
    {
        glClear(GL_DEPTH_BUFFER_BIT);

        // cache projection matrices
        m_ViewProjectionMatrix = Viewport::GetProjectionMatrix();
        m_CameraProjectionMatrix = mat3::Rotation(m_Camera2D.Rotation * -1.0f) * mat3::Scale(vec2::ONE() * m_Camera2D.Zoom) * mat3::Translate(m_Camera2D.Position * -1.0f);
        // set materials and shaders to null
        m_CurrentShaderID = CHUNK_NULL;
        m_CurrentMaterialID = CHUNK_NULL;

        m_Vbo2D.Bind();
    }

    void Renderer2D::IBeginUI()
    {
        // cache projection matrices
        m_ViewProjectionMatrix = Viewport::GetProjectionMatrix();
        m_CameraProjectionMatrix = mat3::IDENTITY();
        // set materials and shaders to null
        m_CurrentShaderID = CHUNK_NULL;
        m_CurrentMaterialID = CHUNK_NULL;

        m_Vbo2D.Bind();
    }

    void Renderer2D::IEnd()
    {
        // submit last batch
        m_Vbo2D.Submit();
    }

    void Renderer2D::IDrawQuad(const Quad2D &quad2D, ResourceID materialID)
    {
        
        // check material changed
        if (materialID != m_CurrentMaterialID)
        {
            // submit current batch
            m_Vbo2D.Submit();

            // get material
            m_CurrentMaterialID = materialID;
            Material& material = ResourceManager<Material>::Get(materialID);

            // check if shader changed
            if (material.GetShaderID() != m_CurrentShaderID)
            {
                // bind the new shader
                m_CurrentShaderID = material.GetShaderID();
                Shader& shader = ResourceManager<Shader>::Get(m_CurrentShaderID);

                // bind shader
                shader.Bind();
                const auto& program = shader.GetShaderProgram();
                program.BindVertex2D();
            }

            // set projection matrices
            material.SetShaderParam(m_CameraParamName, m_CameraProjectionMatrix);
            material.SetShaderParam(m_ViewParamName, m_ViewProjectionMatrix);
            
            // bind material
            material.Bind();
        }

        // add quad to current batch
        m_Vbo2D.PushQuad(quad2D);
    }

} // namespace ASEngine
