#ifndef BLACKSKYH
#define BLACKSKYH
#include "../basic/sky.h"
#include "../basic/vec3.h"
#include "../basic/ray.h"
class blackSky : public sky {
public:
    blackSky() {}
    virtual vec3 getColor(const ray &r) const {
        return vec3(0.0, 0.0, 0.0);
    }
};

#endif