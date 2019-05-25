//
// Created by revetoon on 4/22/19.
//

#ifndef OBJPARSER_LEAFGROWTH_HH
#define OBJPARSER_LEAFGROWTH_HH


#include "../../Obj/Object.hh"

class leafGrowth {

public:

//    static objectToTriangles

    static void radialgrow(Object &leaf, double rate);
private:
    static int leafCenterIndex(const Object &leaf);

};


#endif //OBJPARSER_LEAFGROWTH_HH
