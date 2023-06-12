
#ifndef ASENGINE_SPRITE_H
#define ASENGINE_SPRITE_H

#include "../Renderer/Texture.h"
#include "../Math/vec2.h"
#include "../Thirdparty/json.hpp"
#include "../Log/Log.h"
#include "Image.h"


namespace ASEngine {

    class Sprite {
    public:
        //data
        Texture texture;
        int frames = 0;
        int width = -1;
        int height = -1;
        vec2 offset = vec2{0.0f, 0.0f};

        //load
        bool load(Texture _texture, int _frames, vec2 _offset );
    };

} // ASEnginge

#endif //ASENGINE_SPRITE_H
