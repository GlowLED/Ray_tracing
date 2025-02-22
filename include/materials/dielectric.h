#ifndef DIELECTRICH
#define DIELECTRICH

#include "../basic/material.h"
#include "../basic/vec3.h"
#include "../basic/ray.h"
#include "../basic/random.h"

class dielectric : public material {
    public:
        dielectric(float ri) : ref_idx(ri) {}
        
        virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
            vec3 outward_normal;
            vec3 reflected;
            reflect(r_in.getDirection(), rec.normal, reflected);
            float ni_over_nt;
            attenuation = vec3(1.0, 1.0, 1.0);
            vec3 refracted;
            float reflect_prob;
            float cosine;
            float offset = 0.0001;
            if (dot(r_in.getDirection(), rec.normal) > 0) {
                outward_normal = -rec.normal;
                ni_over_nt = ref_idx;
                cosine = ref_idx * dot(r_in.getDirection(), rec.normal) / r_in.getDirection().length();
            }
            else {
                outward_normal = rec.normal;
                ni_over_nt = 1.0 / ref_idx;
                cosine = -dot(r_in.getDirection(), rec.normal) / r_in.getDirection().length();
            }
            if (refract(r_in.getDirection(), outward_normal, ni_over_nt, refracted)) {
                reflect_prob = schlick(cosine, ref_idx);
            }
            else {
                vec3 offset_p = rec.p + offset * outward_normal;
                scattered = ray(offset_p, reflected);
                reflect_prob = 1.0;
            }
            if (drand48() < reflect_prob) {
                vec3 offset_p = rec.p + offset * outward_normal;
                scattered = ray(offset_p, reflected);
            }
            else {
                vec3 offset_p = rec.p - offset * outward_normal;
                scattered = ray(offset_p, refracted);
            }
            return true;
        }
        float ref_idx;
    };

#endif