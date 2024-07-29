#include "ASEngine.h"

#include <emscripten/emscripten.h>
#define SEC_TO_MIL 1000.0f

ASEngine::ASEngine* g_ASEngine = nullptr;
float g_PreviousTime = 0.0f;


static void Update()
{
    // get time now
    float currentTime = emscripten_get_now();
    float deltaTime = (currentTime - g_PreviousTime) / SEC_TO_MIL;

    g_PreviousTime = currentTime;

    ASEngine::Display::GetInstance().BeginFrame();
    ASEngine::ASEngine::GetInstance().Update(deltaTime);
    ASEngine::Display::GetInstance().EndFrame();
}


int main(int argc, char *argv[])
{
    // setup engine
    g_ASEngine = new ASEngine::ASEngine();
    g_ASEngine->Setup(argc, argv);

    // create display
    ASEngine::Display::Create();

    // init
    ASEngine::Registry();
    g_ASEngine->Init();

    g_PreviousTime = emscripten_get_now();
    emscripten_set_main_loop(Update, 0, false);
}
