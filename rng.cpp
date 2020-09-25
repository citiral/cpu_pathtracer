#include "rng.h"
#include <glm/glm.hpp>

Rng rng;

Rng::Rng(): _r(), _e1(_r()), _frand_n(0.0, 1.0), _frand_1(0.0, 1.0), _frand_pi(0.0, M_PI)
{

}

float Rng::rand_normal() {
    return _frand_n(_e1);
}

float Rng::rand_one() {
    return _frand_1(_e1);
}

float Rng::rand_pi() {
    return _frand_pi(_e1);
}

glm::vec3 Rng::rand_hemisphere(glm::vec3 n) {
    // https://mathworld.wolfram.com/SpherePointPicking.html

    float u = rand_one() * 2 - 1;
    float theta = rand_pi() * 2;

    float root = sqrt(1 - u*u);

    glm::vec3 rand_sphere = glm::vec3(root * cos(theta), root * sin(theta), u);
    //glm::vec3 rand_sphere = glm::normalize(glm::vec3(rand_normal(), rand_normal(), rand_normal()));
    float c = glm::dot(n, rand_sphere);

    if (c < 0) {
        return rand_sphere - 2 * c * n;
    } else {
        return rand_sphere;
    }
}