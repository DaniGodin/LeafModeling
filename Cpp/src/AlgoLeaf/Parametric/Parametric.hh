//
// Created by revetoon on 4/25/19.
//

#ifndef OBJPARSER_PARAMETRIC_HH
#define OBJPARSER_PARAMETRIC_HH


#include "../../Obj/Object.hh"

class Parametric {
    typedef double(*parametricF)(double args[]);


public:
    Parametric(parametricF formula, double eq);

    double calculate(double args[]);

    Object generateObjectOrthogonal(double xmin, double xmax, double ymin, double ymax, double step, double density, const Point3D &center);
    Object generateObjectRadial(double radius, double step, double anglestep, double density, const Point3D &center);

private:
    std::vector<int> sortShape(const std::vector<Point3D> &pts);

    Point3D searchPointRadial();

    bool isClustering(const std::vector<Point3D> &pts, const Point3D &p, double minDistance);

private:
    parametricF formula;
    double eq = 0.0;

};


#endif //OBJPARSER_PARAMETRIC_HH
