#ifndef OBJECTH
#define OBJECTH

#include "ray.h"
#include "vec3.h"
class material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        bool front_face = dot(r.direction, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class object {
public:
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};

#endif