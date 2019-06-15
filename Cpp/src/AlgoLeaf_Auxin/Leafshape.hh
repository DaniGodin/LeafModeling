//
// Created by dany on 25/05/19.
//

#ifndef ALGOLEAF_AUXIN_LEAFSHAPE_HH
#define ALGOLEAF_AUXIN_LEAFSHAPE_HH


#include "../Obj/Point3D.hh"
#include "functional"




namespace  Shape {


    struct rectangle {

        Point3D origin;
        double x_lim;
        double y_lim;


    };

    class Leafshape {

    public:

        double growth_x;
        double growth_y;
        double growth_size = 0;
        rectangle r; // where to project points
        std::function<double(Point3D, double, double, double)> equation;

    public:

        Leafshape(){};
        Leafshape(double _growth, std::function<double(Point3D, double, double, double)> _equ, rectangle _r, double _growth_x = 1, double _growth_y = 1) :
                                                                                                growth_size(_growth),
                                                                                               r(_r),
                                                                                               equation(_equ),
                                                                                               growth_x(_growth_x),
                                                                                               growth_y(_growth_y)
                                                                                               {};

        Point3D gen_point();


    };

}
#endif //ALGOLEAF_AUXIN_LEAFSHAPE_HH
