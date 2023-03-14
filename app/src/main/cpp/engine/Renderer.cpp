//
// Created by ksiks_wa3r on 3/1/23.
//

#include "Renderer.h"

namespace ASEngine {

    //rendering main functions
    //init renderer
    void Renderer::init() {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    }

    //on surface change
    void Renderer::surfaceChange(int width, int height) {
        glViewport(0, 0, width, height);
    }

    //draw frame
    void Renderer::draw() {
        glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }

} // ASEngine