//
// Created by dan on 13/03/19.
//

#include "leaf_object.hh"

namespace algoLeaf {


    int compute_energy(std::vector<venationPoint *> childrens) {
        int energy = 0;
        for (auto c : childrens){

            energy += c->photoEnergy;
        }

        return energy > 0 ? energy : 1;
    }



    venationPoint::venationPoint(Point3D position, std::vector<venationPoint *> childrens) {

        venationPoint::photoEnergy = compute_energy(childrens);
        venationPoint::childrens = childrens;
        venationPoint::position = position;

    }


    Leaf::Leaf(int shape, Point3D petiole, std::vector<venationPoint *> venations) {
        Leaf::shape = shape;
        Leaf::start = new venationPoint(petiole, venations);
        Leaf::petiole = petiole;

    }

}
