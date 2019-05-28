//
// Created by dany on 25/05/19.
//

#ifndef ALGOLEAF_AUXIN_NODES_HH
#define ALGOLEAF_AUXIN_NODES_HH

#include <iostream>
#include <vector>

#include "../Obj/Point3D.hh"

namespace Nodes {


    class VenationPoint {

    public:

        Point3D pos;


    public:

        VenationPoint(Point3D position) : pos(position){};


    };


    class AuxinPoint {

    public:

        Point3D pos;
        VenationPoint closest;

    public:

        AuxinPoint(Point3D position) : pos(position), closest(VenationPoint(Point3D(0, 0, 0))){};


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