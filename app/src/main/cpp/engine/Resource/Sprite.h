//
// Created by ksiks_wa3r on 3/14/23.
//

#ifndef MY_APPLICATION_SPRITE_H
#define MY_APPLICATION_SPRITE_H

#include "../Renderer/Texture.h"
#include "../Math/vec2.h"
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
        static Sprite load(std::string _name, Texture _texture, int _frames, vec2 _offset );
        //add sprite
        static void add(SpriteID spriteId, Sprite& sprite);
        //destroy
        void destroy();

        //equiv between ResourceID and Resource
        //= operator
        Sprite& operator=(SpriteID spriteId) {
                return Sprite::sprites[spriteId];
        };

        //constructors
        Sprite() {};
        Sprite(SpriteID spriteId) {
                *this = Sprite::sprites[spriteId];
        };

        static std::unordered_map<ResourceID, Sprite> sprites;

    };

} // ASEnginge

#endif //MY_APPLICATION_SPRITE_H
