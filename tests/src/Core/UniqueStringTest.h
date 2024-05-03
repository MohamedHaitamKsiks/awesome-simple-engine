#ifndef ASENGINE_UNIQUE_STRING_TEST_H
#define ASENGINE_UNIQUE_STRING_TEST_H

#include "ASEngine.h"

using namespace ASEngine;

class UniqueStringTest: public UnitTest
{
private:
    // test data
    UniqueString m_SomeString; 
    
    void Describe() override;
};

#endif // ASENGINE_UNIQUE_STRING_TEST_H
