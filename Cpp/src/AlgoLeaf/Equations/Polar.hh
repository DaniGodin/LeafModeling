//
// Created by revetoon on 4/27/19.
//

#ifndef OBJPARSER_POLAR_HH
#define OBJPARSER_POLAR_HH


#include "../../Obj/Object.hh"

class Polar {
    // args are expected as follow:
    // args[0] : phi
    // ...
    typedef double(*polarF)(double args[]);

public:
    Polar(polarF formula);

    double calculate(double args[]);

    Object generateObject(double minr, double maxr, double anglestep, double density, const Point3D &center);

private:
    bool isClustering(const std::vector<Point3D*> &pts, const Point3D &p, double minDistance);


private:
    polarF formula;

};


#endif //OBJPARSER_POLAR_HH
