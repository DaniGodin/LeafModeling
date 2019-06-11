//
// Created by dany on 25/05/19.
//

#include <cmath>
#include "mathStuff.hh"


namespace Math {

    double get_distance(Nodes::VenationPoint v1, Nodes::VenationPoint v2) {

        float x = v1.pos.getX() - v2.pos.getX();
        float y = v1.pos.getY() - v2.pos.getY();

        return sqrt(pow(x, 2 ) + pow(y, 2));


    }


    Nodes::VenationPoint get_newNode(Nodes::VenationPoint parent_node,
                                           std::vector<Nodes::AuxinPoint* > auxin_list, double step) {

        Vector3D dir = Vector3D(0, 0, 0);
        for (auto &aux : auxin_list){

            Vector3D a_dir = aux->pos - parent_node.pos;
            a_dir.normalize();
            dir = Vector3D(dir.getX() + a_dir.getX(), dir.getY() + a_dir.getY(), 0);

        }

        dir.normalize();
        dir = dir * step;
        return Nodes::VenationPoint(parent_node.pos + dir);


    }


}