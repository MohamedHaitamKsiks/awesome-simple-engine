#include "Example2D.h"
#include "BouncingFox/BouncingFox.h"
#include "Core/Math/Matrix3x3.h"
#include "Core/Math/Vector2.h"
#include <sstream>

void Example2D::Init()
{
    m_Sprite = Sprite::GetResourceClass().Load("sprites/spr_run.sprite.json");
    m_Font = Font::GetResourceClass().Load("fonts/kongtext_32.font.json");

    m_ViewportMaterial = Renderer2D::GetInstance().GetDefaultMaterial()->Clone();

    m_Viewport = Viewport::GetResourceClass().Load("viewports/pixel.viewport.json");
    m_ViewportMaterial->SetShaderParam("Texture", m_Viewport->GetTexture(0));

    // add on render
    m_OnRender2DConnectionID = Renderer2D::GetInstance().GetOnRender2D().Connect([this](Renderer2D& renderer2D)
    {
        OnRender2D(renderer2D);
    });

}

void Example2D::Terminate()
{

}

void Example2D::Update(float delta)
{
    m_Time += delta;

    // move foxes
    EntityQuery<Transform2D, BouncingFox> query{};
    query.ForEachCollection([this, &delta](ComponentCollection<Transform2D>& transforms, ComponentCollection<BouncingFox>& foxes, size_t count)
    {
        for (ComponentIndex i = 0; i < count; i++)
        {
            auto& transform = transforms[i];
            auto& fox = foxes[i];

            transform.Position += fox.Velocity * delta;
            if (transform.Position.x < 10.0f)
            {
                transform.Position.x = 10.1f;
                fox.Velocity.x *= -1.0f;
            }
            if (transform.Position.x > 300.1f)
            {
                transform.Position.x = 300.0f;
                fox.Velocity.x *= -1.0f;
            }
            if (transform.Position.y < 10.0f)
            {
                transform.Position.y = 10.1f;
                fox.Velocity.y *= -1.0f;
            }
            if (transform.Position.y > 150.1f)
            {
                transform.Position.y = 150.0f;
                fox.Velocity.y *= -1.0f;
            }
        }
    });

    // set title to fps
    if (delta > 0.0)
    {
        m_FPS = (static_cast<float>(m_FrameCount) *  m_FPS + 1.0f / delta) / static_cast<float>(m_FrameCount + 1);
        m_FrameCount++;

        if (m_FrameCount > 10000)
            m_FrameCount = 0;
    }
}

void Example2D::OnRender2D(Renderer2D& renderer2D)
{

    int frame = static_cast<int>(m_Time * 8.0f) % 6;

    // render to defualt layer
    auto& defaultLayer = renderer2D.GetLayer("Default");

    // draw background
    defaultLayer.DrawFillRectangle(Vector2(300.0f, 160.0f), Matrix3x3::Translate(Vector2::ONE() * 10.0f), Color(0.2f, 0.2f, 0.3f, 1.0f));

    // draw sprites for boucing fox
    EntityQuery<Transform2D, BouncingFox> query{};
    query.ForEachCollection([this, &defaultLayer, &frame](ComponentCollection<Transform2D>& transforms, ComponentCollection<BouncingFox>& foxes, size_t count)
    {
        for (ComponentIndex i = 0; i < count; i++)
        {
            Matrix3x3 transform = transforms[i].GetGlobalTransform();

            //defaultLayer.DrawSprite(m_Sprite, Matrix3x3::Translate(Vector2::DOWN() * 2.0f) * transform , frame, 0, Color::BLACK());
            defaultLayer.DrawSprite(m_Sprite, transform, (frame + i) % 6, 0, Color::WHITE());
        }
    });

    // render to pixel viewport
    auto& pixelViewportLayer = renderer2D.GetLayer("PixelViewport");

    // render viewport
    float windowWidth = static_cast<float>(Display::GetInstance().GetWindowWidth());
    float windowHeight = static_cast<float>(Display::GetInstance().GetWindowHeight());

    Quad2D& viewportQuad2D = pixelViewportLayer.DrawQuad2D(m_ViewportMaterial);
    viewportQuad2D.Create(Vector2(windowWidth, windowHeight), Matrix3x3::IDENTITY(), Color::WHITE(), Vector2(0.0f, 1.0f), Vector2(1.0f, 0.0f));

    // draw fps
    std::stringstream ss;
    ss << static_cast<uint32_t>(m_FPS) << " FPS";
    std::string fpsText = ss.str();

    // add outline
    float angle = Math::PI / 48.0f;
    Vector2 position = Vector2(32.0f, 48.0f);

    pixelViewportLayer.DrawText(m_Font, fpsText, Matrix3x3::Translate(position + Vector2::DOWN() * 4.0f) * Matrix3x3::Rotation(angle), Color::BLACK());
    pixelViewportLayer.DrawText(m_Font, fpsText, Matrix3x3::Translate(position + Vector2::UP() * 4.0f) * Matrix3x3::Rotation(angle), Color::BLACK());
    pixelViewportLayer.DrawText(m_Font, fpsText, Matrix3x3::Translate(position + Vector2::RIGHT() * 4.0f) * Matrix3x3::Rotation(angle), Color::BLACK());
    pixelViewportLayer.DrawText(m_Font, fpsText, Matrix3x3::Translate(position + Vector2::LEFT() * 4.0f) * Matrix3x3::Rotation(angle), Color::BLACK());

    // draw text
    pixelViewportLayer.DrawText(m_Font, fpsText, Matrix3x3::Translate(position) * Matrix3x3::Rotation(angle), Color::WHITE());
}
