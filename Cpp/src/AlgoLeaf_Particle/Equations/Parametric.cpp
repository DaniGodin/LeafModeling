//
// Created by revetoon on 4/25/19.
//

#include <queue>
#include <cmath>
#include <climits>
#include <cfloat>
#include "Parametric.hh"
#include "../../Utils/dblutils.hh"

Parametric::Parametric(parametricF formula, double eq)
        : f1(formula), eq(eq)
{}

Parametric::Parametric(parametricF formula, double eq, double alpha)
        : f1(formula), eq(eq), alpha(alpha)
{}

Parametric::Parametric(std::function<double(Point3D, double, double, double)> formula, double eq)
        : f2(formula), eq(eq), ftype(FunctionType::FUNCTIONAL)
{}

Parametric::Parametric(std::function<double(Point3D, double, double, double)> formula, double eq, double alpha)
        :f2(formula), eq(eq), alpha(alpha), ftype(FunctionType::FUNCTIONAL)
{}

Parametric::Parametric(std::function<double(Point3D, double, double, double)> formula, double eq, double alpha, double a_x, double a_y)
        :f2(formula), eq(eq), alpha(alpha), ftype(FunctionType::FUNCTIONAL), a_x(a_x), a_y(a_y)
{}

double Parametric::calculate(double *args) {
    switch (ftype) {
        case FunctionType::TYPEDEF:
            return f1(args);
        case FunctionType::FUNCTIONAL:
            return f2(Point3D(args[0], args[1], 0), args[2], a_x, a_y);
    }
}

std::vector<int> Parametric::sortShape(const std::vector<Point3D> &pts) {
    bool done[pts.size()] = { false };
    std::vector<int> indexes_order = std::vector<int>();
    int curr = 0;
    double shortest;
    int shortest_i;
    for (int i = 0; i < pts.size(); ++i) {
        // append closest point
        indexes_order.push_back(curr);
        done[curr] = true;
        shortest = DBL_MAX;
        shortest_i = curr;
        for (int j = 0; j < pts.size(); ++j) {
            if (done[j])
                continue;

            // calc dist from last pt
            double dist = (pts[j] - pts[curr]).length();
            // found point with shorter distance to curr
            if (dist < shortest) {
                shortest = dist;
                shortest_i = j;
            }
        }
        curr = shortest_i;
    }
//    indexes_order.push_back(curr);
    return indexes_order;
}

Object *
Parametric::generateObjectOrthogonal(double xmin=-2, double xmax=2, double ymin=-2, double ymax=2, double step=0.001, double minDistance=0.1, const Point3D &center=Point3D(0, 0, 0)) {
    std::vector<Point3D> pts = std::vector<Point3D>();
    pts.push_back(center);

    //  precision for "zero"
    double precision = 0.0001;

    // calc parametric equation results in a grid
    for (double y = ymin; y < ymax; y += step) {
        for (double x = xmin; x < xmax; x += step) {
            Point3D pt = Point3D(x, y, 0);
            // calculate result
            double args[] = { pt.getX(), pt.getY(), alpha};
            double res = calculate(args);
            // if equal to 0
            if (std::fabs(res) < precision) {

                // avoid clusters of pts
                if (isClustering(pts, pt, minDistance))
                    continue;
                // push new point
                pts.push_back(pt);
            }
        }
    }

    // Order points as good as we can
    std::vector<int> order = Parametric::sortShape(pts);

    // create the object and append all the triangles
    Object *leafScheme = new Object("LeafParametric");

    leafScheme->push(pts[order[0]]);
    leafScheme->push(pts[order[1]]);
    for (int i = 2; i < order.size(); ++i) {
        leafScheme->push(pts[order[i]]);
        FaceEl f = FaceEl(leafScheme);
//        LineEl l = LineEl();
//        l.push(leafScheme.getV()[i-1], i-1);
//        l.push(leafScheme.getV()[i], i);
        f.push(leafScheme->getV()[0]);
        f.push(leafScheme->getV()[i-1]);
        f.push(leafScheme->getV()[i]);
        leafScheme->push(f);
//        leafScheme.push(l);
    }
    return leafScheme;
}

Object *
Parametric::generateObjectRadial(double radius=2.1, double step=0.01, double angleStep = 0.001, double minDistance=0.1, const Point3D &center=Point3D(0, 0, 0)) {
    std::vector<Point3D> pts = std::vector<Point3D>();
    pts.push_back(center);

    double force = 0.01;

    //  precision for "zero"
    double precision = 0.0001;

    Vector3D up = Vector3D::up();
    // calc parametric equation results in a circle
    for (double a = 0; a < 2 * M_PI; a += angleStep) {
        // direction from center with angle a
        Vector3D dir = Vector3D(
                up.getX() * std::cos(a) - up.getY() * std::sin(a),
                up.getX() * std::sin(a) + up.getY() * std::cos(a),
                0
        );
        std::vector<double> radiuses = std::vector<double>();
        for (double r = 0.0; r < radius; r += step) {


            Point3D pt = center + (dir * r);
            // calculate result
            double args[] = { pt.getX(), pt.getY(), alpha};
            double res = calculate(args);
            // if equal to 0
            if (std::fabs(res) < precision) {
                radiuses.push_back(r);
            }
        }
        if (!radiuses.empty()) {
            int idx = dblutils::argmean(radiuses);
            float add = (static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX)) * force;
            Point3D pt = center + (dir * radiuses[idx]);
            if (!isClustering(pts, pt, minDistance))
                pts.push_back(pt + (dir * add));
        }
    }

    // points are already "radially" sorted in the shape
    // generate the object
    Object *leafScheme = new Object("LeafParametric");

    leafScheme->push(pts[0]);
    leafScheme->push(pts[1]);
    for (int i = 2; i < pts.size(); ++i) {
        leafScheme->push(pts[i]);
        FaceEl f = FaceEl(leafScheme);
        f.push(leafScheme->getV()[0]);
        f.push(leafScheme->getV()[i-1]);
        f.push(leafScheme->getV()[i]);
        leafScheme->push(f);
    }
    FaceEl f = FaceEl(leafScheme);
    f.push(leafScheme->getV()[0]);
    f.push(leafScheme->getV()[pts.size() - 1]);
    f.push(leafScheme->getV()[1]);
    leafScheme->push(f);

    return leafScheme;
}

bool Parametric::isClustering(const std::vector<Point3D> &pts, const Point3D &p, double minDistance) {
    // avoid clusters of pts
    double shortest = DBL_MAX;
    for (int i = 0; i < pts.size(); ++i) {
        double dist = (pts[i] - p).length();
        if (dist < shortest)
            shortest = dist;
    }
    // if point too close to previous ones -> skip it
    return (shortest < minDistance);
}

Object *Parametric::randomizeOutline(Object *obj, double force) {
    Point3D *center = obj->getV()[0];

    float signWeight = 0.5;
    float deviation = 0;
    for (int i = 1; i < obj->getV().size() - 1; ++i) {
        Point3D *current = obj->getV()[i];
        Vector3D dir = (*current - *center);
        float sign = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) < signWeight ? 1 : -1;
        float add = (static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX)) * force;
        deviation += sign * add;
        signWeight += sign * 0.1;
        dir = dir + deviation;
        current->setX(current->getX() + dir.getX());
        current->setY(current->getY() + dir.getY());
        current->setZ(current->getZ() + dir.getZ());
    }
}
