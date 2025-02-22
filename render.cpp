#include <fstream>
#include <iostream>
#include <string>

#include "include/basic/camera.h"
#include "include/basic/material.h"
#include "include/basic/object.h"
#include "include/basic/ray.h"
#include "include/basic/renderer.h"
#include "include/basic/sky.h"
#include "include/basic/vec3.h"
#include "include/basic/world.h"
#include "include/materials/metal.h"
#include "include/objects/sphere.h"
#include "include/skys/basicSky.h"
#include "include/objects/cube.h"
#include "include/materials/dielectric.h"
#include "include/materials/light.h"
#include "include/skys/blackSky.h"
#include "include/materials/lambertian.h"

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 1000;
    int max_depth = 50;
    float exposure = 1;
    std::ofstream out("out.ppm");

    vec3 lookfrom(-1.5, 0.25, 2);
    vec3 lookat(0, 0, 0);
    camera cam(lookfrom, lookat, 60, float(nx) / float(ny));

    material *blue_light_material = new light(vec3(0.0, 0.0, 1.0));
    material *red_light_material = new light(vec3(1.0, 0.0, 0.0));
    material *glass_material = new dielectric(vec3(0.0, 1.0, 0.0), 1.5, 0.2);
    material *metal_material = new metal(vec3(0.8, 0.8, 0.8), 0.5);
    material *red_material = new metal(vec3(0.8, 0.3, 0.3), 0.2);
    material *gray_material = new lambertian(vec3(0.5, 0.5, 0.5));
    material *white_light_material = new light(vec3(1.0, 1.0, 1.0));

    object *list[6];
    list[0] = new sphere(vec3(1, 0, 0), 0.5, blue_light_material);    // blue lightglass
    list[1] = new sphere(vec3(-1, 0, 0), 0.5, red_light_material);    // red light
    list[2] = new cube(vec3(-0.25, -0.5, 0), vec3(0.25, 0.0, 0.5) , metal_material);    // red cube
    list[3] = new sphere(vec3(0, -0.1, 1.3), 0.4, glass_material);    // glass sphere
    list[4] = new cube(vec3(-100, -100, -100), vec3(100, -0.5, 100), gray_material);    // metal cube
    list[5] = new sphere(vec3(0, 1.5, 0), 0.3, white_light_material);    // white light
    sky* sky = new blackSky();
    world world(list, 6, sky);

    renderer renderer;
    renderer.render(cam, &world, out, ny, nx, max_depth, ns, exposure);

    out.close();
    return 0;
}