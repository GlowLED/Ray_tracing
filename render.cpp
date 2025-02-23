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
#include "include/basic/transform.h"
#include "include/transforms/rotate.h"

int main() {
    int nx = 1920;
    int ny = 1080;
    int ns = 500;
    int max_depth = 50;
    float exposure = 1;
    float aperture = 0.3;
    std::ofstream out("out.ppm");

    vec3 lookfrom(-1.8, 0.8, 1.5);
    vec3 lookat(0, 0.05, 0.25);
    camera cam(lookfrom, lookat, 30, float(nx) / float(ny), aperture);

    material *blue_light_material = new light(vec3(0.0, 0.0, 1.0));
    material *red_light_material = new light(vec3(1.0, 0.0, 0.0));
    material *glass_material = new dielectric(vec3(1.0, 1.0, 1.0), 1.5, 0.0);
    material *metal_material = new metal(vec3(0.8, 0.8, 0.8), 0.5);
    material *red_material = new metal(vec3(0.8, 0.3, 0.3), 0.2);
    material *gray_material = new lambertian(vec3(0.5, 0.5, 0.5));
    material *white_light_material = new light(vec3(1.0, 1.0, 1.0));
    material *green_light_material = new light(vec3(0.0, 1.0, 0.0));

    object *list[6];
    list[0] = new sphere(vec3(1, 0, 0), 0.5, blue_light_material);    // blue lightglass
    list[1] = new sphere(vec3(-1, 0, -0.5), 0.5, red_light_material);    // red light
    list[2] = new cube(vec3(-0.25, -0.2, 0), vec3(0.25, 0.3, 0.5) , gray_material);
    list[3] = new sphere(vec3(0, -0.1, 1.3), 0.4, glass_material);
    list[4] = new cube(vec3(-100, -100, -100), vec3(100, -0.5, 100), gray_material);    // metal cube
    list[5] = new sphere(vec3(-0.2, 0.3, -0.3), 0.3, green_light_material);
    list[2]->setTransform(new rotate(vec3(45, 45, 45), vec3(0, 0, 0)));
    sky* sky = new basicSky();
    world world(list, 6, sky);
    hit_record rec;
    cam.autoDist(world, rec);
    renderer renderer;
    renderer.render(cam, &world, out, ny, nx, max_depth, ns, exposure);

    out.close();
    return 0;
}