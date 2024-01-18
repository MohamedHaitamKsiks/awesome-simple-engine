#include "Renderer2D.h"

namespace ASEngine
{
    Renderer2D::Renderer2D()
    {

        // create the vbo2D
        m_Vbo2D.Create();

        // cache param names
        m_RenderUniformBufferName = UniqueString("Render");
        m_ProjectionParamName = UniqueString("Projection");
        m_ViewParamName = UniqueString("View");

    }

    Renderer2D::~Renderer2D()
    {
        
    }

    /*
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
    */

    void Renderer2D::Begin()
    {
        // cache projection matrices
        m_ProjectionMatrix = Viewport::GetProjectionMatrix();
        m_ViewMatrix = mat3::Rotation(m_Camera2D.Rotation * -1.0f) * 
            mat3::Scale(vec2::ONE() * m_Camera2D.Zoom) * 
            mat3::Translate(m_Camera2D.Position * -1.0f);

        // set materials and shaders to null
        m_CurrentShaderID = CHUNK_NULL;
        m_CurrentMaterialID = CHUNK_NULL;

        m_Vbo2D.Bind();
    }

    void Renderer2D::BeginUI()
    {
        // cache projection matrices
        m_ProjectionMatrix = Viewport::GetProjectionMatrix();
        m_ViewMatrix = mat3::IDENTITY();
        // set materials and shaders to null
        m_CurrentShaderID = CHUNK_NULL;
        m_CurrentMaterialID = CHUNK_NULL;

        m_Vbo2D.Bind();
    }

    void Renderer2D::End()
    {
        // submit last batch
        m_Vbo2D.Submit();
    }

    void Renderer2D::DrawQuad(const Quad2D &quad2D, ResourceID materialID)
    {
        
        // check material changed
        if (materialID != m_CurrentMaterialID)
        {
            // submit current batch
            m_Vbo2D.Submit();

            // get material
            m_CurrentMaterialID = materialID;
            auto& material = ResourceManager<Material>::Get(materialID);

            // check if shader changed
            if (material.GetShaderID() != m_CurrentShaderID)
            {
                // bind the new shader
                m_CurrentShaderID = material.GetShaderID();
                auto& shader = ResourceManager<Shader>::Get(m_CurrentShaderID);

                // bind shader
                shader.Bind();
            }

            // set projection matrices
            material.SetUniformBufferParam(m_RenderUniformBufferName, m_ViewParamName, m_ViewMatrix);
            material.SetUniformBufferParam(m_RenderUniformBufferName, m_ProjectionParamName, m_ProjectionMatrix);

            // bind material
            material.Bind();
        }

        // add quad to current batch
        m_Vbo2D.PushQuad(quad2D);
    }

} // namespace ASEngine
