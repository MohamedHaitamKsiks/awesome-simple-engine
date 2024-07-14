#include "ASEngine.h"

// Desktop application

int main(int argc, char *argv[])
{
    // setup engine
    ASEngine::ASEngine m_ASEngine{};
    m_ASEngine.Setup(argc, argv);

    // create display
    ASEngine::Display::Create();
    ASEngine::Display& display = ASEngine::Display::GetInstance();

    // init
    ASEngine::Registry();
    m_ASEngine.Init();

    // run application
    int returnCode = m_ASEngine.Run([&m_ASEngine, &display](float delta)
    {
        display.BeginFrame();
        m_ASEngine.Update(delta);
        display.EndFrame();

        if (display.IsWindowShouldClose())
            m_ASEngine.Exit(0);
    });

    // cleanup 
    m_ASEngine.Terminate();
    
    return returnCode;
}