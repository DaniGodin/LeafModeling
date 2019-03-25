//
// Created by revetoon on 3/2/19.
//

#ifndef OBJPARSER_NODE_HH
#define OBJPARSER_NODE_HH


#include <vector>
#include "../Obj/Point3D.hh"

class Node {
public:
    Node(Node *parent);

    Node(const Point3D &pt, Node *parent);

    Node();

    Point3D &getPt();

    std::vector<Node *> &getChildren();

    Node *getParent() const;

    void setParent(Node *parent);


private:
    Point3D pt;
    std::vector<Node *> children;
    Node *parent = nullptr;
    double energy;

};


#endif //OBJPARSER_NODE_HH
