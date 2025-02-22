#ifndef DIELECTRICH
#define DIELECTRICH

#include "../basic/material.h"
#include "../basic/vec3.h"
#include "../basic/ray.h"
#include "../basic/random.h"

class dielectric : public material {
    public:
        dielectric(const vec3 &a, float ri, float f) : ref_idx(ri) {
            if (f < 1) {
                fuzz = f;
            }
            else {
                fuzz = 1;
            }
            albedo = a;
        }
        
        virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
            vec3 outward_normal;
            vec3 reflected;
            reflect(r_in.getDirection(), rec.normal, reflected);
            float ni_over_nt;
            attenuation = albedo;
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
                reflect_prob = 1.0;
            }
            if (drand48() < reflect_prob) {
                vec3 offset_p = rec.p + offset * outward_normal;
                vec3 diffused;
                if (fuzz > 0) {
                    diffuse(outward_normal, diffused);
                    reflected = (1-fuzz) * unit_vector(reflected) + fuzz * diffused;
                }
                scattered = ray(offset_p, reflected);
            }
            else {
                vec3 offset_p = rec.p - offset * outward_normal;
                vec3 diffused;
                if (fuzz > 0) {
                    diffuse(-outward_normal, diffused);
                    refracted = (1-fuzz) * unit_vector(refracted) + fuzz * diffused;
                }
                scattered = ray(offset_p, refracted);
            }
            return true;
        }
        float ref_idx, fuzz;
        vec3 albedo;
    };

#endif