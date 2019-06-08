//
// Created by dany on 25/05/19.
//

#include "Leaf.hh"

namespace Leaf {

    Creation::Creation(double _birth, double kd_venation, Shape::Leafshape _shape, unsigned int _dart_step,
                       unsigned int _initial, double _growth) {

        birth_distance = _birth;
        KD_venations = kd_venation;
        shape = _shape;
        dart_step = _dart_step;
        petiole = Nodes::VenationPoint(Point3D(0,0,0));
        VenationsList = {};
        growth_step = _growth;
        gen_auxin(_initial);

    };


    void Creation::run(unsigned int nb_iterations) {



        
    }


    void Creation::gen_auxin(unsigned int nb_auxins) {}

    void Creation::gen_nodes(double step) {}


    void Creation::get_closest(Nodes::AuxinPoint *a) {}

    void Creation::grow_shape() {}

    void Creation::kill_auxins() {}








}