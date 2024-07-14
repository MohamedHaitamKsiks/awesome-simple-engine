#include "ASEngine.h"
#include <emscripten/emscripten.h>


ASEngine::ASEngine* g_ASEngine = nullptr;


static void Update()
{
    ASEngine::Display::GetInstance().BeginFrame();
    ASEngine::ASEngine::GetInstance().Update(0.02f);
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

    emscripten_set_main_loop(Update, 0, false);
}