#ifndef TESTMODULE_H
#define TESTMODULE_H

#include "ASEngine.h"

using namespace ASEngine;

class TestModule : public IModule
{
    void Registry() override;
};

#endif // TESTMODULE_H
