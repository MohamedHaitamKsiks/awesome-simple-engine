#include "Matrix3x3.h"
#include "Math.h"
#include "MatrixSerialiazation.h"

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

    Matrix3x3  Matrix3x3::Transform(const Vector2& position, const Vector2& scale, float rotation)
    {
        float cosAngle = Math::Cos(rotation);
        float sinAngle = Math::Sin(rotation);

        return Matrix3x3{
            DataType{
                ColumnType{{ cosAngle * scale.x, -sinAngle * scale.x, 0.0f, 0.0f }},
                ColumnType{{ sinAngle * scale.y,  cosAngle * scale.y, 0.0f, 0.0f }},
                ColumnType{{ position.x        ,          position.y, 1.0f, 0.0f }}
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
        matrix[2][0] = -1.0f;
        matrix[2][1] = 1.0f;

        return matrix;
    }

    ASENGINE_SERIALIAZE_MATRIX(Matrix3x3);

} // namespace ASEngine
