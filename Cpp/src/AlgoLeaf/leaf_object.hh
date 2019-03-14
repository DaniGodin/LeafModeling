//
// Created by dan on 13/03/19.
//

#include "../Obj/Point3D.hh"
#include "../Tree/Node.hh"

#ifndef OBJPARSER_LEAF_OBJECT_H
#define OBJPARSER_LEAF_OBJECT_H

#endif //OBJPARSER_LEAF_OBJECT_H



namespace algoLeaf {

    class venationPoint {


    public:

        venationPoint(Point3D position, Node *childrens);

        int getPhotoEnergy() const;

        void setPhotoEnergy(int photoEnergy);
        //number of photons at this point

        Node *getVen_node() const;

        void setVen_node(Node *ven_node);

    private:

        Node *ven_node = nullptr;

        int photoEnergy;

    };

    class Leaf{

    public:
        const venationPoint &getStart() const;

        void setStart(const venationPoint &start);

        int shape; // should have a proper object for the leaf shape
        Point3D petiole; //position of the node of the leaf
        venationPoint  start; // structure containing all the venations intersection points of the leaf.


    };






}