//
// Created by ksiks_wa3r on 3/21/23.
//

#ifndef MY_APPLICATION_CAMERA_H
#define MY_APPLICATION_CAMERA_H

#include "../Math/vec2.h"
#include "../Math/mat3.h"

namespace ASEngine {

    class Camera {

    public:
        //transform
         vec2 position = vec2{0.0f, 0.0f};
         vec2 offset = vec2{0.0f, 0.0f};
         float zoom = 1.0f;
         float rotation = 0.0f;

         //get camera matrix
         mat3 getMatrix();

         //current camera
         static Camera* current;

    };

} // ASEngine

#endif //MY_APPLICATION_CAMERA_H
