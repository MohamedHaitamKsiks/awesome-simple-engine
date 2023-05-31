#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#define GLFW_INCLUDE_ES2
#include "GLFW/glfw3.h"

#include "asengine.h"
#include "objects/loadGameObject.h"

int main() {
    loadGameObjects();

    ASEngine::Application::create(ASEngine::PLATFORM_DESKTOP);

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    ASEngine::Application::getSingleton()->init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        ASEngine::Application::getSingleton()->update(0.0f);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ASEngine::Application::getSingleton()->terminate();
    glfwTerminate();
    return 0;
}