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

        VenationPoint(){};
        VenationPoint(Point3D position) : pos(position){};



    };


    class AuxinPoint : public VenationPoint {

    public:

        VenationPoint closest;

    public:

        AuxinPoint(){};
        AuxinPoint(Point3D position) : VenationPoint(position), closest(VenationPoint(Point3D(0, 0, 0))){};


    };


    class VenNodePlot : public VenationPoint{

    public:

        double radius = 0;

        std::vector<VenNodePlot > childrens;


    public:

        VenNodePlot(){};
        VenNodePlot(std::vector<VenNodePlot > child_list, Point3D position) ;

    };











}



#endif //ALGOLEAF_AUXIN_NODES_HH