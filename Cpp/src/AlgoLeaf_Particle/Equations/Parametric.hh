//
// Created by revetoon on 4/25/19.
//

#ifndef OBJPARSER_PARAMETRIC_HH
#define OBJPARSER_PARAMETRIC_HH


#include <functional>
#include "../../Obj/Object.hh"

class Parametric {

    // args are expected as follow:
    // args[0] : x
    // args[1] : y
    // args[2] : alpha
    typedef double(*parametricF)(double args[]);

    enum class FunctionType {
        TYPEDEF = 0,
        FUNCTIONAL
    };


public:
    Parametric(parametricF formula, double eq);
    Parametric(parametricF formula, double eq, double alpha);
    Parametric(std::function<double(Point3D, double)> formula, double eq);
    Parametric(std::function<double(Point3D, double)> formula, double eq, double alpha);

    double calculate(double args[]);

    Object *generateObjectOrthogonal(double xmin, double xmax, double ymin, double ymax, double step, double minDistance, const Point3D &center);
    Object *generateObjectRadial(double radius, double step, double anglestep, double minDistance, const Point3D &center);

    static Object *randomizeOutline(Object *obj, double force);

private:
    std::vector<int> sortShape(const std::vector<Point3D> &pts);

    Point3D searchPointRadial();

    bool isClustering(const std::vector<Point3D> &pts, const Point3D &p, double minDistance);

private:
    parametricF f1;
    std::function<double(Point3D, double)> f2;
    double eq = 0.0;
    double alpha = 1.0;
    FunctionType ftype = FunctionType::TYPEDEF;


};


#endif //OBJPARSER_PARAMETRIC_HH
