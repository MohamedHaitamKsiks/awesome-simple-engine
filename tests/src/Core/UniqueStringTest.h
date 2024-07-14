#ifndef __ASENGINE_UNIQUE_STRING_TEST_H
#define __ASENGINE_UNIQUE_STRING_TEST_H

#include "ASEngine.h"

using namespace ASEngine;

class UniqueStringTest: public UnitTest
{
public:
    ~UniqueStringTest() {}

private:
    // test data
    UniqueString m_SomeString; 
    
    void Describe() override;
};

#endif // __ASENGINE_UNIQUE_STRING_TEST_H
