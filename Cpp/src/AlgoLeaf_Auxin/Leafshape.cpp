//
// Created by dany on 25/05/19.
//

#include "Leafshape.hh"
#include <random>


namespace Shape{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    Point3D Leafshape::gen_point() {

        bool find = false;
        Point3D coord;

        double x = r.origin.getX();
        double y = r.origin.getY();

        double x_lim = x + r.x_lim;
        double y_lim = y + r.y_lim;

        while(!find){

            double r1 = x + dis(gen) * ( x_lim - x);
            double r2 = y + dis(gen) * ( y_lim - y);
            Point3D rand = Point3D(r1, r2, 0);
            double eval_point = equation(rand, growth_size, growth_x, growth_y);
            if (0.02 >= eval_point && eval_point >= -0.01){
                coord = rand;
                find = true;

            }

        }
        return coord;

    }



}