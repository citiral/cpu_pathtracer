#include "pathtracer.h"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include "rng.h"

PathTracer::PathTracer(int width, int height): _width(width), _height(height), sample_count(0) {
    _output = new Texture<glm::vec3>(width, height);
}

void PathTracer::set_scene(Scene* scene) {
    _scene = scene;
}

void PathTracer::set_camera(glm::vec3 pos, glm::vec3 dir) {
    _cam_pos = pos;
    _cam_dir = dir;
}

Texture<glm::vec3>* PathTracer::get_output() {
    return _output;
}

glm::vec3 PathTracer::sample_ray(glm::vec3 pos, glm::vec3 dir, int max_depth)
{
    // Intersect the ray with the world
    Intersection inter;
    _scene->intersect(pos, dir, inter);

    // If we hit something, recursively continue the ray
    if (inter.hit) {
        glm::vec3 inter_point = pos + dir * inter.dist;
        glm::vec3 normal = inter.object->normal(inter_point);
        glm::vec3 incoming_luminance;

        glm::vec3 bounce;
        glm::vec3 color = glm::vec3(1, 1, 1);
        float factor;
        inter.object->mat->generate_ray(dir, normal, bounce, color, factor);

        if (max_depth > 0) {
                incoming_luminance = sample_ray(inter_point + normal * 0.0001f, bounce, max_depth - 1);

                float p = 1.0f / (2.0f * M_PI);
                return (color * inter.object->luminance) +
                       (color * (incoming_luminance * factor));
        } else {
            return color * inter.object->luminance;
        }
    }
    // If the ray didn't hit anything, return the background color 0,0,0
    else {
        return glm::vec3(0.3, 0.3, 0.7) * 20.0f;
    }
}

void PathTracer::sample() {
    sample_count++;

    glm::vec3 up = glm::vec3(0, 1, 0);

    float ratio = _width / (float)_height;

    float pixel_width = 1 / (float)_width * ratio;
    float pixel_height = 1 / (float)_height;

    for (int y = 0; y < _height ; y++) {
        for (int x = 0; x < _width ; x++) {
            
            
            float fx = x / (float)_width * ratio;
            float fy = y / (float)_height;

            // Intersect from the camera with the world
            Intersection inter;
            glm::vec3 right = glm::cross(_cam_dir, up);
            glm::vec3 ray_dir = glm::normalize(_cam_dir + ((fx + rng.rand_one()*pixel_width - pixel_width/2) - (ratio / 2.0f)) * right - ((fy + rng.rand_one()*pixel_height - pixel_height/2) - 0.5f) * up);

            glm::vec3 sample = sample_ray(_cam_pos, ray_dir, 8);
            _output->set_pixel(x, y, (sample + _output->get_pixel(x, y) * (float)(sample_count - 1)) / (float)sample_count);
        }
    }
}
