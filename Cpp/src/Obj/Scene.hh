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
    Scene();

    virtual ~Scene();

    std::vector<Object *> &getObjects();

    std::vector<Material *> &getMaterials();

    void push(Object *o);
    void push(Material *mat);

private:
    std::vector<Object *> objects;
    std::vector<Material *> materials;
};


#endif //OBJPARSER_SCENE_HH
