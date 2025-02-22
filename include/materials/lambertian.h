#ifndef LAMBERTIANH
#define LAMBERTIANH
#include "../basic/material.h"
#include "../basic/vec3.h"
#include "../basic/ray.h"
class lambertian : public material {
public:
    lambertian() {}
    lambertian(const vec3 &a) : albedo(a) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
        diffuse(rec.normal, scattered.direction);
        const float offset = 0.0001; // 小偏移量
        vec3 offset_p = rec.p + offset * rec.normal;
        scattered.origin = offset_p;
        attenuation = albedo;
        return true;
    }
    vec3 albedo;
};


#endif