#ifndef LIGHTH
#define LIGHTH
#include "../basic/vec3.h"
#include "../basic/ray.h"
#include "../basic/material.h"
class light : public material{
public:
    light() {}
    light(const vec3 &a) : albedo(a) {}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
        return false;
    }
    virtual vec3 emitted() const {
        return albedo;
    }
    vec3 albedo;
};
#endif