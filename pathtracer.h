#pragma once

#include "texture.h"
#include "scene.h"
#include <glm/vec3.hpp>

class PathTracer {
public:
    PathTracer(int width, int height);

    void set_scene(Scene* scene);
    void set_camera(glm::vec3 pos, glm::vec3 dir);

    Texture<glm::vec3>* get_output();

    void sample();

private:
    glm::vec3 sample_ray(glm::vec3 pos, glm::vec3 dir, int max_depth);

    float rand_normal();
    float rand_one();
    float rand_pi();
    glm::vec3 rand_hemisphere(glm::vec3 n);

    Scene* _scene;
    glm::vec3 _cam_pos;
    glm::vec3 _cam_dir;
    Texture<glm::vec3>* _output;
    int _width;
    int _height;

    int sample_count;
};
