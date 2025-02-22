#ifndef RANDOMH
#define RANDOMH
#include <random>
#include "vec3.h"
static std::uniform_real_distribution<float> distribution;  // 默认构造即为[0,1)
static std::mt19937 generator;
float drand48() {
    return ::distribution(::generator);
}
vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}
vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
    } while (dot(p, p) >= 1.0);
    return p;
}
#endif