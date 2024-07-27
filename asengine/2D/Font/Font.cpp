#include "Font.h"
#include "Core/Math/Vector2.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Texture/Texture.h"

#include <cstdint>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Core/Memory/ByteBuffer.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Error/Assertion.h"
#include "Core/FileSystem/File.h"

#include "Resource/ResourceRefSerialization.h"

#include "2D/Renderer2D/Renderer2D.h"

// font consts
#define _ASENGINE_FONT_SPRITE_HFRAMES 16
#define _ASENGINE_FONT_SPRITE_VFRAMES 8

ASENGINE_SERIALIZE_RESOURCE_REF(Font);
namespace ASEngine
{
    template <>
    void Serializer::Deserialize(const Json &object, Font &dest)
    {
        std::string fontPath = "";
        Serializer::Deserialize(object.at("FontPath"), fontPath);

        uint32_t size = 0;
        Serializer::Deserialize(object.at("Size"), size);

        uint32_t characterSeparation = 0;
        Serializer::Deserialize(object.at("CharacterSeparation"), characterSeparation);

        uint32_t lineSeparation = 0;
        Serializer::Deserialize(object.at("LineSeparation"), lineSeparation);

        uint32_t spaceSize = 0;
        Serializer::Deserialize(object.at("SpaceSize"), spaceSize);

        ResourceRef<Material> material = Renderer2D::GetInstance().GetDefaultMaterial();
        if (object.find("Material") != object.end())
        {
            Serializer::Deserialize(object.at("Material"), material);
        }

        // create font
        dest.Create(fontPath, size, characterSeparation, lineSeparation, spaceSize, material);
    }

    template <>
    Json Serializer::Serialize(const Font &dest)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Font);

    void Font::Create(const std::string& fontPath, uint32_t size, uint32_t characterSeparation, uint32_t lineSeparation, uint32_t spaceSize)
    {
        Create(fontPath, size, characterSeparation, lineSeparation, spaceSize, Renderer2D::GetInstance().GetDefaultMaterial());
    }

    void Font::Create(const std::string& fontPath, uint32_t size, uint32_t characterSeparation, uint32_t lineSeparation, uint32_t spaceSize, const ResourceRef<Material> material)
    {
        // init ft library
        FT_Library ftLib;
        ASENGINE_ASSERT(FT_Init_FreeType(&ftLib) == 0, "Couldn't load FreeType Library");

        // load .fft font
        File fontFile;
        fontFile.Open(fontPath, FileOpenMode::READ);

        ByteBuffer fontBuffer;
        fontFile.Read(fontBuffer);
        fontFile.Close();

        // create face
        FT_Face face;
        ASENGINE_ASSERT(FT_New_Memory_Face(ftLib, reinterpret_cast<FT_Byte*>(fontBuffer.GetData()), fontBuffer.GetSize(), 0, &face) == 0, "Failed to create font face!");

        FT_Set_Pixel_Sizes(face, 0, size);
        //FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

        // font image
        Image fontImage;
        fontImage.Create(size * _ASENGINE_FONT_SPRITE_HFRAMES, size * _ASENGINE_FONT_SPRITE_VFRAMES);

        // init font to big black transparent image
        for (uint32_t y = 0; y < static_cast<uint32_t>(fontImage.GetHeight()); y++)
        {
            for (uint32_t x = 0; x <  static_cast<uint32_t>(fontImage.GetWidth()); x++)
            {
                fontImage.SetPixelAt(x, y, 0, 0, 0, 0);
            }
        }

        // add font characters to the image
        for (uint32_t i = 0; i < _ASENGINE_FONT_CHARACTER_NUMBER; i++)
        {
            // load font char
            ASENGINE_ASSERT(FT_Load_Char(face, char(i), FT_LOAD_RENDER) == 0, "Failed to load Glyph");

            // bitmap
            uint32_t bitmapWidth = face->glyph->bitmap.width;
            uint32_t bitmapHeight = face->glyph->bitmap.rows;
            size_t bitmapBufferSize = bitmapWidth * bitmapHeight;

            // image frame
            uint32_t hframe = i % _ASENGINE_FONT_SPRITE_HFRAMES;
            uint32_t vframe = i / _ASENGINE_FONT_SPRITE_HFRAMES;

            // get image offset
            uint32_t imageOffsetX = hframe * size;
            uint32_t imageOffsetY = vframe * size;

            // add character to image
            for (uint32_t j = 0; j < bitmapBufferSize; j++)
            {
                //sub image coordinates
                uint32_t subImageCoordX = j % bitmapWidth;
                uint32_t subImageCoordY = j / bitmapWidth;

                //image coord
                uint32_t imageCoordX = subImageCoordX + imageOffsetX;
                uint32_t imageCoordY = subImageCoordY + imageOffsetY;

                //pixel
                uint8_t pixelAlphaValue = face->glyph->bitmap.buffer[j];
                fontImage.SetPixelAt(imageCoordX, imageCoordY, 255, 255, 255, pixelAlphaValue);
            }

            // character info
            auto& characterInfo = m_CharacterInfos[i];
            characterInfo.Width = face->glyph->bitmap.width;
            characterInfo.BearingY = face->glyph->bitmap_top;
            characterInfo.HFrame = hframe;
            characterInfo.VFrame = vframe;
        }

        // create texture
        ResourceRef<Texture> fontTexture = Texture::GetResourceClass().New();
        fontTexture->Create(fontImage, TextureFilter::NEAREST, TextureRepeatMode::CLAMP);

        // create font sprite
        m_Sprite = Sprite::GetResourceClass().New();
        m_Sprite->Create(fontTexture, _ASENGINE_FONT_SPRITE_HFRAMES, _ASENGINE_FONT_SPRITE_VFRAMES, Vector2::ZERO(), material);

        // save font params
        m_Size = size;
        m_CharacterSeparation = characterSeparation;
        m_LineSeparation = lineSeparation;
        m_SpaceSize = spaceSize;
    }
} // namespace ASEngine
