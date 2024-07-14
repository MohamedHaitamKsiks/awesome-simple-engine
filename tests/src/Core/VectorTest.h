#ifndef __ASENGINE_VECTOR_TEST_H
#define __ASENGINE_VECTOR_TEST_H

#include "ASEngine.h"
using namespace ASEngine;

// generic vector test 
// has two implementations for Vector2 and Vector3
template<typename VectorType>
class VectorTest: public UnitTest
{
public:
    ~VectorTest() {}

private:
    void Describe() override;
    virtual void DescribeSpecializedTests() = 0;
};

// Vector2 specific tests
class Vector2Test: public VectorTest<Vector2>
{
    void DescribeSpecializedTests() override;
};


// Vector3 specific tests
class Vector3Test : public VectorTest<Vector3>
{
    void DescribeSpecializedTests() override;
};


#endif // __ASENGINE_VECTOR_TEST_H