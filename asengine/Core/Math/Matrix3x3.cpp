#include "Matrix3x3.h"
#include "Math.h"

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

} // namespace ASEngine
