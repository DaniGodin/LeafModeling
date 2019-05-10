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

    Scene(const std::vector<Object *> &objects, const std::vector<Material *> &materials);

    virtual ~Scene();

    std::vector<Object *> &getObjects();

    std::vector<Material *> &getMaterials();

    const std::string &getMtllib() const;

    void setMtllib(const std::string &mtllib);

    void push(Object *o);
    void push(Material *mat);

private:
    std::vector<Object *> objects;
    std::vector<Material *> materials;
    std::string mtllib = "";
};


#endif //OBJPARSER_SCENE_HH
