#ifndef __ASENGINE_RENDERER_2D_H
#define __ASENGINE_RENDERER_2D_H

#include <set>

#include "Core/Signal/Signal.h"

#include "ECS/System.h"

#include "2D/Layer2D/Layer2D.h"
#include "2D/Quad2D/Quad2D.h"
#include "2D/Font/Font.h"

#include "Renderer/Material/Material.h"
#include "Renderer/Shader/Shader.h"

#include "Core/Singleton/Singleton.h"


#include "Renderer/Texture/Texture.h"

namespace ASEngine
{
    class  Renderer2D: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(Renderer2D);
    public:
        // renderer settings
        struct Settings
        {
            std::vector<UniqueString> Layers;
            ResourceRef<Material> DefaultMaterial;
        };

        ~Renderer2D() {}

        // get layer
        inline Layer2D& GetLayer(UniqueString layerName)
        {
            return m_Layers2D[layerName];
        }

        // get layers
        inline const std::vector<UniqueString>& GetLayerNames() const
        {
            return m_LayerNames;
        }

        // get default shader
        inline const ResourceRef<Shader>& GetDefaultShader() const
        {
            return m_DefaultShader;
        }

        // get default material
        inline const ResourceRef<Material>& GetDefaultMaterial() const
        {
            return m_DefaultMaterial;
        }

        // fill rectangle default material
        inline const ResourceRef<Material>& GetFillRectangleDefaultMaterial() const
        {
            return m_FillRectangleDefaulMaterial;
        }

        // fill rectangle default material
        inline const ResourceRef<Texture>& GetFillRectangleTexture() const
        {
            return m_FillRectangleTexture;
        }


        // get on renderer 2d signal
        inline Signal<Renderer2D&>& GetOnRender2D()
        {
            return m_OnRender2D;
        }

    private:
        std::vector<UniqueString> m_LayerNames = {};
        std::unordered_map<UniqueString, Layer2D> m_Layers2D = {};

        ResourceRef<Shader> m_DefaultShader = ResourceRef<Shader>::NONE();
        ResourceRef<Material> m_DefaultMaterial = ResourceRef<Material>::NONE();

        // fill rectangle material
        ResourceRef<Material> m_FillRectangleDefaulMaterial = ResourceRef<Material>::NONE();
        ResourceRef<Texture> m_FillRectangleTexture = ResourceRef<Texture>::NONE(); // one white pixel

        Signal<Renderer2D&> m_OnRender2D;

        void Init() override;
        void OnRender() override;
    };
} // namespace ASEngine


#endif // __ASENGINE_RENDERER_2D_H
