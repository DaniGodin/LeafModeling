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

        double growth_size = 0;
        rectangle r; // where to project points
        std::function<double(Point3D, double)> equation;

    public:

        Leafshape(){};
        Leafshape(double _growth, std::function<double(Point3D, double)> _equ, rectangle _r) : growth_size(_growth),
                                                                                               r(_r),
                                                                                               equation(_equ) {};

        Point3D gen_point();


    };

}
#endif //ALGOLEAF_AUXIN_LEAFSHAPE_HH
