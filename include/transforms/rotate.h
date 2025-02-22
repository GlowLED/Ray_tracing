#ifndef ROTATEH
#define ROTATEH

#include "../basic/transform.h"
#include "../basic/vec3.h"
#include "../basic/matrix3.h"
class rotate : public transform {
public:
    rotate(const vec3 &a, const vec3 &c) {
        vec3 rad = a * (M_PI / 180);
        mat3 rotation_matrix_x(
            1, 0, 0, 
            0, cos(rad[0]), -sin(rad[0]),
            0, sin(rad[0]), cos(rad[0])
        );
        mat3 rotation_matrix_y(
            cos(rad[1]), 0, sin(rad[1]),
            0, 1, 0,
            -sin(rad[1]), 0, cos(rad[1])
        );
        mat3 rotation_matrix_z(
            cos(rad[2]), -sin(rad[2]), 0,
            sin(rad[2]), cos(rad[2]), 0,
            0, 0, 1
        );
        rotation_matrix = matmul(rotation_matrix_z, matmul(rotation_matrix_y, rotation_matrix_x));
        rotation_matrix_transposed = rotation_matrix.transpose();
        center_in_world = c;
        center_in_object = matmul(rotation_matrix_transposed, center_in_world);
    }
    virtual vec3 world_to_object(const vec3 &v) const {
        return matmul(rotation_matrix_transposed, v - center_in_world) + center_in_object;
    } 
    virtual vec3 object_to_world(const vec3 &v) const {
        return matmul(rotation_matrix, v - center_in_object) + center_in_world;
    }
    mat3 rotation_matrix, rotation_matrix_transposed;
    vec3 center_in_world, center_in_object;
};

#endif