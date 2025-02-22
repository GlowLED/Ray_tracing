#ifndef TRANSFORMH
#define TRANSFORMH
#include "vec3.h"
class transform {
public:
    virtual vec3 apply(const vec3 &v) const = 0;
}
#endif