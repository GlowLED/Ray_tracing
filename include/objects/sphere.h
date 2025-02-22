#ifndef SPHEREH
#define SPHEREH
#include "../basic/object.h"
#include "../basic/vec3.h"
#include "../basic/ray.h"
#include "../basic/material.h"
class sphere : public object {
public:
    sphere() {}
    sphere(const vec3 &c, float r, material *m) : center(c), radius(r), mat_ptr(m) {}
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
        vec3 oc = r.getOrigin() - center;
        float a = dot(r.getDirection(), r.getDirection());
        float b = dot(oc, r.getDirection());
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b * b - a * c;
        if (discriminant > 0) {
            float temp = (-b - sqrt(discriminant)) / a;
            if (temp < t_max && temp > t_min) {
                rec.t = temp;
                rec.p = r.pointAtParameter(rec.t);
                rec.normal = (rec.p - center) / radius;
                rec.mat_ptr = mat_ptr;
                return true;
            }
            temp = (-b + sqrt(discriminant)) / a;
            if (temp < t_max && temp > t_min) {
                rec.t = temp;
                rec.p = r.pointAtParameter(rec.t);
                rec.normal = (rec.p - center) / radius;
                rec.mat_ptr = mat_ptr;
                return true;
            }
        }
        return false;
    }
    vec3 center;
    float radius;
    material *mat_ptr;
};
#endif