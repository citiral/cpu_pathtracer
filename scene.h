#pragma once

#include <glm/vec3.hpp>
#include <vector>

enum class MaterialType {
    LAMBERTIAN,
    MIRROR,
};

class Material {
public:
    virtual void generate_ray(glm::vec3 incident, glm::vec3 normal, glm::vec3 &vec_out, glm::vec3 &col_out, float& factor) = 0;
};

class MaterialLambertian : public Material {
public:
    MaterialLambertian(glm::vec3 color);
    virtual void generate_ray(glm::vec3 incident, glm::vec3 normal, glm::vec3 &vec_out, glm::vec3 &col_out, float& factor);

private:
    glm::vec3 _col;
};

class MaterialMirror : public Material {
public:
    MaterialMirror(glm::vec3 color);
    virtual void generate_ray(glm::vec3 incident, glm::vec3 normal, glm::vec3 &vec_out, glm::vec3 &col_out, float& factor);

private:
    glm::vec3 _col;
};

class SceneObject {
public:
    SceneObject(Material* mat): mat(mat), luminance(0) {};

    virtual bool intersect(glm::vec3& pos, glm::vec3& dir, float& dist) = 0;
    virtual glm::vec3 normal(glm::vec3& pos) = 0;

    Material* mat;
    float luminance;
};


class Sphere : public SceneObject {
public:
    Sphere(glm::vec3 pos, float size, Material* mat);

    bool intersect(glm::vec3& pos, glm::vec3& dir, float& dist);
    glm::vec3 normal(glm::vec3& pos);

private:
    glm::vec3 _pos;
    float _size;
};

class Plane : public SceneObject {
public:
    Plane(glm::vec3 pos, glm::vec3 normal, Material* mat);

    bool intersect(glm::vec3& pos, glm::vec3& dir, float& dist);
    glm::vec3 normal(glm::vec3& pos);

private:
    glm::vec3 _pos;
    glm::vec3 _normal;
};

class Intersection {
public:
    bool hit;
    float dist;
    SceneObject* object;
    glm::vec3 normal;
};


class Scene {
public:
    Scene();
    ~Scene();

    void add_sceneobject(SceneObject* object);
    void intersect(glm::vec3& pos, glm::vec3& dir, Intersection& intersection);
private:
    std::vector<SceneObject*> _sceneobjects;
};