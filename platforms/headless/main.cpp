#include "ASEngine.h"

// Headless application

int main(int argc, char *argv[])
{
    // setup engine
    ASEngine::ASEngine m_ASEngine{};
    m_ASEngine.Setup(argc, argv);

    // init
    ASEngine::Registry();
    m_ASEngine.Init();

    // run application
    int returnCode = m_ASEngine.Run([&m_ASEngine](float delta)
    {
        m_ASEngine.Update(delta);
    });

    // cleanup 
    m_ASEngine.Terminate();
    
    return returnCode;
}