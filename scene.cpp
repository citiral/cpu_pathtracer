#include "scene.h"
#include "rng.h"
#include <glm/gtx/intersect.hpp>


MaterialLambertian::MaterialLambertian(glm::vec3 color): _col(color)
{

}

void MaterialLambertian::generate_ray(glm::vec3 incident, glm::vec3 normal, glm::vec3 &vec_out, glm::vec3 &col_out, float& factor)
{
    vec_out = rng.rand_hemisphere(normal);
    col_out = _col;

    float p = 1.0f / (2.0f * M_PI);
    factor =  glm::dot(vec_out, normal) / M_PI / p;
}

MaterialMirror::MaterialMirror(glm::vec3 color): _col(color)
{

}

void MaterialMirror::generate_ray(glm::vec3 incident, glm::vec3 normal, glm::vec3 &vec_out, glm::vec3 &col_out, float& factor)
{
    vec_out = glm::reflect(incident, normal);

    col_out = _col;

    factor = 1;
}

Sphere::Sphere(glm::vec3 pos, float size, Material* mat): SceneObject(mat), _pos(pos), _size(size)
{

}

bool Sphere::intersect(glm::vec3& pos, glm::vec3& dir, float& dist)
{
    return glm::intersectRaySphere(pos, dir, _pos, _size*_size, dist);
}

glm::vec3 Sphere::normal(glm::vec3& pos)
{
    return glm::normalize(pos - _pos);
}

Plane::Plane(glm::vec3 pos, glm::vec3 normal, Material* mat): SceneObject(mat), _pos(pos), _normal(normal)
{
}
bool Plane::intersect(glm::vec3& pos, glm::vec3& dir, float& dist)
{
    //glm::vec3 rpos = _pos - pos;
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
    float denom = - glm::dot(_normal, dir);

    if (denom > 1e-6) {
        glm::vec3 p0l0 = _pos - pos;
        dist = - glm::dot(p0l0, _normal) / denom;
        return dist > 0;
    }

    return false;
}

glm::vec3 Plane::normal(glm::vec3& pos)
{
    return _normal;
}

Scene::Scene()
{

}

Scene::~Scene()
{
    for (SceneObject* obj : _sceneobjects) {
        delete obj;
    }
}

void Scene::add_sceneobject(SceneObject* object)
{
    _sceneobjects.push_back(object);    
}

void Scene::intersect(glm::vec3& pos, glm::vec3& dir, Intersection& intersection)
{
    intersection.hit = false;
    float dist;

    for (SceneObject* obj : _sceneobjects) {
        if (obj->intersect(pos, dir, dist)) {
            if (!intersection.hit || dist < intersection.dist) {
                intersection.hit = true;
                intersection.object = obj;
                intersection.dist = dist;
            }
        }
    }
}