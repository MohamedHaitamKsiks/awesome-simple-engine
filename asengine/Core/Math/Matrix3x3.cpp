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

    ASENGINE_SERIALIAZE_MATRIX(Matrix3x3);

} // namespace ASEngine
