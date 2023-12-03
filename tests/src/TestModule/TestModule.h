#ifndef TESTMODULE_H
#define TESTMODULE_H

#include "ASEngine.h"
#include "TestSystem.h"

using namespace ASEngine;

class TestModule : public IModule
{
    // register components
    void RegisterComponents();

    // register systems
    void RegisterSystems();

    // init resources managers
    void InitResourceManagers();

    // terminate resource managers
    void TerminateResourceManagers();
};

#endif // TESTMODULE_H
