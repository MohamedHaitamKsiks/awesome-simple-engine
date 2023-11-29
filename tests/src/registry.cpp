#include "registry.h"

void Registry()
{
    UnitTest test{};
    test.Test("Test Case 1", [&test]() 
    {
        test.Expect(1);
    });

    RUN_TESTS(test);
}