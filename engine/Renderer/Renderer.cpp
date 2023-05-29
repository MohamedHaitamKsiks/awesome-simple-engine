//
// Created by ksiks_wa3r on 3/1/23.
//

#include "Renderer.h"

namespace ASEngine {

    //rendering main functions
    //init renderer
    void Renderer::init() {
        //enable blend
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //set clear color
        glClearColor(0.5f, 0.5f, 0.55f, 1.0f);


    }


    //draw frame
    void Renderer::draw() {
        glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		//use default material
        Material::use("mt_default");
    }



} // ASEngine