//
// Created by revetoon on 3/26/19.
//

#ifndef OBJPARSER_TREETRANSLATOR_HH
#define OBJPARSER_TREETRANSLATOR_HH


#include "../Obj/Object.hh"
#include "Node.hh"
#include "../Obj/Meshes/Cylinder.hh"

class TreeTranslator {
public:
    enum class GENTYPE {
        line,
        cylinder
    };

public:

    std::vector<Object> generate(Node *root, std::string name, GENTYPE genType);


private:
    void genTreeO(Node *n, Object &o, long rootIndex);

    void genTreeCyl(Node *n, const std::string &name, std::vector<Object> &objs, const Cylinder &parentCyl);


private:


};


#endif //OBJPARSER_TREETRANSLATOR_HH
