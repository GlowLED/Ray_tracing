#ifndef SKYH
#define SKYH
#include "ray.h"
class sky {
public:
    virtual vec3 getColor(const ray &r) const = 0;
};

#endif