#pragma once
#include "ASEngine.h"

using namespace ASEngine;

UNIT_TEST(CoreTest, 
{
    UniqueString someString("Hello World!");

    UNIT_TEST_CASE("Test Unique String equality", {
        UniqueString anotherString("Hello World!");
        EXPECT(someString == anotherString);
    });

    UNIT_TEST_CASE("Test Unique String Length", {
        EXPECT(someString.GetLength() == 12);
    });
});

UNIT_TEST(AnotherCoreTest,
{
    UniqueString someString("Hello World!");

    UNIT_TEST_CASE("Test Unique String equality2", {
        UniqueString anotherString("Hello World!");
        EXPECT(someString == anotherString);
    });

    UNIT_TEST_CASE("Test Unique String Length2", {
        EXPECT(someString.GetLength() == 11);
    });
});