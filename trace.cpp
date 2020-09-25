#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <cmath>
#include <random>
#include "window.h"
#include "texture.h"
#include "scene.h"
#include "pathtracer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640


std::random_device _r;
std::default_random_engine _e1(_r());
std::uniform_real_distribution<float> _frand(0.0, 1.0);

float frand()
{
    return _frand(_e1);
}

int main(int argc, char **argv)
{
    Texture<glm::vec3>* screen = new Texture<glm::vec3>(800, 640);

    Window* window = new Window(800, 640);
    Scene* scene = new Scene();
    PathTracer* pt = new PathTracer(800, 640);

    Sphere* s = new Sphere(glm::vec3(-0.3, 5, 1), 1.5f, new MaterialLambertian(glm::vec3(1, 1, 1)));
    s->luminance = 200;
    scene->add_sceneobject(s);
    scene->add_sceneobject(new Sphere(glm::vec3(1, -0, 0), 1.4f, new MaterialMirror(glm::vec3(0.85, 0.85, 0.85))));
    s = new Sphere(glm::vec3(1, -1.5, -3), 1.4f, new MaterialLambertian(glm::vec3(0.2, 1, 0.2)));
    s->luminance = 550.5f;
    scene->add_sceneobject(s);
    //scene->add_sceneobject(new Sphere(glm::vec3(1.0, -1000.0, 1.0), glm::vec3(1, 1, 1), 997.0f));
    scene->add_sceneobject(new Plane(glm::vec3(0, -3, 0), glm::vec3(0, 1, 0), new MaterialLambertian(glm::vec3(1, 1, 1))));


    glm::vec3 camera_pos = glm::vec3(0, 0, 0);
    glm::vec3 camera_dir = glm::vec3(0, 0, -1);

    camera_pos.x = sin(2) * 15.0f;
    camera_pos.z = cos(2) * 15.0f;
    camera_pos.y = 0.001f;
    camera_dir = glm::normalize(-camera_pos);

    pt->set_scene(scene);
    pt->set_camera(camera_pos, camera_dir);

    while (!window->main_loop()) {
        pt->sample();
        window->draw_texture(pt->get_output());
    }

    delete window;
        
    return EXIT_SUCCESS;
}
