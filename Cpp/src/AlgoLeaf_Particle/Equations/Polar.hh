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

    Object *generateObject(double minr, double maxr, double anglestep, double minDistance, const Point3D &center);


private:
    bool isClustering(const std::vector<Point3D*> &pts, const Point3D &p, double minDistance);


private:
    polarF formula;

//\\//\\//\\//

public: // Some Leaf Equations

    static double Cannabis(double args[]) {
        double phi = args[0];
        return (1.0 + 0.9 * cos(8.0 * phi)) * (1.0 + 0.1 * cos(24.0 * phi)) * (0.9 + 0.05 * cos(200.0 * phi)) * (1.0 + sin(phi));
    }

    static double JapaneseMarple(double args[]) {
        double phi = args[0];
        return (1.0 + sin(phi)) * (1.0 + 0.3 * cos(8.0 * phi)) * (1.0 + 0.1 * cos(24.0 * phi));
    }

};


#endif //OBJPARSER_POLAR_HH
