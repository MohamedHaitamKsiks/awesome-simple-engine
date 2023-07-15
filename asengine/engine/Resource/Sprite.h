
#ifndef ASENGINE_SPRITE_H
#define ASENGINE_SPRITE_H

#include "Resource.h"
#include "ResourceManager.h"
#include "Image.h"

#include "engine/FileSystem/File.h"
#include "engine/Renderer/Texture.h"
#include "engine/Math/vec2.h"
#include "engine/Thirdparty/json.hpp"
#include "engine/Log/Log.h"

namespace ASEngine {

    class Sprite : public Resource{
    public:
        //data
        Texture texture = Texture::defaultTexture;
        int frames = 0;
        int width = -1;
        int height = -1;
        vec2 offset = vec2{0.0f, 0.0f};

        //load
        bool load(Texture _texture, int _frames, vec2 _offset );
    
        static void importAll();
    };

} // ASEnginge

#endif //ASENGINE_SPRITE_H
