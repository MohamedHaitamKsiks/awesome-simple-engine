#ifndef __EXAMPLE_2D
#define __EXAMPLE_2D

#include "2D/Renderer2D/Renderer2D.h"
#include "ASEngine.h"
#include "Core/Signal/Signal.h"
using namespace ASEngine;

class Example2D: public ISystem
{
public:
    Example2D() {}
    ~Example2D() {}

private:
    ResourceRef<Sprite> m_Sprite{};
    ResourceRef<Font> m_Font{};

    ResourceRef<Material> m_ViewportMaterial{};
    ResourceRef<Viewport> m_Viewport{};

    float m_Time = 0.0f;

    float m_FPS = 0.0f;
    uint32_t m_FrameCount = 0;

    SignalConnectionID m_OnRender2DConnectionID;

    void Init() override;
    void Update(float delta) override;
    void OnRender2D(Renderer2D& renderer2D);
    void Terminate() override;
};

#endif // __EXAMPLE_2D
