#ifndef __ASENGINE_VIEWPORT_H
#define __ASENGINE_VIEWPORT_H

#include "Resource/ResourceRef.h"
#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"
#include "Resource/ResourceSerialization.h"



#include "Renderer/Texture/Texture.h"

namespace ASEngine
{
    struct ViewportInfo
    {
        uint32_t Width = 0;
        uint32_t Height = 0;
        size_t TextureCount = 1;
        uint32_t Samples = 1;
    };

    // viewport context to render to
    class  Viewport: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(Viewport);
    ASENGINE_SERIALIZE_RESOURCE(Viewport);
    public:
        virtual ~Viewport() {}

        // create viewport with size and number of output textures
        void Create(uint32_t width, uint32_t height, size_t textureCount = 1);

        // create viewport using viewport info struct
        void Create(const ViewportInfo& info);

        //  width
        inline uint32_t GetWidth() const
        {
            return m_Info.Width;
        }

        // height
        inline uint32_t GetHeight() const
        {
            return m_Info.Height;
        }

        // get size
        inline Vector2 GetSize() const
        {
            return Vector2(static_cast<float>(GetWidth()), static_cast<float>(GetHeight()));
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

        // is multisampling enabled
        inline bool IsMultisampled() const
        {
            return m_Info.Samples >= 1;
        }

        inline uint32_t GetSamples() const
        {
            return m_Info.Samples;
        }

    protected:
        virtual void CreateImp(const ViewportInfo& info) = 0;

    private:
        std::vector<ResourceRef<Texture>> m_Textures{};
        ViewportInfo m_Info{};
    };
} // namespace ASEngine


#endif // __ASENGINE_VIEWPORT_H
