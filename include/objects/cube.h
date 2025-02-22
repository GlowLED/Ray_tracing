#ifndef CUBEH
#define CUBEH
#include "../basic/object.h"
#include "../basic/vec3.h"
#include "../basic/ray.h"
#include "../basic/material.h"
#include "../basic/transform.h"
#include "../transforms/blank.h"

class cube : public object {
public:
    cube() {}
    cube(const vec3 &p0, const vec3 &p1, material *m) : p0(p0), p1(p1), mat_ptr(m) {}
    vec3 p0, p1;
    material *mat_ptr;
    virtual bool hit_local(const ray &r, float t_min, float t_max, hit_record &rec) const {
        float tmin = t_max;
        bool flag = false;
        vec3 p, normal;
        for (int i = 0; i < 3; i++) {
            float t0 = (p0[i] - r.origin[i]) / r.direction[i];
            float t1 = (p1[i] - r.origin[i]) / r.direction[i];
            if (t0 > 0.0 && t0 < tmin) {
                p = r.pointAtParameter(t0);
                if (p0[(i + 1) % 3] < p[(i + 1) % 3] && p[(i + 1) % 3] < p1[(i + 1) % 3] && p0[(i + 2) % 3] < p[(i + 2) % 3] && p[(i + 2) % 3] < p1[(i + 2) % 3]) {
                    tmin = t0;
                    normal = vec3(0, 0, 0);
                    normal[i] = (r.origin[i] < p0[i]) ? -1 : 1;
                    rec.t = t0;
                    rec.p = p;
                    rec.normal = normal;
                    rec.mat_ptr = mat_ptr;
                    flag = true;
                }
            }
            if (t1 > 0.0 && t1 < tmin) {
                p = r.pointAtParameter(t1);
                if (p0[(i + 1) % 3] < p[(i + 1) % 3] && p[(i + 1) % 3] < p1[(i + 1) % 3] && p0[(i + 2) % 3] < p[(i + 2) % 3] && p[(i + 2) % 3] < p1[(i + 2) % 3]) {
                    tmin = t1;
                    normal = vec3(0, 0, 0);
                    normal[i] = (r.origin[i] < p0[i]) ? -1 : 1;
                    rec.t = t1;
                    rec.p = p;
                    rec.normal = normal;
                    rec.mat_ptr = mat_ptr;
                    flag = true;
                }
            }
        }
        return flag;
    }
    
};


#endif