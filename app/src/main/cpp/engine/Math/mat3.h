//
// Created by ksiks_wa3r on 3/20/23.
//

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
            mat3 b = identity();
            b[0][0] = s.x;
            b[1][1] = s.y;
            return b;
        }

        //rotation
        static mat3 rotation(float angle) {
            mat3 b = identity();
            b[0][0] = cos(angle);
            b[1][0] = -sin(angle);
            b[0][1] = sin(angle);
            b[1][1] = cos(angle);
            return b;
        }


        //translate
        static mat3 translate(vec2 v) {
            mat3 b = identity();
            b[0][2] = v.x;
            b[1][2] = v.y;
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


        // matrix addition
        mat3 operator + (mat3 m) {
            mat3 res;

            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 3; i++) {
                    res[j][i] = (*this)[j][i] + m[j][i];

                }
            }
            return res;
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
