#ifndef __ASENGINE_VIEWPORT_H
#define __ASENGINE_VIEWPORT_H

#include "Resource/ResourceRef.h"
#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"
#include "Resource/ResourceSerialization.h"



#include "Renderer/Texture/Texture.h"

namespace ASEngine
{
    // viewport context to render to
    class  Viewport: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(Viewport);
    ASENGINE_SERIALIZE_RESOURCE(Viewport);
    public:
        virtual ~Viewport() {}

        // create viewport with size and number of output textures
        void Create(uint32_t width, uint32_t height, size_t textureCount = 1);

        //  width
        inline uint32_t GetWidth() const
        {
            return m_Width;
        }

        // height
        inline uint32_t GetHeight() const
        {
            return m_Height;
        }

        // get size
        inline Vector2 GetSize() const
        {
            return Vector2(static_cast<float>(m_Width), static_cast<float>(m_Height));
        }

        // texture
        inline ResourceRef<Texture> GetTexture(size_t textureIndex) const
        {
            return m_Textures.at(textureIndex);
        }

        // get textures
        inline const std::vector<ResourceRef<Texture>>& GetTextures() const
        {
            return m_Textures;
        }

    protected:
        virtual void CreateImp(uint32_t width, uint32_t height, size_t textureCount) = 0;


    private:
        std::vector<ResourceRef<Texture>> m_Textures{};
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
    };
} // namespace ASEngine


#endif // __ASENGINE_VIEWPORT_H
