#ifndef METALH
#define METALH
#include "../basic/material.h"
#include "../basic/vec3.h"
#include "../basic/ray.h"
class metal : public material {
public:
    metal() {}
    metal(const vec3 &a, float f) : albedo(a) {
        if (f < 1) {
            fuzz = f;
        }
        else {
            fuzz = 1;
        }
    }
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
        vec3 reflected, diffused;
        reflect(unit_vector(r_in.getDirection()), rec.normal, reflected);
        const float offset = 0.0001; // 小偏移量
        vec3 offset_p = rec.p + offset * rec.normal;
        if (fuzz > 0) {
            diffuse(rec.normal, diffused);
            scattered = ray(offset_p, (1-fuzz) * unit_vector(reflected) + fuzz * unit_vector(diffused));
        }
        else {
            scattered = ray(offset_p, reflected);
        }
        attenuation = albedo;
        return (dot(scattered.getDirection(), rec.normal) > 0);
    }
    vec3 albedo;
    float fuzz;
};
#endif