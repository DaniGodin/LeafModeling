//
// Created by revetoon on 3/15/19.
//

#ifndef OBJPARSER_LNODEFUNC_HH
#define OBJPARSER_LNODEFUNC_HH


#include <vector>
#include "LNode.hh"

class LNodeFunc : public LNode {

public:
    LNodeFunc(const std::string &id);

    LNodeFunc(const LNode &other);

private:
    std::vector<std::string> parameters;
};


#endif //OBJPARSER_LNODEFUNC_HH
