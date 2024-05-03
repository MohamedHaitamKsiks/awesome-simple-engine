#include "UniqueStringTest.h"

void UniqueStringTest::Describe()
{
    m_SomeString = UniqueString{"Hello World!"};
    
    Test(" It should verify equality between two same strings ", [&]()
    {
        UniqueString anotherString{"Hello World!"};
        ASENGINE_EXPECT(m_SomeString == anotherString); 
    });

    Test("It should verify inequality", [&]()
    {
        UniqueString anotherString{"ASEngine"};
        ASENGINE_EXPECT(m_SomeString != anotherString);
    });

    Test("It should return valid length", [&]()
    {
        ASENGINE_EXPECT(m_SomeString.GetLength() == 12);
    });
}