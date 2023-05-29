//
// Created by ksiks_wa3r on 3/14/23.
//

#include "Sprite.h"

namespace ASEngine {


    Sprite Sprite::load(const std::string& _name, Texture _texture, int _frames, vec2 _offset) {
        //create sprite
        Sprite sprite{};
        sprite.texture = _texture;
        sprite.width = _texture.width() / _frames;
        sprite.height = _texture.height();
        sprite.frames = _frames;
        sprite.offset = _offset;
        //add sprite
        Sprite::add(_name, sprite);
        return sprite;
    }

    void Sprite::add(const SpriteID& spriteId, Sprite &sprite) {
        Sprite::sprites[spriteId] = sprite;
    }

    void Sprite::destroy() {
        Sprite::sprites.erase(id);
    }

    std::unordered_map<ResourceID, Sprite> Sprite::sprites = {};

    void Sprite::importAll() {
        //load json file
        std::string importSpritesString = Resource::loadAsText("sprites/import.sprites.json");
        //parse to json
        nlohmann::json importedSprites = nlohmann::json::parse(importSpritesString);
        //import all sprites
        for (int i = 0; i < importedSprites.size(); i++) {
            //get sprite info
            std::string spriteName = importedSprites[i]["name"];
            std::string spriteImageFile = importedSprites[i]["image"];
            int spriteFrames = importedSprites[i]["frames"];
            vec2 spriteOffset = vec2 {
                importedSprites[i]["offset"]["x"],
                importedSprites[i]["offset"]["y"]
            };
            //load sprite
            Image spriteImage = Image::load("sprites/" + spriteImageFile);
            Texture spriteTexture = Texture::load(spriteImage);
            Sprite::load(spriteName, spriteTexture, spriteFrames, spriteOffset);
            //delete image
            spriteImage.destroy();
            ALOG("%s loaded", spriteName.c_str());
        }
    }

    //terminate sprites
    void Sprite::terminate() {
        sprites.clear();
    }


} // ASEngine