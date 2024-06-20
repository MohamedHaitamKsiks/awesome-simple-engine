#include "DesktopApplication.h"

namespace ASEngine
{

    int DesktopApplication::Run()
    {
        // init window
        if (!Init())
        {
            Debug::Error("Application coudn't started!");
            return 1;
        }

        // start gameloop
        // delta
        float delta = 0.01f;

        /* Loop until the user closes the window */
        do
        {
            // get time now
            const auto pastTime = std::chrono::high_resolution_clock::now();

            Update(delta);

            // compute delta
            const auto currentTime = std::chrono::high_resolution_clock::now();
            delta = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count() / SEC_TO_MICRO;
        
        } while( !Display::GetInstance().IsWindowShouldClose() );
        
        Terminate();
        return 0;
    }

    DesktopApplication::~DesktopApplication()
    {
        
    }

    bool DesktopApplication::Init()
    {
        // setup application modules and systems
        m_ASEngine.Setup();
        Display::Create(Renderer::Backend::OPENGL);
        Registry();
        m_ASEngine.Init();
       
        return true;
    }


    void DesktopApplication::Update(float delta)
    {
        Display::GetInstance().BeginFrame();
        m_ASEngine.Update(delta);
        Display::GetInstance().EndFrame();
    }

    void DesktopApplication::Terminate()
    {
        m_ASEngine.Terminate();
    }
} // namespace ASEngine