#ifndef WORLDH
#define WORLDH
#include "object.h"
#include "sky.h"
class world {
public:
    world(){}
    world(object **l, int n, sky *s) : obj_list(l), obj_n(n), world_sky(s) {}
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
        hit_record temp_rec;
        bool hit_anything = false;
        float closest_so_far = t_max;
        for (int i = 0; i < obj_n; i++) {
            if (obj_list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
    object **obj_list;
    int obj_n;
    sky *world_sky;
};
#endif