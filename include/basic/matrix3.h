#ifndef MATRIX3H
#define MATRIX3H
#include "vec3.h"
class mat3 {
public:
    mat3() {}
    mat3(float e00, float e01, float e02, float e10, float e11, float e12, float e20, float e21, float e22) {
        e[0][0] = e00;
        e[0][1] = e01;
        e[0][2] = e02;
        e[1][0] = e10;
        e[1][1] = e11;
        e[1][2] = e12;
        e[2][0] = e20;
        e[2][1] = e21;
        e[2][2] = e22;
    }
    float e[3][3];
};
matmul(const mat3 &m1, const mat3 &m2) {
    mat3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.e[i][j] = m1.e[i][0] * m2.e[0][j] + m1.e[i][1] * m2.e[1][j] + m1.e[i][2] * m2.e[2][j];
        }
    }
    return result;
}
matmul(const mat3 &m, const vec3 &v) {
    vec3 result;
    for (int i = 0; i < 3; i++) {
        result[i] = m.e[i][0] * v[0] + m.e[i][1] * v[1] + m.e[i][2] * v[2];
    }
    return result;
}
#endif