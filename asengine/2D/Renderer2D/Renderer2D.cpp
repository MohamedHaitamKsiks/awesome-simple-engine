#include "Renderer2D.h"

#include "Core/FileSystem/File.h"
#include "Core/Error/Assertion.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Serialization/SerializeStruct.h"

#include "2D/Transform2D/Transform2D.h"
#include "2D/Camera2D/Camera2D.h"

#include "ECS/EntityQuery.h"

#include "Display/Display.h"

#include "Renderer/Color.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture/Texture.h"

namespace ASEngine
{
    ASENGINE_SERIALIZE_STRUCT(Renderer2D::Settings, Layers, DefaultMaterial);

    void Renderer2D::Init()
    {
        // load renderer 2d config
        File settingsFile;
        ASENGINE_ASSERT(settingsFile.Open("renderer2d.settings.json", FileOpenMode::READ), "Cound't open renderer2d.settings.json");

        Json settingsJson = Json::parse(settingsFile.ReadText());
        Renderer2D::Settings settings;

        Serializer::Deserialize(settingsJson, settings);

        settingsFile.Close();

        // create layers
        for (auto layerName: settings.Layers)
        {
            m_LayerNames.push_back(layerName);

            auto& layer2D = m_Layers2D[layerName];
            layer2D.Init();
        }

        // get default shader/materail
        m_DefaultMaterial = settings.DefaultMaterial;
        m_DefaultShader = m_DefaultMaterial->GetShader();

        // create fill rectangle texture
        Image fillRectangleImage;
        fillRectangleImage.Create(1, 1);
        fillRectangleImage.SetPixelAt(0, 0, Color::WHITE());

        m_FillRectangleTexture = Texture::GetResourceClass().New();
        m_FillRectangleTexture->Create(fillRectangleImage, TextureFilter::NEAREST, TextureRepeatMode::REPEAT);

        // create fill rectangle material
        m_FillRectangleDefaulMaterial = m_DefaultMaterial->Clone();
        m_FillRectangleDefaulMaterial->SetShaderParam("Texture", m_FillRectangleTexture);
    }

    void Renderer2D::Update(float delta)
    {
        // call on render signal
        m_OnRender2D.Emit(*this);

        // render to gpu
        auto& renderer = Renderer::GetInstance();

        // render for each camera
        EntityQuery<Transform2D, Camera2D> query{};

        // for each is enough since we would have a large number of cameras
        query.ForEach([this, &renderer](Transform2D& transform2D, Camera2D& camera2D)
        {
            // get matrices
            Matrix3x3 cameraTransform = transform2D.GetGlobalTransform();

            uint32_t viewportWidth, viewportHeight;
            if (camera2D.Target == ResourceRef<Viewport>::NONE())
            {
                viewportWidth = Display::GetInstance().GetWindowWidth();
                viewportHeight = Display::GetInstance().GetWindowHeight();
            }
            else
            {
                viewportWidth = camera2D.Target->GetWidth();
                viewportHeight = camera2D.Target->GetHeight();
            }

            Matrix3x3 viewportTransform = Matrix3x3::ViewportProjection(viewportWidth, viewportHeight);

            renderer.Begin(camera2D.Target);
            renderer.Clear();

            for (auto& layerName: m_LayerNames)
            {
                if (camera2D.Layers.find(layerName) == camera2D.Layers.end())
                    continue;

                m_Layers2D[layerName].Draw(cameraTransform, viewportTransform, camera2D.PixelSnapping);
            }

            renderer.End();
        });
    }

}; // ASEngine
