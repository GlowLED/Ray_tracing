#ifndef BASICSKYH
#define BASICSKYH
#include "../basic/sky.h"
class basicSky : public sky {
public:
    basicSky() {}
    virtual vec3 getColor(const ray &r) const {
        vec3 unit_direction = unit_vector(r.getDirection());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
};
#endif