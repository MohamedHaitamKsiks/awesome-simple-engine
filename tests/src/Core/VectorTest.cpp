#include "VectorTest.h"
#define TEST_PRECISION 0.00001f
#define TEST_VECTOR_EQL(v1, v2) (v1 - v2).Length() < TEST_PRECISION

template<typename VectorType>
void VectorTest<VectorType>::Describe()
{

    // general tests
    Test("Is has Length ", []()
    {
        VectorType v = VectorType::RIGHT();
        ASENGINE_EXPECT(Math::Abs(v.Length() - 1.0f) < TEST_PRECISION);
    });

    Test("It can be added to another Vector", []()
    {
        VectorType v1 = VectorType::RIGHT();
        VectorType v2 = VectorType::UP();
        v1 = v1 + v2;

        VectorType result{1.0f, -1.0f};
        ASENGINE_EXPECT(TEST_VECTOR_EQL(v1, result));
    });

    Test("It can be scaled by float", []()
    {
        VectorType v = VectorType::RIGHT();
        float alpha = 5.0f;
        v *= alpha;

        VectorType result{alpha, 0.0f};
        ASENGINE_EXPECT(TEST_VECTOR_EQL(v, result));
    });

    Test("test Vector dot product", []()
    {
        VectorType v1 = VectorType::RIGHT();
        VectorType v2 = VectorType::UP();
        float d = v1.Dot(v2);

        ASENGINE_EXPECT(Math::Abs(d) < TEST_PRECISION);
    });

    DescribeSpecializedTests();
}

template class VectorTest<Vector2>;
template class VectorTest<Vector3>;

void Vector2Test::DescribeSpecializedTests()
{
    Test("It can be rotated", []()
    {
        Vector2 v = Vector2::RIGHT();
        Vector2 result = Vector2::UP();
        v = v.Rotate(Math::PI / 2.0);
        ASENGINE_EXPECT(TEST_VECTOR_EQL(v, result));
    });
}

void Vector3Test::DescribeSpecializedTests()
{
}
