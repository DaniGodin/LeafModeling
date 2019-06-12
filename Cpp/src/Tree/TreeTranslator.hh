//
// Created by revetoon on 3/26/19.
//

#ifndef OBJPARSER_TREETRANSLATOR_HH
#define OBJPARSER_TREETRANSLATOR_HH


#include "../Obj/Object.hh"
#include "Node.hh"
#include "../Obj/Meshes/Cylinder.hh"
#include "../Obj/Scene.hh"
#include "../AlgoLeaf_Particle/leaf_object.hh"
#include "../AlgoLeaf_Auxin/Nodes.hh"

class TreeTranslator {
public:
    enum class GENTYPE {
        line,
        cylinder
    };

public:
    TreeTranslator(Scene &scene);

    std::vector<Object*> generate(Node *root, std::string name, const Color &rootCol = Color::white(), const Color &leafCol = Color::white(), GENTYPE genType = GENTYPE::cylinder);
    std::vector<Object*> generate(algoLeaf::venationPoint *root, std::string name, int pointCount, const Color &rootCol = Color::white(), const Color &leafCol = Color::white());
    std::vector<Object*> generate(Nodes::VenNodePlot *root, std::string name, int pointCount, const Color &rootCol = Color::white(), const Color &leafCol = Color::white());

    Node *convertVenationToNode(algoLeaf::venationPoint *root, int pointCount);
    Node *convertVenNodeToNode(Nodes::VenNodePlot *root, int pointCount);

private:
    void genTreeO(Node *n, Object *o, long rootIndex);

    void genTreeCyl(Node *n, const std::string &name, std::vector<Object*> &objs, const Cylinder *parentCyl, const Color &rootCol, const Color &leafCol);

    Node *convertVenationToNode_rec(algoLeaf::venationPoint *venation, Node *parent, int pointCount);

    Node *convertVenNodeToNode_rec(Nodes::VenNodePlot *ven, Node *parent, int pointCount);

private:
    Scene &scene;

};


#endif //OBJPARSER_TREETRANSLATOR_HH
