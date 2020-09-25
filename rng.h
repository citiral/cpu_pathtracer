#pragma once

#include <random>
#include <glm/vec3.hpp>

class Rng {
public:
    Rng();

    float rand_normal();
    float rand_one();
    float rand_pi();
    glm::vec3 rand_hemisphere(glm::vec3 n);

private:
    std::random_device _r;
    std::default_random_engine _e1; 
    std::normal_distribution<float> _frand_n;
    std::uniform_real_distribution<float> _frand_1;
    std::uniform_real_distribution<float> _frand_pi;
};

extern Rng rng;