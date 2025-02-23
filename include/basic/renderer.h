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

#include <omp.h>

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
        vec3 exposed = color * exposure;
        
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

        int* pixels = new int[height * width * 3];

        int num_threads = omp_get_max_threads();
        omp_set_num_threads(num_threads);

#pragma omp parallel for collapse(2)
    for (int j = height-1; j >= 0; j--) {
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

                int index = ((height-1-j) * width + i) * 3;
                pixels[index] = int(255.99 * col[0]);
                pixels[index + 1] = int(255.99 * col[1]);
                pixels[index + 2] = int(255.99 * col[2]);
                
                #pragma omp critical
                {
                    if (current++ % step == 0) {
                        std::cout << "Rendering " << step_count++ << "%" << std::endl;
                    }
                }
        }
    }
    for (int i = 0; i < total * 3; i++) {
        out << pixels[i] << " ";
    }
    return true;
}
};

#endif