#ifndef __ASENGINE_CLASS_MANAGER_TEST_H
#define __ASENGINE_CLASS_MANAGER_TEST_H

#include "ASEngine.h"
using namespace ASEngine;

class ClassManagerTest: public UnitTest
{
public:
    ClassManagerTest() {}

private:
    void Describe() override;
};

#endif // __ASENGINE_CLASS_MANAGER_TEST_H