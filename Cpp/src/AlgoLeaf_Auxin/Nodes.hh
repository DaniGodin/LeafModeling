//
// Created by dany on 25/05/19.
//

#ifndef ALGOLEAF_AUXIN_NODES_HH
#define ALGOLEAF_AUXIN_NODES_HH

#include <iostream>
#include <vector>

#include "../Obj/Point3D.hh"

namespace Nodes {

    class Auxin {

    public:

        Point3D pos;


    public:

        Auxin(Point3D position) : pos(position) {};

    };


    class VenationPoint {

    public:

        Point3D pos;


    public:

        VenationPoint(Point3D position) : pos(position){};


    };


    class VenNodePlot{

    public:

        Point3D pos;

        double radius = 0;

        std::vector<VenNodePlot > childrens;


    public:

        VenNodePlot(std::vector<VenNodePlot > child_list, Point3D position);



    };











}



#endif //ALGOLEAF_AUXIN_NODES_HH