
#ifndef MY_APPLICATION_MAT3_H
#define MY_APPLICATION_MAT3_H

#include <string>
#include <sstream>

#include "math.h"
#include "vec2.h"

namespace ASEngine {

    //mat3
    struct mat3 {
        float data[9];

        float* operator[](int j) {
            return &data[3 * j];
        }


        // get identity matrix
        static mat3 identity() {
            mat3 b = {{
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
            }};
            return b;
        }

        // get zero matrix
        static mat3 zeros() {
            mat3 b = {{
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f
            }};
            return b;
        }

        // scale
        static mat3 scale(vec2 s) {
            mat3 b = {{
                s.x, 0.0f, 0.0f,
                0.0f, s.y, 0.0f,
                0.0f, 0.0f, 1.0f
            }};
            return b;
        }

        //rotation
        static mat3 rotation(float angle) {
            mat3 b = {{
                cos(angle) , sin(angle), 0.0f,
                -sin(angle), cos(angle), 0.0f,
                0.0f,        0.0f,       1.0f
            }};
            return b;
        }


        //translate
        static mat3 translate(vec2 v) {
            mat3 b = {{
                1.0f, 0.0f, v.x,
                0.0f, 1.0f, v.y,
                0.0f, 0.0f, 1.0f
            }};
            return b;
        }

        //transfrom
        static mat3 transform(vec2 translate, vec2 scale, float rotation) {
            mat3 b = {{
                scale.x * cos(rotation), scale.y * sin(rotation), translate.x,
               - scale.x * sin(rotation), scale.y * cos(rotation), translate.y,
                0.0f,                    0.0f,                    1.0f
            }};
            return b;
        }

        // matrix multiplication
        mat3 operator * (mat3 m) {
            mat3 res = mat3::zeros();
            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 3; i++) {
                    for (int k = 0; k < 3; k++) {
                        res[j][i] += (*this)[j][k] * m[k][i];
                    }
                }
            }
            return res;
        }

        // matrix multiplication with vector
        vec2 operator * (vec2 v) {
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
        mat3 operator + (mat3 &m) {
            mat3 res;

            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 3; i++) {
                    res[j][i] = (*this)[j][i] + m[j][i];

                }
            }
            return res;
        }

        //equal
        inline bool operator==(mat3 m) {
            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 3; i++) {
                    if ((*this)[j][i] != m[j][i])
                        return false;
                }
            }
            return true;
        }

        //print matrix

        std::string toString() {
            std::ostringstream os;

            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 3; i++) {
                    os << (*this)[j][i] << ",";
                }
                os << "\n";
            }
            return os.str();
        }
    };

} //ASEngine

#endif //MY_APPLICATION_MAT3_H
