#ifndef __ASENGINE_FONT_H
#define __ASENGINE_FONT_H

#include "Core/Math/Vector2.h"
#include "Renderer/Texture/Texture.h"
#include "Renderer/Material/Material.h"

#include "Resource/ResourceRef.h"
#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"
#include "Resource/ResourceSerialization.h"

#include "2D/Sprite/Sprite.h"

#include "API/API.h"

#define _ASENGINE_FONT_CHARACTER_NUMBER 128

namespace ASEngine
{
    // font
    class ASENGINE_API Font: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(Font);
    ASENGINE_SERIALIZE_RESOURCE(Font);
    public:
        // character rendering informations
        struct CharacterInfo
        {
            uint32_t Width = 0;
            uint32_t BearingY = 0;
            uint32_t HFrame = 0;
            uint32_t VFrame = 0;
        };

        ~Font() {}

        // create font from .ttf file
        void Create(const std::string& fontPath, uint32_t size, uint32_t characterSeparation, uint32_t lineSeparation, uint32_t spaceSize);

        // create font from .ttf file with material
        void Create(const std::string& fontPath, uint32_t size, uint32_t characterSeparation, uint32_t lineSeparation, uint32_t spaceSize, const ResourceRef<Material> material);

        // get character info
        inline const CharacterInfo& GetCharacterInfo(char character) const
        {
            return m_CharacterInfos[static_cast<size_t>(character)];
        }

        // get sprite
        inline const ResourceRef<Sprite>& GetSprite() const
        {
            return m_Sprite;
        }

        // get size
        inline uint32_t GetSize() const
        {
            return m_Size;
        }

        // get character sepration px
        inline uint32_t GetCharacterSeparation() const
        {
            return m_CharacterSeparation;
        }

        // get line separation in px
        inline uint32_t GetLineSeparation() const
        {
            return m_LineSeparation;
        }

        // get space size
        inline uint32_t GetSpaceSize() const
        {
            return m_SpaceSize;
        }

        // get extremities of string if rendered wiht his font (to be able to align it)
        Vector2 GetExtremities(const std::string& text) const;

    private:
        ResourceRef<Sprite> m_Sprite = ResourceRef<Sprite>::NONE();
        CharacterInfo m_CharacterInfos[_ASENGINE_FONT_CHARACTER_NUMBER];

        uint32_t m_Size = 0;
        uint32_t m_CharacterSeparation = 0;
        uint32_t m_LineSeparation = 0;
        uint32_t m_SpaceSize = 0;
    };
} // ASEngine

#endif // __ASENGINE_FONT_H
