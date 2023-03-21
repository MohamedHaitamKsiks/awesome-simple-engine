//
// Created by ksiks_wa3r on 3/14/23.
//

#include "Sprite.h"

namespace ASEngine {


    Sprite Sprite::load(std::string _name, Texture _texture, int _frames, vec2 _offset) {
        //create sprite
        Sprite sprite{};
        sprite.texture = _texture;
        sprite.width = _texture.width() / _frames;
        sprite.height = _texture.height() / _frames;
        sprite.frames = _frames;
        sprite.offset = _offset;
        //add sprite
        Sprite::add(_name, sprite);
        return sprite;
    }

    void Sprite::add(SpriteID spriteId, Sprite &sprite) {
        sprite.id = spriteId;
        Sprite::sprites[spriteId] = sprite;
    }

    void Sprite::destroy() {
        Sprite::sprites.erase(id);
    }

    std::unordered_map<ResourceID, Sprite> Sprite::sprites = {};


} // ASEngine