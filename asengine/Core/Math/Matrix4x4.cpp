#include "Matrix4x4.h"
#include "Math.h"

namespace ASEngine
{
    Matrix4x4 Matrix4x4::RotationX(float angle)
    {
        Matrix4x4 b = Matrix4x4::IDENTITY();
        b[1][1] = Math::Cos(angle);
        b[1][2] = Math::Sin(angle);
        b[2][1] = -b[1][2];
        b[2][2] = b[1][1];
        return b;
    }

    Matrix4x4 Matrix4x4::RotationY(float angle)
    {
        Matrix4x4 b = Matrix4x4::IDENTITY();
        b[0][0] = Math::Cos(angle);
        b[0][2] = Math::Sin(angle);
        b[2][0] = -b[0][2];
        b[2][2] = b[0][0];
        return b;
    }

    Matrix4x4 Matrix4x4::RotationZ(float angle)
    {
        Matrix4x4 b = Matrix4x4::IDENTITY();
        b[0][0] = Math::Cos(angle);
        b[0][1] = Math::Sin(angle);
        b[1][0] = -b[0][1];
        b[1][1] = b[0][0];
        return b;
    }

    Matrix4x4 Matrix4x4::OrthographicProjection(float width, float height, float near, float far)
    {
        return Matrix4x4 {
            DataType{
                ColumnType{{ 2.0f / width,   0.0f,           0.0f,                 0.0f }},
                ColumnType{{ 0.0f,           2.0f / height,  0.0f,                 0.0f }},
                ColumnType{{ 0.0f,           0.0f,           1.0f / (near - far) , near / (near - far) }},
                ColumnType{{ 0.0f,           0.0f,           0.0f                , 1.0f }}
            }
        };
    }

    Matrix4x4 Matrix4x4::PerspectiveProjection(float aspectRatio, float fov, float near, float far)
    {
        float tanOfFOV = Math::Tan(fov / 2.0f);

        return Matrix4x4 {
            DataType{
                ColumnType{{ 1.0f / (tanOfFOV * aspectRatio) , 0.0f,                   0.0f,               0.0f }},
                ColumnType{{ 0.0f,                             1.0f / tanOfFOV,        0.0f,               0.0f }},
                ColumnType{{ 0.0f,                             0.0f,                   far / (near - far), far * near / (near - far) }},
                ColumnType{{ 0.0f,                             0.0f,                   -1.0f,              0.0f }}
            }
        };
    }

} // namespace ASEngine
