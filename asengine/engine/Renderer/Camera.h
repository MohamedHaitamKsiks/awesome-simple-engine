#ifndef ASENGINE_CAMERA_H
#define ASENGINE_CAMERA_H

#include "engine/Math/vec2.h"
#include "engine/Math/mat3.h"

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

#endif //ASENGINE_CAMERA_H
