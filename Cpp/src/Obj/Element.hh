//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_ELEMENT_HH
#define OBJPARSER_ELEMENT_HH

#include <tuple>
#include "Point3D.hh"
#include "Texture2D.hh"
#include "Point2D.hh"
#include "Vector3D.hh"

typedef std::tuple<int, Point3D*> Point3D_i;
typedef std::tuple<int, Texture2D*> Texture2D_i;
typedef std::tuple<int, Point2D*> Point2D_i;
typedef std::tuple<int, Vector3D*> Vector3D_i;

// FORWARD DECLARATION
class Object;

class Element {
//    friend class Object;

public:
    explicit Element(Object *parent);

protected:
    Object *parent;
};

#include "Object.hh"

#endif //OBJPARSER_ELEMENT_HH
