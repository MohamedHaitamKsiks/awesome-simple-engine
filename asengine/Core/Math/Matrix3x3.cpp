#include "Matrix3x3.h"
#include "Math.h"
#include "MatrixSerialiazation.h"

#include "Core/Error/Assertion.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

namespace ASEngine
{
    Matrix3x3 Matrix3x3::Rotation(float angle)
    {
        float cosAngle = Math::Cos(angle);
        float sinAngle = Math::Sin(angle);
        
        return Matrix3x3{
            DataType{
                ColumnType{{ cosAngle, -sinAngle, 0.0f, 0.0f }},
                ColumnType{{ sinAngle,  cosAngle, 0.0f, 0.0f }},
                ColumnType{{ 0.0f,          0.0f, 1.0f, 0.0f }}
            }
        };
    }

    Matrix3x3 Matrix3x3::ViewportProjection(uint32_t width, uint32_t height)
    {
        float viewportWidth = static_cast<float>(width);
        float viewportHeight = static_cast<float>(height);

        // get viewport transform
        Matrix3x3 matrix = Matrix3x3::IDENTITY();
        matrix[0][0] = 2.0f / viewportWidth;
        matrix[1][1] = -2.0f / viewportHeight;
        matrix[0][2] = -1.0f;
        matrix[1][2] = 1.0f;

        return matrix;
    }

    ASENGINE_SERIALIAZE_MATRIX(Matrix3x3);

} // namespace ASEngine
