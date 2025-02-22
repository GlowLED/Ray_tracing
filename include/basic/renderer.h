#ifndef RENDERERH
#define RENDERERH
#include "camera.h"
#include "object.h"
#include "ray.h"
#include "vec3.h"
#include "world.h"
#include <fstream>
#include <string>
#include <cfloat>
#include <iostream>
class renderer {
public:
    renderer() {}
    vec3 color(const ray &r, world *world, int depth, int max_depth) {
        if (depth >= max_depth) {
            return vec3(0, 0, 0);
        }
        hit_record rec;
        if (world->hit(r, 0.0, FLT_MAX, rec)) {
            ray scattered;
            vec3 attenuation;
            if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
                return attenuation * color(scattered, world, depth + 1, max_depth);
            }
            else {
                return rec.mat_ptr->emitted();
            }
        }
        else {
            return world->world_sky->getColor(r);
        }
    }
    vec3 tone_map(const vec3& color, float exposure) const {
        // 应用曝光度
        vec3 exposed = color * exposure;
        
        // 进行伽马校正
        return vec3(
            sqrt(exposed[0]),
            sqrt(exposed[1]),
            sqrt(exposed[2])
        );
    }
    bool render(camera &cam, world *world, std::ofstream &out, int height, int width, int max_depth, int antialasing, float exposure) {
        out << "P3\n" << width << " " << height << "\n255\n";
        int total = height * width;
        int step = total / 100;
        int current = 0, step_count = 0;
        for (int j = height - 1; j >= 0; j--) {
            for (int i = 0; i < width; i++) {
                vec3 col(0, 0, 0);
                for (int s = 0; s < antialasing; s++) {
                    float u = float(i + drand48()) / float(width);
                    float v = float(j + drand48()) / float(height);
                    ray r = cam.getRay(u, v);
                    col += color(r, world, 0, max_depth);
                }
                col /= float(antialasing);
                col = tone_map(col, exposure);
                int ir = int(255.99 * col[0]);
                int ig = int(255.99 * col[1]);
                int ib = int(255.99 * col[2]);
                out << ir << " " << ig << " " << ib << "\n";
                current++;
                if (current % step == 0) {
                    step_count++;
                    std::cout << "Progress: " << step_count << "%" << std::endl;
                }
            }
        }
        return true;
    }
};

#endif