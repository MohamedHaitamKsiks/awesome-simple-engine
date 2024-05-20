#ifndef ASENGINE_SHADER_SOURCE_TEST_H
#define ASENGINE_SHADER_SOURCE_TEST_H

#include "ASEngine.h"

using namespace ASEngine;

class ShaderSourceTest: public UnitTest
{
public:
    void Describe() override;

private:
    ResourceRef<ShaderSource> m_Source;
};

#endif // ASENGINE_SHADER_SOURCE_TEST_H