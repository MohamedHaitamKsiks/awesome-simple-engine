

#include <iostream>
#include <chrono>
#define SEC_TO_MICRO 1000000.0f;

#include "engine/asengine.h"
#include "objects/loadGameObject.h"

//#define GLFW_INCLUDE_ES2
#include "GLFW/glfw3.h"

int main() {
    loadGameObjects();
    ASEngine::Application::create(ASEngine::PLATFORM_DESKTOP);

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(720, 1280, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    ASEngine::Application::getSingleton()->init();

    //delta
    float delta = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // get time now
        auto pastTime = std::chrono::high_resolution_clock::now();

        ASEngine::Application::getSingleton()->update(delta);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();

        // compute delta
        auto currentTime = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count() / SEC_TO_MICRO;
    }

    ASEngine::Application::getSingleton()->terminate();
    glfwTerminate();

    return 0;
}