#ifndef __ASENGINE_VIEWPORT_EXAMPLER_H
#define __ASENGINE_VIEWPORT_EXAMPLER_H

#include "ASEngine.h"
using namespace ASEngine;

class ViewportExample: public ISystem
{
public:
    ~ViewportExample() {}

private:
    ResourceRef<Viewport> m_Viewport{};
    //ResourceRef<Buffer> m_Viewport

    ResourceRef<Material> m_DefaultMaterial{};
    ResourceRef<Material> m_WavesMaterial{}; 

    // triangle 
    ResourceRef<Buffer> m_TriangleVertexBuffer{};
    ResourceRef<Buffer> m_TriangleIndexBuffer{};

    // rectangle
    ResourceRef<Buffer> m_RectangleVertexBuffer{};
    ResourceRef<Buffer> m_RectangleIndexBuffer{};

    float m_Timer = 0.0f;

    Vector2 m_MousePosition = Vector2::ZERO();
    Vector2 m_TargetMousePosition = Vector2::ZERO();
    Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
    bool m_MouseDown = false; 

    void Init() override;
    void Update(float delta) override;
    void OnInputEvent(const InputEvent& event) override;
    void Terminate() override;

};



#endif // __ASENGINE_VIEWPORT_EXAMPLER_H