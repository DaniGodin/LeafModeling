//
// Created by dany on 25/05/19.
//

#ifndef ALGOLEAF_AUXIN_MATHSTUFF_HH
#define ALGOLEAF_AUXIN_MATHSTUFF_HH


#include "Nodes.hh"

namespace Math {

    double get_distance(Nodes::VenationPoint v1, Nodes::VenationPoint v2);

    Nodes::VenationPoint get_newNode(Nodes::VenationPoint parent_node, std::vector<Nodes::AuxinPoint* > auxin_list,
                                     double step);



}

#endif //ALGOLEAF_AUXIN_MATHSTUFF_HH
