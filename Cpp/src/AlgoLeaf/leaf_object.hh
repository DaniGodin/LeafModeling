//
// Created by dan on 13/03/19.
//

#include "../Obj/Point3D.hh"
#include <iostream>
#include <vector>

#ifndef OBJPARSER_LEAF_OBJECT_H
#define OBJPARSER_LEAF_OBJECT_H





namespace algoLeaf {

    class venationPoint {


    public:

        venationPoint(){};

        venationPoint(Point3D position, std::vector<venationPoint *> childrens);

        std::ostream&operator <<(std::ostream &out);

    public:

        Point3D position;
        std::vector<venationPoint*> childrens;
        int photoEnergy;

    };


    class Leaf{

    public:

        Leaf(int shape, Point3D petiole, std::vector<venationPoint *> venations);

        std::ostream&operator <<(std::ostream &out);


    public:

        int shape; // should have a proper object for the leaf shape
        Point3D petiole; //position of the node of the leaf
        venationPoint *start; // structure containing all the venations intersection points of the leaf.


    };
}

#endif //OBJPARSER_LEAF_OBJECT_H