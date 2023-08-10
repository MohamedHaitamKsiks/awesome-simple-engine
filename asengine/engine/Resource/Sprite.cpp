#include "Sprite.h"

namespace ASEngine 
{

    bool Sprite::Load(Texture texture, int frames, const vec2& offset) 
    {
        if (frames <= 0) 
            return false;

        m_Texture = texture;
        // get default shader
        ResourceID shaderID = ResourceManager<Shader>::GetResourceId(UniqueString("shaders/default.glsl"));
        // set default material
        m_DefaultMaterial = ResourceManager<Material>::Add();
        auto& material = ResourceManager<Material>::Get(m_DefaultMaterial);
        material.Create(shaderID);
        material.SetShaderParam(UniqueString("u_Texture"), m_Texture);
        
        m_Width = texture.GetWidth() / frames;
        m_Height = texture.GetHeight();
        m_Frames = frames;
        m_Offset = offset;
        return true;
    }

    // sprite serialization
    template <>
    Json Serializer<Sprite>::Serialize(const Sprite &value)
    {
        Json spriteObject = Json({});
        return spriteObject;
    }
    template <>
    void Serializer<Sprite>::Deserialize(const Json &object, Sprite &dest)
    {
        assert(object.is_object());

        // decerialize fields
        std::string imagePath;
        Serializer<std::string>::Deserialize(object["ImagePath"], imagePath);

        vec2 offset;
        Serializer<vec2>::Deserialize(object["Offset"], offset);

        int frames;
        Serializer<int>::Deserialize(object["Frames"], frames);

        // load image
        Image img;
        img.Load(imagePath);

        // laod texture
        Texture spriteTexture = Texture::LoadFromImage(img);

        // load sprite
        dest.Load(spriteTexture, frames, offset);
    }

} // ASEngine