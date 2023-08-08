#include "Renderer2D.h"

namespace ASEngine
{
    Renderer2D::Renderer2D()
    {
        // init glew for desktop devices
        #ifndef __ANDROID__
        glewInit();
        #endif

        // enable blend
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // set clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // create the vbo2D
        m_Vbo2D.Create();

        // cache param names
        m_CameraParamName = UniqueString("u_Camera");
        m_ViewParamName = UniqueString("u_View");

        // connect to on window change signal
        Window::ResizeSignal().Connect(std::bind(&Renderer2D::OnWindowChangeSize, this, std::placeholders::_1, std::placeholders::_2));
    }

    Renderer2D::~Renderer2D()
    {
        
    }

    void Renderer2D::OnWindowChangeSize(int width, int height)
    {
        // recompute viewport 
        glViewport(0, 0, width, height);
        
    }

    void Renderer2D::IBegin()
    {
        // cache projection matrices
        m_ViewProjectionMatrix = Viewport::GetProjectionMatrix();
        m_CameraProjectionMatrix = mat3::IDENTITY();

        // set materials and shaders to null
        m_CurrentShaderID = CHUNK_NULL;
        m_CurrentMaterialID = CHUNK_NULL;

        // clear background
        glClear(GL_COLOR_BUFFER_BIT);
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
