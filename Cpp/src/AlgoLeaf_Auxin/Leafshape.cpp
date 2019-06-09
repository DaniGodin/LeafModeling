//
// Created by dany on 25/05/19.
//

#include "Leafshape.hh"
#include <random>


namespace Shape{


    Point3D Leafshape::gen_point() {

        bool find = false;
        Point3D coord;

        double x = r.origin.getX();
        double y = r.origin.getY();

        double x_lim = x + r.x_lim;
        double y_lim = y + r.y_lim;

        std::cout << "hello" << std::endl;
        while(!find){

            std::uniform_real_distribution<double> unif(0,1);
            std::default_random_engine re;
            double r1 = x + unif(re) * ( x_lim - x);
            double r2 = y + unif(re) * ( y_lim - y);
            Point3D rand = Point3D(r1, r2, 0);
            double eval_point = equation(rand, growth_size);
            std::cout << "r1: " << r1 << "   r2: " << r2 << "  eval_point: " <<eval_point << std::endl;
            if (0.05 >= eval_point && eval_point >= -0.05){

                coord = rand;
                find = true;

            }

        }
        std::cout << "found" << std::endl;

        return coord;

    }



}