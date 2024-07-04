#include "MatrixTest.h"

#define PRECISION 0.00001f

template <typename MatrixType>
inline void MatrixTest<MatrixType>::Describe()
{
    // serialiazation test
    Test("it is serialiazable", []()
    {
        // create matrix object
        Json matrixObject = Json::array();
        for (uint32_t j = 0; j < MatrixType::GetColumnsSize(); j++)
        {
            Json column = Json::array();
            for (uint32_t i = 0; i < MatrixType::GetRowsSize(); i++)
            {
                column.push_back(static_cast<float>(i + j * MatrixType::GetColumnsSize()));
            }
            matrixObject.push_back(column);
        }
        
        // deserialize
        MatrixType matrix;
        Serializer::Deserialize(matrixObject, matrix);
    
        // compare result
        for (uint32_t j = 0; j < MatrixType::GetColumnsSize(); j++)
        {
            for (uint32_t i = 0; i < MatrixType::GetRowsSize(); i++)
            {
                ASENGINE_EXPECT(Math::Abs(matrix[j][i] - matrixObject[j][i].get<float>()) < PRECISION);
            }
        }

        // it serializes
        Json serializedMatrix = Serializer::Serialize(matrix);
        // compare result
        for (uint32_t j = 0; j < MatrixType::GetColumnsSize(); j++)
        {
            for (uint32_t i = 0; i < MatrixType::GetRowsSize(); i++)
            {
                ASENGINE_EXPECT(Math::Abs(serializedMatrix[j][i].get<float>() - matrix[j][i]) < PRECISION);
            }
        }
    });

    DescribeSpecializedTests();
}

void Matrix3x3Test::DescribeSpecializedTests()
{
    Test("It multiplies", []()
    {
        Matrix3x3 a = Matrix3x3::Scale(Vector2::ONE() * 2.0f);
        Matrix3x3 b = Matrix3x3::Translate(Vector2{160.0f, 158.0f});
        Matrix3x3 ab = a * b;

        ASENGINE_EXPECT(ab[0][0] == 2.0f);
        ASENGINE_EXPECT(ab[1][1] == 2.0f);
        ASENGINE_EXPECT(ab[0][2] == 160.0f);
        ASENGINE_EXPECT(ab[1][2] == 158.0f);
    });
}

void Matrix4x4Test::DescribeSpecializedTests()
{
    Test("It multiplies", []()
    {
        Matrix4x4 a = Matrix4x4::Scale(Vector3::ONE() * 2.0f);
        Matrix4x4 b = Matrix4x4::Translate(Vector3{160.0f, 158.0f, 0.5f});
        Matrix4x4 ab = a * b;

        ASENGINE_EXPECT(ab[0][0] == 2.0f);
        ASENGINE_EXPECT(ab[1][1] == 2.0f);
        ASENGINE_EXPECT(ab[2][2] == 2.0f);
        ASENGINE_EXPECT(ab[0][3] == 160.0f);
        ASENGINE_EXPECT(ab[1][3] == 158.0f);
        ASENGINE_EXPECT(ab[2][3] == 0.5f);
    });
}
