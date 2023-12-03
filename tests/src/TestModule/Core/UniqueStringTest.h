#pragma once
#include "ASEngine.h"

using namespace ASEngine;

UNIT_TEST(UniqueStringTest, 
{
    UniqueString someString("Hello World!");

    UNIT_TEST_CASE("It should verify equality between two same strings", {
        UniqueString anotherString("Hello World!");
        EXPECT(someString == anotherString);
    });

    UNIT_TEST_CASE("It should return valid length", {
        EXPECT(someString.GetLength() == 11);
    });
});
