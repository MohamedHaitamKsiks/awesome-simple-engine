#include "PoolAllocatorTest.h"
#include <chrono>

// define some random values to test if constructor is called
#define POOLALLOCATOR_DEFAULT_VALUE 456512
#define POOLALLOCATOR_CONTRUCTOR_VALUE 65452111
#define POOLALLOCATOR_DESTRUCTOR_VALUE 12125

int PoolAllocatorTest::s_TestValue = 0;

PoolAllocatorTest::TestClass::TestClass()
{
    s_TestValue = POOLALLOCATOR_CONTRUCTOR_VALUE;
}

PoolAllocatorTest::TestClass::~TestClass()
{
    s_TestValue = POOLALLOCATOR_DESTRUCTOR_VALUE;
}


void PoolAllocatorTest::Describe()
{

    Test("it should have a capacity", [&]()
    {
        ASENGINE_EXPECT(m_Pool.GetCapacity() == POOL_ALLOCATOR_DEFAULT_PAGE_SIZE * 2);
    });

    Test("it should call constructor/destructor", [&]()
    {
        s_TestValue = POOLALLOCATOR_DEFAULT_VALUE;
        
        ChunkID testID = m_Pool.Allocate();
        ASENGINE_EXPECT(s_TestValue == POOLALLOCATOR_CONTRUCTOR_VALUE);
        
        m_Pool.Free(testID);
        ASENGINE_EXPECT(s_TestValue == POOLALLOCATOR_DESTRUCTOR_VALUE);
    });

    Test("is should be faster than heap for 1000000 allocations", [&]()
    {
        constexpr int testCount = 1000000;

        // get delta time of heap
        auto pastTime = std::chrono::high_resolution_clock::now();
        std::vector<TestClass*> tests{};

        for (int i = 0; i < testCount; i++)
            tests.push_back(new TestClass());

        auto currentTime = std::chrono::high_resolution_clock::now();
        float heapDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count();
        Debug::Log("Heap Delta Time for ", heapDeltaTime / 1000.0f, "ms");
        
        // clean up
        for (auto* p: tests)
            delete p;
        
        // delta time of pool allocator
        pastTime = std::chrono::high_resolution_clock::now();
        std::vector<ChunkID> testsIDs{};

        for (int i = 0; i < testCount; i++)
            testsIDs.push_back(m_Pool.Allocate());

        currentTime = std::chrono::high_resolution_clock::now();
        float poolAllocatorDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count();
        Debug::Log("PoolAllocator Delta Time for ", poolAllocatorDeltaTime / 1000.0f, "ms");
        
        // cleanup
        for (auto chunkID: testsIDs)
            m_Pool.Free(chunkID);

        ASENGINE_EXPECT(poolAllocatorDeltaTime < heapDeltaTime);
    });
}
