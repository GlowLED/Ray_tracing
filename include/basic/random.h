#ifndef RANDOMH
#define RANDOMH
#include <random>
static std::uniform_real_distribution<float> distribution;  // 默认构造即为[0,1)
static std::mt19937 generator;
float drand48() {
    return ::distribution(::generator);
}
#endif