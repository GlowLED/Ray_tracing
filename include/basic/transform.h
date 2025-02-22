#ifndef TRANSFORMH
#define TRANSFORMH
#include "vec3.h"
class transform {
public:
    virtual vec3 world_to_object(const vec3 &v) const = 0;
    virtual vec3 object_to_world(const vec3 &v) const = 0;
};
#endif