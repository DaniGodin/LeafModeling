//
// Created by revetoon on 3/26/19.
//

#include <iostream>
#include <cmath>
#include "TreeTranslator.hh"
#include "../Utils/Strutils.hh"

std::vector<Object *> TreeTranslator::generate(Node *root, std::string name, const Color &rootCol, const Color &leafCol, GENTYPE gentype) {
    if (gentype == GENTYPE::line) {

        Object *o = new Object(name);

        // push the root
        o->push(root->getPt());
//        o.getV().push_back(std::move(root->getPt()));
        genTreeO(root, o, 0);
        return std::vector<Object*>{o};
    }

    if (gentype == GENTYPE::cylinder) {

        double trunkHeight = 0.1;
        Cylinder *trunk = new Cylinder(root->getPt() + (Vector3D::up() * -trunkHeight), Vector3D::up(), trunkHeight, root->getEnergy(), name + "_trunk", 30);
        Material *m = new Material(Strutils::nameId("Vein"), Color::white(), rootCol, Color::white());
        trunk->setUniformMaterial(m);
        scene.push(m);
        scene.push(trunk);
        std::vector<Object*> objs(1, trunk);

        // push cylinders
        genTreeCyl(root, name, objs, trunk, rootCol, leafCol);

        return objs;
    }

    throw std::out_of_range("specified gentype does not exist.");
}

void TreeTranslator::genTreeO(Node *n, Object *o, long rootIndex) {
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
        long index = o->getV().size();
        o->push(c->getPt());
//        o.getV().push_back(std::move(c->getPt()));
        // create line elt from root to child
        LineEl l = LineEl(o);
        // root pt
        l.push(o->getV()[rootIndex], rootIndex);
//        l.getVertices().push_back(
//                std::make_tuple(
//                        std::make_tuple<int, Point3D *>(rootIndex, &o.getV()[rootIndex]),
//                        std::make_tuple<int, Texture2D *>(0, nullptr))
//        );
        // child pt
        l.push(o->getV()[index], index);
//        l.getVertices().push_back(
//                std::make_tuple(
//                        std::make_tuple<int, Point3D *>(index, &o.getV()[index]),
//                        std::make_tuple<int, Texture2D *>(0, nullptr))
//        );
        // push line elt
        o->push(l);
//        o.getLineEls().push_back(std::move(l));
        // iterate through child
        genTreeO(c, o, index);
    }
}

void TreeTranslator::genTreeCyl(Node *n, const std::string &name, std::vector<Object*> &objs, const Cylinder *parentCyl, const Color &rootCol, const Color &leafCol) {
    static unsigned count = 0;
    int depth = Node::depth(n);
    // iterate through children (tree structure so each child is a new node)
    Color deltaCol = (leafCol - rootCol) / depth;
    for (auto &c : n->getChildren()) {
        Vector3D direction = c->getPt() - parentCyl->getCenterUp();
        // Generate cylinders with SAME bottom and top radius
//        Cylinder *cyl = new Cylinder(parentCyl->getCenterUp(), direction, direction.length(), c->getEnergy(), name + "_" + std::to_string(count++), 6);
        // Generate cylinders with DIFFERENT bottom and top radius
        Cylinder *cyl = new Cylinder(parentCyl->getCenterUp(), direction, direction.length(), n->getEnergy(), c->getEnergy(), name + "_" + std::to_string(count++));
//        std::cout << cyl.getName() << " "  <<c->getEnergy() << std::endl;
        // Create uniform texture
        Material *m = new Material(Strutils::nameId("Vein"), Color::white(), rootCol + deltaCol, Color::white());
        cyl->setUniformMaterial(m);
        scene.push(m);
        // Push cylinder
        objs.push_back(cyl);
        scene.push(cyl);
        // iterate through child
        genTreeCyl(c, name, objs, cyl, rootCol + deltaCol, leafCol);
    }
}

std::vector<Object *>
TreeTranslator::generate(algoLeaf::venationPoint *root, std::string name, int pointCount, const Color &rootCol, const Color &leafCol) {
    Node *converted = convertVenationToNode(root, pointCount);
    auto result = generate(converted, name, rootCol, leafCol);
    delete converted;
    return result;
}

std::vector<Object *>
TreeTranslator::generate(Nodes::VenNodePlot *root, std::string name, int pointCount, const Color &rootCol, const Color &leafCol) {
    Node *converted = convertVenNodeToNode(root, pointCount);
    auto result = generate(converted, name, rootCol, leafCol);
    delete converted;
    return result;
}

Node *TreeTranslator::convertVenationToNode_rec(algoLeaf::venationPoint *venation, Node *parent, int pointCount) {
    Node *n = new Node(venation->position, parent, static_cast<double>(venation->photoEnergy) / (static_cast<double>(pointCount) * 0.5));

    for (auto *c : venation->childrens) {
        n->getChildren().push_back(convertVenationToNode_rec(c, n, pointCount));
    }

    return n;
}

Node *TreeTranslator::convertVenationToNode(algoLeaf::venationPoint *root, int pointCount) {
    Node *n = new Node(root->position, nullptr, static_cast<double>(root->photoEnergy) / (static_cast<double>(pointCount) * 0.5));

    for (auto *c : root->childrens) {
        n->getChildren().push_back(convertVenationToNode_rec(c, n, pointCount));
    }

    return n;
}

TreeTranslator::TreeTranslator(Scene &scene) : scene(scene) {}

Node *TreeTranslator::convertVenNodeToNode(Nodes::VenNodePlot *root, int pointCount) {
    Node *n = new Node(root->pos, nullptr, static_cast<double>(root->radius) / (static_cast<double>(pointCount) * 0.5));

    for (auto &c : root->childrens) {
        n->getChildren().push_back(convertVenNodeToNode_rec(&c, n, pointCount));
    }

    return n;
}

Node *TreeTranslator::convertVenNodeToNode_rec(Nodes::VenNodePlot *venation, Node *parent, int pointCount) {
    Node *n = new Node(venation->pos, parent, static_cast<double>(venation->radius) / (static_cast<double>(pointCount) * 0.5));

    for (auto &c : venation->childrens) {
        n->getChildren().push_back(convertVenNodeToNode_rec(&c, n, pointCount));
    }

    return n;
}

Node *TreeTranslator::simplifyTree_(Node *n, int step, int skipStep, Node *parent) {
    Node *p = parent;
    int sk = ++skipStep;
    if (skipStep >= step || n->getChildren().empty()) {
        Node *node = new Node(n->getPt(), parent, n->getEnergy());
        parent->getChildren().push_back(node);
        p = node;
        sk = 0;
    }
    for (auto *c : n->getChildren()) {
        simplifyTree_(c, step, sk, p);
    }
    return nullptr;
}

Node *TreeTranslator::simplifyTree(Node *root, int step) {
    Node *node = new Node(root->getPt(), nullptr, root->getEnergy());

    for (auto *c : root->getChildren()) {
        simplifyTree_(c, step, 0, node);
    }
    return node;
}