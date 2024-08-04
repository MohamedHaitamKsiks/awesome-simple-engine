#ifndef __INTERPOLATIONEXAMPLE_H
#define __INTERPOLATIONEXAMPLE_H

#include "ASEngine.h"
using namespace ASEngine;

class InterpolationExample: public ISystem
{
    float m_Time = 0.0f;
    float m_Speed = 0.5f;

    void Init() override;
    void Update(float delta) override;
    void OnRender2D(Renderer2D& renderer2D);
};

#endif // __INTERPOLATIONEXAMPLE_H
