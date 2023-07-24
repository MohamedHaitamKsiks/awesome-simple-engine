#include "Sprite.h"

namespace ASEngine 
{

    bool Sprite::Load(Texture texture, int frames, const vec2& offset) 
    {
        /*if (m_Frames <= 0) 
            return false;

        m_Texture = texture;
        m_Width = texture.width() / frames;
        m_Height = texture.height();
        m_Frames = frames;
        m_Offset = offset;
        return true;*/
    }

    
    void Sprite::ImportAll() {
        /*
        //load json file
        File importSpritesFile;
        importSpritesFile.Open("sprites/import.sprites.json", FileOpenMode::READ);
        std::string importSpritesString = importSpritesFile.ReadText();
        importSpritesFile.Close();
        //parse to json
        nlohmann::json importedSprites = nlohmann::json::parse(importSpritesString);
        //import all sprites
        for (size_t i = 0; i < importedSprites.size(); i++) {
            //get sprite info
            std::string spriteName = importedSprites[i]["name"];
            std::string spriteImageFile = importedSprites[i]["image"];
            int spriteFrames = importedSprites[i]["frames"];
            vec2 spriteOffset = vec2 {
                importedSprites[i]["offset"]["x"],
                importedSprites[i]["offset"]["y"]
            };
            //load sprite
            Image spriteImage;
            spriteImage.Load("sprites/" + spriteImageFile);
            //Texture spriteTexture = Texture::load(spriteImage);

            //ResourceManager<Sprite>::getSingleton()
            //    ->add(UniqueString(spriteName))
            //    ->load(spriteTexture, spriteFrames, spriteOffset);

            //Log::out(spriteName + " loaded");
        }
        */
    }
    


} // ASEngine