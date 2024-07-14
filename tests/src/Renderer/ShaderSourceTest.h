#ifndef __ASENGINE_SHADER_SOURCE_TEST_H
#define __ASENGINE_SHADER_SOURCE_TEST_H

#include "ASEngine.h"

using namespace ASEngine;

class ShaderSourceTest: public UnitTest
{
public:
    ~ShaderSourceTest();
    void Describe() override;

private:
    ResourceRef<ShaderSource> m_Source;
};

#endif // __ASENGINE_SHADER_SOURCE_TEST_H