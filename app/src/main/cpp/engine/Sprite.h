//
// Created by ksiks_wa3r on 3/14/23.
//

#ifndef MY_APPLICATION_SPRITE_H
#define MY_APPLICATION_SPRITE_H

#include "Resource.h"

namespace ASEngine {

    typedef std::string SpriteID;

    class Sprite: Resource {
    public:
        //data
        Texture texture;
        int frames;
        int width;
        int height;
        vec2 offset = vec2::zero();

        //load
        static bool load( std::string& name, Texture _texture, int _frames, vec2 _offset );
        //destroy sprite
        void destroy();


    private:
        //sprite list
        static std::unordered_map<SpriteID, Sprite> sprites;

    };

} // ASEnginge

#endif //MY_APPLICATION_SPRITE_H
