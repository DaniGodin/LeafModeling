//
// Created by revetoon on 3/26/19.
//

#ifndef OBJPARSER_TREETRANSLATOR_HH
#define OBJPARSER_TREETRANSLATOR_HH


#include "../Obj/Object.hh"
#include "Node.hh"
#include "../Obj/Meshes/Cylinder.hh"
#include "../AlgoLeaf/leaf_object.hh"

class TreeTranslator {
public:
    enum class GENTYPE {
        line,
        cylinder
    };

public:

    std::vector<Object*> generate(Node *root, std::string name, GENTYPE genType);
    std::vector<Object*> generate(algoLeaf::venationPoint *root, std::string name, int pointCount, GENTYPE genType);

    Node *convertVenationToNode(algoLeaf::venationPoint *root, int pointCount);

private:
    void genTreeO(Node *n, Object *o, long rootIndex);

    void genTreeCyl(Node *n, const std::string &name, std::vector<Object*> &objs, const Cylinder *parentCyl);

    Node *convertVenationToNode_rec(algoLeaf::venationPoint *venation, Node *parent, int pointCount);

private:


};


#endif //OBJPARSER_TREETRANSLATOR_HH
