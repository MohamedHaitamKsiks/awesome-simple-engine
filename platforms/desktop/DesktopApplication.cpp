#include "DesktopApplication.h"

void DesktopApplication::start() {
    if (!init()) {
        ASEngine::Log::out("Application coudn't started!");
        return;
    }

    // start gameloop
    // delta
    float delta = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // get time now
        auto pastTime = std::chrono::high_resolution_clock::now();

        update(delta);

        // compute delta
        auto currentTime = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count() / SEC_TO_MICRO;
    }

    terminate();
}

bool DesktopApplication::init() {
    //create asengine app
    ASEngine::Application::create(ASEngine::PLATFORM_DESKTOP);

    /* Initialize the library */
    if (!glfwInit())
        return false;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(720/2 , 1280/2 , "Hello World", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    ASEngine::Application::getSingleton()->init();

    return true;

}

void DesktopApplication::update(float delta) {
    ASEngine::Application::getSingleton()->update(delta);
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    /* Poll for and process events */
    glfwPollEvents();
}

void DesktopApplication::terminate() {
    ASEngine::Application::getSingleton()->terminate();
    glfwTerminate();
}