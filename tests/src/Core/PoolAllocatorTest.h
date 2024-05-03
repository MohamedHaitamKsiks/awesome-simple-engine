#ifndef ASENGINE_POOLALLOCATOR_TEST_H
#define ASENGINE_POOLALLOCATOR_TEST_H

#include "ASEngine.h"
using namespace ASEngine;



class PoolAllocatorTest: public UnitTest
{
private:
    // test class
    class TestClass
    {
    public:
        TestClass();
        ~TestClass();
    private:
        uint8_t m_Data[10000];
    };

    // it is going to be editted by class constructor and destructor
    static int s_TestValue;
    PoolAllocator<TestClass> m_Pool{};

    void Describe() override;
};

#endif // ASENGINE_POOLALLOCATOR_TEST_H