//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_SCENE_HH
#define OBJPARSER_SCENE_HH


#include <vector>
#include "Element.hh"
#include "Material.hh"
#include "Object.hh"

class Scene {
public:
    std::vector<Object> &getObjects();

    std::vector<Material> &getMaterials();

    void push(const Object &o);
    void push(const Material &mat);

private:
    std::vector<Object> objects;
    std::vector<Material> materials;
};


#endif //OBJPARSER_SCENE_HH
