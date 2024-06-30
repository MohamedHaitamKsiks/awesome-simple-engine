
#ifndef __ASENGINE_MAT3_H
#define __ASENGINE_MAT3_H

#include "Core/Error/Assertion.h"
#include "SquareMatrix.h"
#include "Vector2.h"
#include <array>

#include "API/API.h"

namespace ASEngine 
{

    //Matrix3x3 column-major and with stride be compatible with std140
    // Used for 2D transformation on Vector2
    class ASENGINE_API Matrix3x3 : public SquareMatrix<3, 1>
    {
    public:
        constexpr Matrix3x3() = default;

        constexpr Matrix3x3(const DataType &data) : SquareMatrix<3, 1>(data)
        {
        }

        constexpr Matrix3x3(const SquareMatrix<3, 1> &matrix) : SquareMatrix<3, 1>(matrix)
        {
        }

        constexpr Matrix3x3(const Matrix<3, 3, 1>& matrix): SquareMatrix<3, 1>(matrix)
        {
        }

        // scale
        inline static constexpr Matrix3x3 Scale(const Vector2& s)
        {
            return Matrix3x3{
                DataType{
                    ColumnType{{ s.x, 0.0f, 0.0f,  0.0f }},
                    ColumnType{{ 0.0f, s.y,  0.0f, 0.0f }},
                    ColumnType{{ 0.0f, 0.0f, 1.0f, 0.0f }}
                }
            };
        }

        //rotation
        static Matrix3x3 Rotation(float angle);
        
        //translate
        inline static constexpr Matrix3x3 Translate(const Vector2& v)
        {
            return Matrix3x3{
                DataType{
                    ColumnType{{ 1.0f, 0.0f,  v.x, 0.0f }},
                    ColumnType{{ 0.0f, 1.0f,  v.y, 0.0f }},
                    ColumnType{{ 0.0f, 0.0f, 1.0f, 0.0f }}
                }
            }; 
        }

        // transform vec
        friend inline constexpr Vector2 operator*(const Matrix3x3& m, const Vector2& v)
        {
            return Vector2{
                m[1][1] * v.x + m[2][1] * v.y + m[3][1],
                m[1][2] * v.x + m[2][2] * v.y + m[3][2] 
            };
        }

        // viewport projection
        static Matrix3x3 ViewportProjection(uint32_t width, uint32_t height);
    };

} //ASEngine

#endif //ASENGINE_MAT3_H
