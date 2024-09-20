#include "Matrix3x3.h"
#include "Core/Error/Assertion.h"
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

    Matrix3x3 Matrix3x3::Inverse() const
    {
        auto& m = (*this);
        Matrix3x3 inv{};

        // computes the inverse of a matrix m
        float det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
                    m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                    m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

        ASENGINE_ASSERT(det != 0.0, "Determinant is zero!");

        float invdet = 1.0f / det;

        inv[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invdet;
        inv[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invdet;
        inv[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invdet;
        inv[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invdet;
        inv[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invdet;
        inv[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * invdet;
        inv[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invdet;
        inv[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * invdet;
        inv[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invdet;

        return inv;
    }

    ASENGINE_SERIALIAZE_MATRIX(Matrix3x3);

} // namespace ASEngine
