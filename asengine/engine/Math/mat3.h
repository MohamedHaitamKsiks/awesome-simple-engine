
#ifndef ASENGINE_MAT3_H
#define ASENGINE_MAT3_H

#include <string>
#include <sstream>

#include "math.h"
#include "vec2.h"

namespace ASEngine {

    //mat3
    struct mat3 {
        // matrix data
        float data[9];

        // get identity matrix
        static constexpr mat3 IDENTITY()
        {
            return {{
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
            }};
        };
        // get zero matrix
        static constexpr mat3 ZEROS()
        {
            return {{
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f
            }};
        };

        // scale
        static mat3 Scale(const vec2& s);
        //rotation
        static mat3 Rotation(float angle);
        //translate
        static mat3 Translate(const vec2& v);
        //transfrom
        static mat3 Transform(const vec2& translate, const vec2& scale, float rotation);
        // tostring matrix
        std::string ToString();

        inline float* operator[](int j)
        {
            return &(data[3 * j]);
        };

        // matrix multiplication
        inline mat3 operator * (mat3 m) 
        {
            mat3 res = mat3::ZEROS();

            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 3; i++) {
                    for (int k = 0; k < 3; k++) {
                        res[j][i] += (*this)[j][k] * m[k][i];
                    }
                }
            }
            return res;
        };

        // matrix multiplication with vector
        inline vec2 operator * (vec2 v) 
        {
            float vector[] = {v.x, v.y, 1.0f};
            float res[] = {0.0f, 0.0f, 0.0f};
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    res[j] += (*this)[j][k] * vector[k];
                }
            }
            return vec2{res[0], res[1]};
        }


        // matrix addition
        inline mat3 operator + (mat3 m)
        {
            mat3 res;

            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 3; i++) {
                    res[j][i] = (*this)[j][i] + m[j][i];

                }
            }
            return res;
        }

        //equal
        inline bool operator==(mat3 m) 
        {
            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 3; i++) {
                    if ((*this)[j][i] != m[j][i])
                        return false;
                }
            }
            return true;
        }
    };

} //ASEngine

#endif //ASENGINE_MAT3_H
