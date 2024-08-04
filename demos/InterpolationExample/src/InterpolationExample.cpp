#include "InterpolationExample.h"
#include "Core/Math/Vector2.h"

void InterpolationExample::Init()
{
    Renderer2D::GetInstance().GetOnRender2D().Connect([this](Renderer2D& renderer2D){
        OnRender2D(renderer2D);
    });
}

void InterpolationExample::Update(float delta)
{
    m_Time += delta * Math::Abs(m_Speed);
    if (m_Time > 1.00f)
    {
        m_Speed *= -1.0f;
        m_Time = 0.0f;
    }
}


void InterpolationExample::OnRender2D(Renderer2D& renderer2D)
{
    auto& defaultLayer = renderer2D.GetLayer("Default");
    Vector2 size = Vector2::ONE() * 64.0f;

    Vector2 a = Vector2(120.0f, 68.0f);
    Vector2 b = Vector2(static_cast<float>(Display::GetInstance().GetWindowWidth()) - size.x - a.x, a.y);
    float t = m_Time;

    if (m_Speed < 0.0f)
    {
        Vector2 c = a;
        a = b;
        b = c;
    }

    auto incrementAB = [&a, &b] ()
    {
        a.y += 128.0f;
        b.y += 128.0f;
    };

    defaultLayer.DrawFillRectangle(size, Matrix3x3::Translate(Interpolation::Linear(a, b, t)), Color::WHITE());
    incrementAB();

    defaultLayer.DrawFillRectangle(size, Matrix3x3::Translate(Interpolation::QuadEaseInOut(a, b, t)), Color::WHITE());
    incrementAB();

    defaultLayer.DrawFillRectangle(size, Matrix3x3::Translate(Interpolation::ExpEaseInOut(a, b, t)), Color::WHITE());
    incrementAB();

    defaultLayer.DrawFillRectangle(size, Matrix3x3::Translate(Interpolation::BackEaseInOut(a, b, t)), Color::WHITE());
    incrementAB();

    defaultLayer.DrawFillRectangle(size, Matrix3x3::Translate(Interpolation::ElasticEaseInOut(a, b, t)), Color::WHITE());
    incrementAB();
}
