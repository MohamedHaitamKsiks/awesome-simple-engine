
#ifndef ASENGINE_MAT3_H
#define ASENGINE_MAT3_H

#include <string>
#include <sstream>

#include "math.h"
#include "vec2.h"

namespace ASEngine {

    //mat3 column based and with stride be compatible with std140
    struct mat3 {
        // matrix data
        float data[12];

        // get identity matrix
        static constexpr mat3 IDENTITY()
        {
            return mat3{{
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f
            }};
        };
        // get zero matrix
        static constexpr mat3 ZEROS()
        {
            return mat3{{
                0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f
            }};
        };

        // scale
        inline static mat3 Scale(const vec2& s)
        {
            return mat3{{
                s.x, 0.0f, 0.0f,  0.0f,
                0.0f, s.y,  0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f
            }};
        }

        //rotation
        inline static mat3 Rotation(float angle)
        {
            return mat3{{
                cos(angle), -sin(angle), 0.0f, 0.0f,
                sin(angle), cos(angle),  0.0f, 0.0f,
                0.0f,       0.0f,        1.0f, 0.0f
            }};
        }
        
        //translate
        inline static mat3 Translate(const vec2& v)
        {
            return mat3{{
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                v.x,  v.y,  1.0f, 0.0f
            }};
        }

        //transfrom
        inline static mat3 Transform(const vec2& translate, const vec2& scale, float rotation)
        {
            return mat3{{
                scale.x * cos(rotation), -scale.x * sin(rotation), translate.x, 0.0f,
                scale.y * sin(rotation),  scale.y * cos(rotation), translate.y, 0.0f,
                translate.x,                          translate.y,        1.0f, 0.0f
            }};
        }

        // tostring matrix
        std::string ToString();

        inline float* operator[](int j)
        {
            return &(data[4 * j]);
        };

        inline const float *operator[](int j) const
        {
            return &(data[4 * j]);
        };

        // matrix multiplication
        friend inline mat3 operator*(const mat3& a, const mat3& b)
        {
            mat3 res = mat3::ZEROS();

            for (int j = 0; j < 3; j++) 
            {
                for (int i = 0; i < 3; i++) 
                {
                    for (int k = 0; k < 3; k++)
                        res[i][j] += a[k][j] * b[i][k];
                }
            }
            return res;
        };

        // matrix multiplication with vector
        friend inline vec2 operator*(const mat3& a, const vec2& v)
        {
            float vector[] = {v.x, v.y, 1.0f};
            float res[] = {0.0f, 0.0f, 0.0f};
            for (int j = 0; j < 3; j++) 
            {
                for (int k = 0; k < 3; k++)
                    res[j] += a[k][j] * vector[k];
            }
            return vec2{res[0], res[1]};
        }


        // matrix addition
        friend inline mat3 operator+(const mat3& a, const mat3& b)
        {
            mat3 res;

            for (int j = 0; j < 3; j++) 
            {
                for (int i = 0; i < 3; i++) 
                    res[j][i] = a[j][i] + b[j][i];
            }
            return res;
        }
    };

} //ASEngine

#endif //ASENGINE_MAT3_H
