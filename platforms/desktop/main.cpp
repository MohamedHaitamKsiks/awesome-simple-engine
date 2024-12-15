#include "ASEngine.h"

// Desktop application

int main(int argc, char *argv[])
{
    // setup engine
    ASEngine::Runtime m_ASEngineRuntime{};
    m_ASEngineRuntime.Setup(argc, argv);

    // create display
    ASEngine::Display::Create();
    ASEngine::Display& display = ASEngine::Display::GetInstance();

    // init
    ASEngine::Registry();
    m_ASEngineRuntime.Init();

    // run application
    int returnCode = m_ASEngineRuntime.Run([&m_ASEngineRuntime, &display](float delta)
    {
        display.BeginFrame();
        m_ASEngineRuntime.Update(delta);
        display.EndFrame();

        if (display.IsWindowShouldClose())
            m_ASEngineRuntime.Exit(0);
    });

    // cleanup
    m_ASEngineRuntime.Terminate();

    return returnCode;
}