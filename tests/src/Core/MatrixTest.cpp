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
        Serializer<MatrixType>::Deserialize(matrixObject, matrix);
    
        // compare result
        for (uint32_t j = 0; j < MatrixType::GetColumnsSize(); j++)
        {
            for (uint32_t i = 0; i < MatrixType::GetRowsSize(); i++)
            {
                ASENGINE_EXPECT(Math::Abs(matrix[j][i] - matrixObject[j][i].get<float>()) < PRECISION);
            }
        }

        // it serializes
        Json serializedMatrix = Serializer<MatrixType>::Serialize(matrix);
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

}

void Matrix4x4Test::DescribeSpecializedTests()
{
}
