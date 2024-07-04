#ifndef __ASENGINE_SYSTEM_TESTSYSTEM_H
#define __ASENGINE_SYSTEM_TESTSYSTEM_H

#include "ASEngine.h"

using namespace ASEngine;

// acts as entry point to run tests
class ASEngineTestSystem: public UnitTestSystem
{
    void Registry() override;
};

#endif // __ASENGINE_SYSTEM_TESTSYSTEM_H
