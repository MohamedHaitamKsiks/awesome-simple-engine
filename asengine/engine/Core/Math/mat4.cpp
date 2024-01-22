#include "mat4.h"

namespace ASEngine
{
    mat4 mat4::Transpose()
    {
        mat4 transposed =  mat4::ZEROS();

        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 4; i++)
                transposed[i][j] = (*this)[j][i];
        }
        return transposed;
    }

    mat4 mat4::RotationX(float angle)
    {
        mat4 b = mat4::IDENTITY();
        b[1][1] = cos(angle);
        b[2][1] = -sin(angle);
        b[1][2] = sin(angle);
        b[2][2] = cos(angle);
        return b;
    }

    mat4 mat4::RotationY(float angle)
    {
        mat4 b = mat4::IDENTITY();
        b[0][0] = cos(angle);
        b[2][0] = -sin(angle);
        b[0][2] = sin(angle);
        b[2][2] = cos(angle);
        return b;
    }

    mat4 mat4::RotationZ(float angle)
    {
        mat4 b = mat4::IDENTITY();
        b[0][0] = cos(angle);
        b[1][0] = -sin(angle);
        b[0][1] = sin(angle);
        b[1][1] = cos(angle);
        return b;
    }


    std::string mat4::ToString()
    {
        std::ostringstream ss;

        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 4; i++)
                ss << (*this)[j][i] << ",";
            
        }
        return ss.str();
    }

    mat4 mat4::OrthographicProjection(float width, float height, float near, float far)
    {
        return mat4
        {{
            2.0f / width,   0.0f,           0.0f,                 0.0f,
            0.0f,           2.0f / height,  0.0f,                 0.0f,
            0.0f,           0.0f,           1.0f / (near - far) , near / (near - far),
            0.0f,           0.0f,           0.0f                , 1.0f
        }};
    }

    mat4 mat4::PerspectiveProjection(float aspectRatio, float fov, float near, float far)
    {
        return mat4
        {{
            1.0f / (tan(fov / 2.0f) * aspectRatio) , 0.0f,                   0.0f,               0.0f,
            0.0f,                                    1.0f / tan(fov / 2.0f), 0.0f,               0.0f,
            0.0f,                                    0.0f,                   far / (near - far), far * near / (near - far),
            0.0f,                                    0.0f,                   -1.0f,              0.0f
        }};
    }

} // namespace ASEngine
