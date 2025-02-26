#ifndef OBJECTH
#define OBJECTH

#include "ray.h"
#include "vec3.h"
#include "transform.h"
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
    virtual bool hit_local(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
        if (trans) {
            ray transformed_ray(
                trans->world_to_object(r.origin),
                trans->world_to_object(r.direction)
            );
            
            if (hit_local(transformed_ray, t_min, t_max, rec)) {
                rec.p = trans->object_to_world(rec.p);
                rec.normal = trans->object_to_world(rec.normal);
                return true;
            }
            return false;
        }
        return hit_local(r, t_min, t_max, rec);
    }
    transform *trans=nullptr;
    bool setTransform(transform *t) {
        trans = t;
        return true;
    }
};

#endif