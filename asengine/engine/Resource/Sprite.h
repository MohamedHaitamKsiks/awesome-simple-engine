
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
        int frames;
        int width;
        int height;
        vec2 offset;
        //load
        bool load(Texture _texture, int _frames, vec2 _offset );
    };

} // ASEnginge

#endif //ASENGINE_SPRITE_H
