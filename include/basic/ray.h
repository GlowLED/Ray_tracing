#ifndef RAYH
#define RAYH
#include "vec3.h"
#include "random.h"

class ray {
public:
    ray() {}
    ray(const vec3 &o, const vec3 &d) {
        origin = o;
        direction = d;
    }
    vec3 getOrigin() const {return origin;}
    vec3 getDirection() const {return direction;}
    vec3 pointAtParameter(float t) const {
        return origin + t * direction;
    }
    vec3 origin, direction;
};

bool reflect(const vec3 &v, const vec3 &n, vec3 &reflected) {
    reflected = v - 2 * dot(v, n) * n;
    return true;
}

bool diffuse(const vec3 &n, vec3 &diffused) {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (dot(p, p) >= 1.0);
    diffused = n + p;
    return true;
}

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted) {
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    else {
        return false;
    }
}

float schlick(float cosine, float ref_idx) {
    
    // 计算基础反射率
    float r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
    r0 = r0 * r0;
    
    // 计算 Schlick 近似
    float x = 1.0 - cosine;
    return r0 + (1.0 - r0) *pow(x, 5);
}
#endif