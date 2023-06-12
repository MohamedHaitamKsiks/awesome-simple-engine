#include "Sprite.h"

namespace ASEngine 
{

    bool Sprite::load(Texture _texture, int _frames, vec2 _offset) 
    {
        if (!_frames) 
            return false;
        texture = _texture;
        width = _texture.width() / _frames;
        height = _texture.height();
        frames = _frames;
        offset = _offset;
        return true;
    }

    /*
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
            Log::out("new sprite loaded");
        }
    }
    */


} // ASEngine