//
// Created by dany on 25/05/19.
//

#ifndef ALGOLEAF_AUXIN_LEAF_HH
#define ALGOLEAF_AUXIN_LEAF_HH

#include <map>
#include <vector>
#include "Nodes.hh"
#include "Leafshape.hh"


namespace Leaf {

    class Creation {

    public:

        //Kind of graph structure
        std::map<Nodes::VenationPoint, std::vector<Nodes::VenationPoint>> VenationsList;
        //Auxinlist
        std::vector<Nodes::AuxinPoint> AuxinsList;
        //shape of the leaf
        Shape::Leafshape shape;
        double birth_distance;
        double KD_venations;
        unsigned int dart_step;
        Nodes::VenationPoint petiole;
        double growth_step;

    public:

        Creation(double _birth, double kd_venation, Shape::Leafshape _shape, unsigned int _dart_step, Nodes::VenationPoint _initial,
                 double _growth);


        void run(unsigned int nb_iterations);

        void get_closest(Nodes::AuxinPoint* a);

        void gen_nodes(double step);

        void gen_auxin();

        void kill_auxins();

        void grow_shape();


    };





}



#endif //ALGOLEAF_AUXIN_LEAF_HH