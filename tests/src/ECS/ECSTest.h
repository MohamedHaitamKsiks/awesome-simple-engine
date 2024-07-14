#ifndef __ASENGINE_ECS_TEST_H
#define __ASENGINE_ECS_TEST_H

#include "ASEngine.h"
using namespace ASEngine;

class ECSTest: public UnitTest
{
public:
    ~ECSTest() {}

private:
    void Describe() override;
};

#endif // __ASENGINE_ECS_TEST_H