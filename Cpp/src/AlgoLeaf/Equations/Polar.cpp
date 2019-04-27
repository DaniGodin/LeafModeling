//
// Created by revetoon on 4/27/19.
//

#include <cmath>
#include <iomanip>
#include <cfloat>
#include "Polar.hh"


Polar::Polar(polarF formula)
    :formula(formula)
{}

double Polar::calculate(double *args) {
    return formula(args);
}

Object Polar::generateObject(double minr=-M_PI, double maxr=M_PI, double anglestep=0.001, double density=0.01, const Point3D &center=Point3D(0, 0, 0)) {

    Object leaf = Object();
    leaf.push(center);

    for (double i = minr; i < maxr; i += anglestep) {
        double args[] = { i };
        double r = formula(args);
        Point3D pt = Point3D(r * std::cos(i), r * std::sin(i), 0.0);
        // check if new pt is clustering
        if (isClustering(leaf.getV(), pt, density))
            continue;
        // push new pt
        leaf.push(pt);
        // create triangle
        FaceEl f = FaceEl();
        f.push(leaf.getV()[0], 0);
        f.push(leaf.getV()[leaf.getV().size() - 2], leaf.getV().size() - 2);
        f.push(leaf.getV()[leaf.getV().size() - 1], leaf.getV().size() - 1);
        leaf.push(f);
    }
    // generate last triangle
    FaceEl f = FaceEl();
    f.push(leaf.getV()[0], 0);
    f.push(leaf.getV()[1], 1);
    f.push(leaf.getV()[leaf.getV().size() - 1], leaf.getV().size() - 1);
    leaf.push(f);

    return leaf;
}

bool Polar::isClustering(const std::vector<Point3D*> &pts, const Point3D &p, double minDistance) {
    // avoid clusters of pts
    double shortest = DBL_MAX;
    for (int i = 0; i < pts.size(); ++i) {
        double dist = (*pts[i] - p).length();
        if (dist < shortest)
            shortest = dist;
    }
    // if point too close to previous ones -> skip it
    return (shortest < minDistance);
}
