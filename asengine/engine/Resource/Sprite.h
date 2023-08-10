
#ifndef ASENGINE_SPRITE_H
#define ASENGINE_SPRITE_H

#include "Resource.h"
#include "Image.h"
#include "Shader.h"
#include "Material.h"
#include "ResourceManager.h"

#include "engine/FileSystem/File.h"
#include "engine/Renderer/Texture.h"
#include "engine/Math/vec2.h"
#include "engine/Log/Log.h"
#include "engine/Serialization/Serializer.h"

namespace ASEngine {

    using SpriteID = ResourceID;

    class Sprite : public Resource
    {
    public:
        //load
        bool Load(Texture texture, int frames, const vec2& offset );
    
        // get default material
        inline ResourceID GetDefaultMaterial() const { return m_DefaultMaterial; }

        // get sprite texture
        inline Texture GetTexture() const { return m_Texture; };

        // get frame number
        inline int GetFrames() const { return m_Frames; };

        // get width
        inline int GetWidth() const { return m_Width; };

        // get height
        inline int GetHeight() const { return m_Height; }
        
        // get sprite offset
        inline vec2 GetOffset() const { return m_Offset; };

    private:
        // data
        Texture m_Texture;
        ResourceID m_DefaultMaterial;
        int m_Frames = 0;
        int m_Width = -1;
        int m_Height = -1;
        vec2 m_Offset = vec2{0.0f, 0.0f};
    };

} // ASEnginge

#endif //ASENGINE_SPRITE_H
