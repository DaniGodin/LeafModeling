#include <iostream>
#include <functional>
#include <cmath>
#include "../Obj/Point3D.hh"
#include "Leafshape.hh"
#include "Leaf.hh"

void recurse_display(Nodes::VenNodePlot res, int *number){
    *number = *number+1;
    std::cout << res.pos;
    std::cout << res.childrens.size() << std::endl;

    for (auto &a: res.childrens){
        recurse_display(a, number);
    }


};


int main() {

    std::function<double(Point3D, double, double, double)> shape1 = [] (Point3D a, double g, double a_x, double a_y) {return (
            -pow(pow(g * a.getX(), 2) + pow(g * a.getY() -1, 2) - 1, 3)
            -(pow(g * a.getX(), 2) * pow(g * a.getY() -1, 3))
            );};

    std::function<double(Point3D, double, double, double)> shape2 = [] (Point3D a, double g, double a_x, double a_y) {return (
            -a_y * pow(pow(g * 2 * a_x * a.getX(), 2) + pow(g * a.getY() -1, 2) - 1, 3)
            -(pow(g * a_y * a.getX(), 2) * pow(g * a.getY(), 3))
    );};


    Shape::rectangle r1 = Shape::rectangle();
    r1.origin = Point3D(-0.7,-0.2, 0);
    r1.x_lim = 2;
    r1.y_lim = 1.4;

    Shape::rectangle r2 = Shape::rectangle();
    r2.origin = Point3D(-0.4,-0.2, 0);
    r2.x_lim = 1.7;
    r2.y_lim = 2;

    Shape::Leafshape leaf_shape1 = Shape::Leafshape(12, shape1, r1);
    Shape::Leafshape leaf_shape2 = Shape::Leafshape(12, shape2, r2, 2, 4);


    //Leaf::Creation Creation_1 = Leaf::Creation(0.08, 0.08, leaf_shape1, 75, 4, 0.02);

    Leaf::Creation Creation_2 = Leaf::Creation(0.08, 0.09, leaf_shape2, 85, 6, 0.04);

    //Creation_1.run(1700);

    Creation_2.run(1500);
    //Nodes::VenNodePlot res1 = Creation_1.get_ventree();

    Nodes::VenNodePlot res2 = Creation_2.get_ventree();



    return 0;

}