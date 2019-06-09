#include <iostream>
#include <functional>
#include <cmath>
#include "../Obj/Point3D.hh"
#include "Leafshape.hh"
#include "Leaf.hh"


int main() {

    std::function<double(Point3D, double)> shape1 = [] (Point3D a, double g) {return (
            -pow(pow(g * a.getX(), 2) + pow(g * a.getY() -1, 2) - 1, 3)
            -(pow(g * a.getX(), 2) * pow(g * a.getY() -1, 3))
            );};

    Shape::rectangle r1 = Shape::rectangle();
    r1.origin = Point3D(-0.7,-0.2, 0);
    r1.x_lim = 2;
    r1.y_lim = 1.4;

    Shape::Leafshape leaf_shape1 = Shape::Leafshape(12, shape1, r1);

    Leaf::Creation Creation_1 = Leaf::Creation(0.08, 0.08, leaf_shape1, 75, 4, 0.02);

    Creation_1.run(70);


    return 0;



}