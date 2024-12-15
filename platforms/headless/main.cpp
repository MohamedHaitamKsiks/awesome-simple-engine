#include "ASEngine.h"

// Headless application

int main(int argc, char *argv[])
{
    // setup engine
    ASEngine::Runtime m_ASEngineRuntime{};
    m_ASEngineRuntime.Setup(argc, argv);

    // init
    ASEngine::Registry();
    m_ASEngineRuntime.Init();

    // run application
    int returnCode = m_ASEngineRuntime.Run([&m_ASEngineRuntime](float delta)
    {
        m_ASEngineRuntime.Update(delta);
    });

    // cleanup
    m_ASEngineRuntime.Terminate();

    return returnCode;
}