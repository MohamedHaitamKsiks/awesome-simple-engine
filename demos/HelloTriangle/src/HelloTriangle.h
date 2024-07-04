#ifndef __HELLO_TRIANGLE_H
#define __HELLO_TRIANGLE_H

#include "ASEngine.h"
using namespace ASEngine;

class HelloTriangle: public ISystem
{
private:
    ResourceRef<Buffer> m_VertexBuffer{};
    ResourceRef<Buffer> m_IndexBuffer{};
    ResourceRef<Shader> m_Shader{};

    void Init() override;
    void Update(float delta) override;
};

#endif // __HELLO_TRIANGLE_H