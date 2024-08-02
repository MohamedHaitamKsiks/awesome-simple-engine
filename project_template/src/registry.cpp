#include "ASEngine.h"

// module registry for the game
namespace ASEngine
{
    void Registry()
    {
        Module2D::Init();
        AudioModule::Init();
    }
} // ASEngine
