#ifndef ROTATEH
#define ROTATEH

#include "transform.h"
#include "vec3.h"
#include "matrix3.h"
class rotate : public transform {
public:
    rotate(const vec3 &a, const vec3 &c) {
        float theta = a.length();
        vec3 axis = unit_vector(a);
        float s = sin(theta);
        float c = cos(theta);
        float t = 1 - c;
        rotation_matrix = mat3(
            t * axis[0] * axis[0] + c, t * axis[0] * axis[1] - s * axis[2], t * axis[0] * axis[2] + s * axis[1],
            t * axis[1] * axis[0] + s * axis[2], t * axis[1] * axis[1] + c, t * axis[1] * axis[2] - s * axis[0],
            t * axis[2] * axis[0] - s * axis[1], t * axis[2] * axis[1] + s * axis[0], t * axis[2] * axis[2] + c
        );
        center = c;
    }
    vec3 apply(const vec3 &v) const {
        return matmul(rotation_matrix, v - center) + center;
    }
    mat3 rotation_matrix;
};

#endif