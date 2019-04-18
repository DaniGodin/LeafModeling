//
// Created by revetoon on 3/26/19.
//

#include <iostream>
#include "TreeTranslator.hh"

std::vector<Object> TreeTranslator::generate(Node *root, std::string name, GENTYPE gentype = GENTYPE::line) {
    if (gentype == GENTYPE::line) {

        Object o = Object(name);

        // push the root
        o.getV().push_back(std::move(root->getPt()));
        genTreeO(root, o, 0);
        return std::vector<Object>{o};
    }

    if (gentype == GENTYPE::cylinder) {

        double trunkHeight = 3;
        Cylinder trunk = Cylinder(root->getPt() + (Vector3D::up() * -trunkHeight), Vector3D::up(), trunkHeight, root->getEnergy(), name + "_trunk");
        std::vector<Object> objs(1, trunk);

        // push cylinders
        genTreeCyl(root, name, objs, trunk);

        return std::move(objs);
    }

    throw std::out_of_range("specified gentype does not exist.");
}

void TreeTranslator::genTreeO(Node *n, Object &o, long rootIndex) {
    // root already pushed -> gotta find its index
//    auto it = std::find(o.getV().begin(), o.getV().end(), n);
//    if (it == std::end(o.getV())) {
//        std::cerr << "Error in getV" << std::endl;
//        return;
//    }
//    // index of root
//    long rootIndex = std::distance(o.getV().begin(), it);

    // iterate through children (tree structure so each child is a new node)
    for (auto &c : n->getChildren()) {
        // push child & get its index
        long index = o.getV().size();
        o.getV().push_back(std::move(c->getPt()));
        // create line elt from root to child
        LineEl l = LineEl();
        // root pt
        l.getVertices().push_back(
                std::make_tuple(
                        std::make_tuple<int, Point3D *>(rootIndex, &o.getV()[rootIndex]),
                        std::make_tuple<int, Texture2D *>(0, nullptr))
        );
        // child pt
        l.getVertices().push_back(
                std::make_tuple(
                        std::make_tuple<int, Point3D *>(index, &o.getV()[index]),
                        std::make_tuple<int, Texture2D *>(0, nullptr))
        );
        // push line elt
        o.getLineEls().push_back(std::move(l));
        // iterate through child
        genTreeO(c, o, index);
    }
}

void TreeTranslator::genTreeCyl(Node *n, const std::string &name, std::vector<Object> &objs, const Cylinder &parentCyl) {
    static unsigned count = 0;
    // iterate through children (tree structure so each child is a new node)
    for (auto &c : n->getChildren()) {
        Vector3D direction = c->getPt() - parentCyl.getCenterUp();
        // Generate cylinders with SAME bottom and top radius
//        Cylinder cyl = Cylinder(parentCyl.getCenterUp(), direction, direction.length(), c->getEnergy(), name + "_" + std::to_string(count++));
        // Generate cylinders with DIFFERENT bottom and top radius
        Cylinder cyl = Cylinder(parentCyl.getCenterUp(), direction, direction.length(), n->getEnergy(), c->getEnergy(), name + "_" + std::to_string(count++));
        std::cout << cyl.getName() << " "  <<c->getEnergy() << std::endl;
        objs.push_back(std::move(cyl));
        ;
        // iterate through child
        genTreeCyl(c, name, objs, cyl);
    }
}
