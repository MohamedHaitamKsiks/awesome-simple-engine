#pragma once
#include "ASEngine.h"

using namespace ASEngine;

ASENGINE_UNIT_TEST(UniqueStringTest, 
{
    UniqueString someString{"Hello World!"};

    ASENGINE_UNIT_TEST_CASE("It should verify equality between two same strings", 
    {
        UniqueString anotherString{"Hello World!"};
        ASENGINE_UNIT_TEST_EXPECT(someString == anotherString);
    });

    ASENGINE_UNIT_TEST_CASE("It should verify inequality",
    {
        UniqueString anotherString{"ASEngine"};
        ASENGINE_UNIT_TEST_EXPECT(someString != anotherString);
    });

    ASENGINE_UNIT_TEST_CASE("It should return valid length", 
    {
        ASENGINE_UNIT_TEST_EXPECT(someString.GetLength() == 12);
    });
});
