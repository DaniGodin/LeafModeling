//
// Created by revetoon on 3/4/19.
//

#ifndef OBJPARSER_LTRANSLATOR_HH
#define OBJPARSER_LTRANSLATOR_HH


#include <vector>
#include "../Obj/Point3D.hh"
#include "../Obj/Vector3D.hh"
#include "../Obj/Object.hh"
#include "LObject.hh"

class LTranslator {
public:
    virtual Object *transcript(LObject lobj) = 0;

};


#endif //OBJPARSER_LTRANSLATOR_HH
