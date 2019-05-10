//
// Created by revetoon on 3/1/19.
//

#include "Scene.hh"

std::vector<Object *> &Scene::getObjects() {
    return objects;
}

std::vector<Material *> &Scene::getMaterials() {
    return materials;
}

void Scene::push(Object *o) {
    objects.push_back(o);
}

void Scene::push(Material *mat) {
    materials.push_back(mat);
}

Scene::Scene() {}

Scene::~Scene() {
    // TODO clean delete
}

Scene::Scene(const std::vector<Object *> &objects, const std::vector<Material *> &materials) : objects(objects),
                                                                                               materials(materials) {}

const std::string &Scene::getMtllib() const {
    return mtllib;
}

void Scene::setMtllib(const std::string &mtllib) {
    Scene::mtllib = mtllib;
}
