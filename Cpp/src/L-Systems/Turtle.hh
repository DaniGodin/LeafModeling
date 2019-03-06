//
// Created by revetoon on 3/6/19.
//

#ifndef OBJPARSER_TURTLE_HH
#define OBJPARSER_TURTLE_HH


#include "../Obj/Vector3D.hh"
#include "../Obj/Point3D.hh"

class Turtle {
public:
    explicit Turtle(const Point3D &curr, int currVIndex);

    Turtle();

public:
    Vector3D tHeading = Vector3D(1, 0, 0);
    Vector3D tLeft = Vector3D(0, 1, 0);
    Vector3D tUp = Vector3D(0, 0, 1);
    Point3D curr;
    int currVIndex = 0;
    int oldVIndex = 0;
};


#endif //OBJPARSER_TURTLE_HH
