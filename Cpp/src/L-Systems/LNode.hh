//
// Created by revetoon on 3/4/19.
//

#ifndef OBJPARSER_LNODE_HH
#define OBJPARSER_LNODE_HH

#include <string>

class LNode {

public:
    explicit LNode(const std::string &id);

    LNode(const LNode& other) { // copy constructor
        id = other.id;
    }

    std::string getId() const;

    bool operator==(const LNode &rhs) const;

    bool operator!=(const LNode &rhs) const;

private:
    std::string id;
};

#endif //OBJPARSER_LNODE_HH
