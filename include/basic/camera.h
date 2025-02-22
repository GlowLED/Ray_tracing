#ifndef CAMERAH
#define CAMERAH
#include "vec3.h"
#include "ray.h"
#include "random.h"
#include <cmath>
#include <cfloat>
#include "object.h"
#include "world.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
class camera {
public:
    camera() {
        lower_left_corner = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }
    camera(vec3 lookfrom, vec3 lookat, float vf, float aspt, float aperture) {
        lens_radius = aperture / 2;
        aspect = aspt;
        float focus_dist = 1.0;
        vfov = vf;
        float theta = vfov * M_PI / 180;
        float half_height = tan(theta/2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vec3(0, 1, 0), w));
        v = cross(w, u);
        lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
        horizontal = 2 * half_width * u * focus_dist;
        vertical = 2 * half_height * v * focus_dist;
    }
    ray getRay(float s, float t) {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
    }
    bool autoDist(const world &world, hit_record &rec) {
        if (world.hit(ray(origin, -w), 0.001, FLT_MAX, rec)) {
            float focus_dist = (origin - rec.p).length();
            float theta = vfov * M_PI / 180;
            float half_height = tan(theta/2);
            float half_width = aspect * half_height;
            lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
            horizontal = 2 * half_width * u * focus_dist;
            vertical = 2 * half_height * v * focus_dist;
            return true;
        }
        return false;
    }
private:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius, vfov, aspect;
};

#endif