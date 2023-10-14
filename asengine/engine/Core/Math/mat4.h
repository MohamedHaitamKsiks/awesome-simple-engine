
#ifndef ASENGINE_MAT4_H
#define ASENGINE_MAT4_H

#include <string>
#include <sstream>

#include "math.h"
#include "vec3.h"

namespace ASEngine {

    //mat4
    struct mat4 
    {
        // matrix data
        float data[16];

        // get identity matrix
        static constexpr mat4 IDENTITY()
        {
            return mat4
            {{
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            }};
        };
        // get zero matrix
        static constexpr mat4 ZEROS()
        {
            return mat4
            {{
                0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f
            }};
        };

        // scale
        inline static mat4 Scale(const vec3& s)
        {
           return mat4
           {{
                s.x, 0.0f, 0.0f, 0.0f,
                0.0f, s.y, 0.0f, 0.0f,
                0.0f, 0.0f, s.z, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            }};
        }
        
        //translate
        inline static mat4 Translate(const vec3& v)
        {
            return mat4
            {{
                1.0f, 0.0f, 0.0f, v.x,
                0.0f, 1.0f, 0.0f, v.y,
                0.0f, 0.0f, 1.0f, v.z,
                0.0f, 0.0f, 0.0f, 1.0f
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
        friend inline mat4 operator*(const mat4& a, const mat4& b)
        {
            mat4 res = mat4::ZEROS();

            for (int j = 0; j < 4; j++) 
            {
                for (int i = 0; i < 4; i++) 
                {
                    for (int k = 0; k < 4; k++) 
                        res[j][i] += a[j][k] * b[k][i];
                }
            }
            return res;
        };

        // matrix multiplication with vector
        friend inline vec3 operator*(const mat4& a, const vec3& v)
        {
            float vector[] = {v.x, v.y, v.z, 1.0f};
            float res[] = {0.0f, 0.0f, 0.0f, 0.0f};
            for (int j = 0; j < 4; j++) 
            {
                for (int k = 0; k < 4; k++) 
                    res[j] += a[j][k] * vector[k];
            }
            return vec3{res[0], res[1], res[2]};
        }


        // matrix addition
        friend inline mat4 operator+(const mat4& a, const mat4& b)
        {
            mat4 res;

            for (int j = 0; j < 4; j++) 
            {
                for (int i = 0; i < 4; i++) 
                    res[j][i] = a[j][i] + b[j][i];
            }
            return res;
        }
    };

} //ASEngine

#endif //ASENGINE_MAT4_H
