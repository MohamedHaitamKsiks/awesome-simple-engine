#ifndef __ASENGINE_MATRIX_TEST_H
#define __ASENGINE_MATRIX_TEST_H

#include "ASEngine.h"
using namespace ASEngine;

// generic matrix test
// has two implementations for Matrix3x3 and Matrix4x4
template <typename MatrixType>
class MatrixTest : public UnitTest
{
public:
    ~MatrixTest() {}

private:
    void Describe() override;
    virtual void DescribeSpecializedTests() = 0;
};

// Matrix3x3 specific tests
class Matrix3x3Test : public MatrixTest<Matrix3x3>
{
    void DescribeSpecializedTests() override;
};

// Matrix3 specific tests
class Matrix4x4Test : public MatrixTest<Matrix4x4>
{
    void DescribeSpecializedTests() override;
};

#endif // __ASENGINE_MATRIX_TEST_H

