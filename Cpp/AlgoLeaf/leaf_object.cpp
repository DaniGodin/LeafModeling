//
// Created by dan on 13/03/19.
//

#include "leaf_object.hh"

namespace algoLeaf {


    int venationPoint::getPhotoEnergy() const {
        return photoEnergy;
    }

    void venationPoint::setPhotoEnergy(int photoEnergy) {
        venationPoint::photoEnergy = photoEnergy;
    }

    Node *venationPoint::getVen_node() const {
        return ven_node;
    }

    void venationPoint::setVen_node(Node *ven_node) {
        venationPoint::ven_node = ven_node;
    }

    const venationPoint &Leaf::getStart() const {
        return start;
    }

    void Leaf::setStart(const venationPoint &start) {
        Leaf::start = start;
    }
}
