#ifndef MATERIALH
#define MATERIALH
struct hit_record;

class material {
public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
    virtual vec3 emitted() const {
        return vec3(0.0, 0.0, 0.0);
    }
};

#endif