//
// Created by revetoon on 3/4/19.
//

#ifndef OBJPARSER_LOBJECT_HH
#define OBJPARSER_LOBJECT_HH


#include <vector>
#include "LNode.hh"
#include "LRuleBasic.hh"
#include "Environment.hh"

class LObject {
public:
    explicit LObject(std::vector<LNode> nodes);

    LObject(std::vector<LNode> nodes, const std::vector<LRule*> &rules);
    LObject(std::vector<LNode> nodes, const std::vector<LRule*> &rules, Environment env);

    const std::vector<LRule*> &getRules() const;

    const std::vector<LNode> &getNodes() const;

    void iterate(unsigned count);

    void print() const;

private:

    void iter();


private:
    std::vector<LRule*> rules;
    std::vector<LNode> nodes;
    Environment env = Environment();

};


#endif //OBJPARSER_LOBJECT_HH
