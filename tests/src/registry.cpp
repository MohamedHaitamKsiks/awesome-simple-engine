#include "registry.h"
#include "CoreTest.h"

void Registry()
{
    RUN_TESTS(
        CoreTest, 
        AnotherCoreTest
    );
}