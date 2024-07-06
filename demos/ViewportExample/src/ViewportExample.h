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

    void Init() override;
    void Update(float delta) override;
    void Terminate() override;

};



#endif // __ASENGINE_VIEWPORT_EXAMPLER_H