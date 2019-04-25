//
// Created by revetoon on 3/1/19.
//

#include "Scene.hh"

std::vector<Object> &Scene::getObjects() {
    return objects;
}

std::vector<Material> &Scene::getMaterials() {
    return materials;
}

void Scene::push(const Object &o) {
    objects.push_back(o);
}

void Scene::push(const Material &mat) {
    materials.push_back(mat);
}
