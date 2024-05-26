
#ifndef __ASENGINE_MAT4_H
#define __ASENGINE_MAT4_H

#include "SquareMatrix.h"
#include "Vector3.h"

namespace ASEngine 
{

    //Matrix4x4
    class Matrix4x4: public SquareMatrix<4, 0>
    {
    public:
        constexpr Matrix4x4() = default;

        constexpr Matrix4x4(const DataType& data): SquareMatrix<4, 0>(data)
        {
        }

        constexpr Matrix4x4(const SquareMatrix<4, 0>& matrix): SquareMatrix<4, 0>(matrix)
        {
        }

        constexpr Matrix4x4(const Matrix<4, 4, 0> &matrix) : SquareMatrix<4, 0>(matrix)
        {
        }

        // scale
        static inline constexpr Matrix4x4 Scale(const Vector3& s)
        {
           return Matrix4x4{
            DataType{
                ColumnType{{ s.x , 0.0f, 0.0f, 0.0f }},
                ColumnType{{ 0.0f, s.y,  0.0f, 0.0f }},
                ColumnType{{ 0.0f, 0.0f, s.z,  0.0f }},
                ColumnType{{ 0.0f, 0.0f, 0.0f, 1.0f }}
            }};
        }
        
        //translate
        static inline constexpr Matrix4x4 Translate(const Vector3& v)
        {
            return Matrix4x4{
                DataType{
                    ColumnType{{ 1.0f, 0.0f, 0.0f, 0.0f }},
                    ColumnType{{ 0.0f, 1.0f, 0.0f, 0.0f }},
                    ColumnType{{ 0.0f, 0.0f, 1.0f, 0.0f }},
                    ColumnType{{ v.x,  v.y,  v.z,  1.0f }}
                }
            };
        }

        // rotations
        // rotation around X
        static Matrix4x4 RotationX(float angle);

        // rotation around Y
        static Matrix4x4 RotationY(float angle);

        // rotation around Z
        static Matrix4x4 RotationZ(float angle);

        // get orthographic projection
        static Matrix4x4 OrthographicProjection(float width, float height, float near, float far);

        // get persperctive projection
        static Matrix4x4 PerspectiveProjection(float aspectRatio, float fov, float near, float far);
  
        // matrix multiplication with vector
        friend inline constexpr Vector3 operator*(const Matrix4x4& m, const Vector3& v)
        {
            return Vector3{
                m[1][1] * v.x + m[2][1] * v.y + m[3][1] * v.z + m[4][1],
                m[1][2] * v.x + m[2][2] * v.y + m[3][2] * v.z + m[4][2],
                m[1][3] * v.x + m[2][3] * v.y + m[3][3] * v.z + m[4][3]
            };
        }
        
    };

} //ASEngine

#endif //ASENGINE_MAT4_H
