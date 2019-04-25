//
// Created by revetoon on 3/2/19.
//

#include "Node.hh"

Node::Node() = default;

Node::Node(const Point3D &pt, Node *parent) : pt(std::move(pt)), parent(parent) {}

Node::Node(const Point3D &pt, Node *parent, double energy) : pt(std::move(pt)), parent(parent), energy(energy) {}

Node::Node(Node *parent) : parent(parent) {}

Node::~Node() {
//    for (Node * c : children) {
//        delete c;
//    }
}

Point3D &Node::getPt() {
    return pt;
}

std::vector<Node *> &Node::getChildren() {
    return children;
}

Node *Node::getParent() const {
    return parent;
}

void Node::setParent(Node *parent) {
    Node::parent = parent;
}

double Node::getEnergy() const {
    return energy;
}
