#include <chrono>
#define SEC_TO_MICRO 1000000.0f;

#include "ASEngine.h"

// headless application
// simple game loop with no screen nor any input system
int main(int argc, char* argv[])
{
    ASEngine::ASEngine engine{};
    engine.Setup(argc, argv);
    ASEngine::Registry();
    engine.Init();

    float delta = 0.01f;
    while (true)
    {
        const auto pastTime = std::chrono::high_resolution_clock::now();
        
        engine.Update(delta);
        
        // compute delta
        const auto currentTime = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count() / SEC_TO_MICRO;
    }  
}