//
// Created by dany on 25/05/19.
//

#include <cmath>
#include "Leaf.hh"
#include "mathStuff.hh"
#include "algorithm"


namespace Leaf {

    Creation::Creation(double _birth, double kd_venation, Shape::Leafshape _shape, unsigned int _dart_step,
                       unsigned int _initial, double _growth) {

        birth_distance = _birth;
        KD_venations = kd_venation;
        shape = _shape;
        dart_step = _dart_step;
        petiole = Nodes::VenationPoint(Point3D(0,0,0));
        VenationsList[petiole] = {};
        growth_step = _growth;
        gen_auxin(_initial);

    };


    void Creation::run(unsigned int nb_iterations) {

        for (int i = 0; i < nb_iterations; i++){
            //std::cout << AuxinsList.size() << std::endl;
            gen_nodes(0.003); //find better way
            kill_auxins();
            gen_auxin(dart_step);
            grow_shape(i);


        }

    }


    void Creation::gen_auxin(unsigned int nb_auxins) {

        for (int i = 0; i < nb_auxins; i++){


            Point3D rand_coord = shape.gen_point();

            Nodes::AuxinPoint Aux = Nodes::AuxinPoint(rand_coord);

            bool to_append = true;

            for (auto &a : AuxinsList){
                if (Math::get_distance(a, Aux) < birth_distance) {
//                    std::cout << "Disqualified 1" << std::endl;
                    to_append = false;
                    break;
                }

            }

            for (auto &v : VenationsList){
                if (Math::get_distance(v.first, Aux) < birth_distance){
                    to_append = false;
                    break;

                }
            }


            if (to_append){
//                std::cout << "to_append" << std::endl;
                get_closest(&Aux);
                AuxinsList.push_back(Aux);
            }

        }
    }



    void Creation::gen_nodes(double step) {

        std::vector<Nodes::VenationPoint > new_nodes = {};
        for (auto &ven : VenationsList){
            std::vector<Nodes::AuxinPoint* > aux;
            for (auto &a : AuxinsList){
                if (a.closest.pos == ven.first.pos){
                    aux.push_back(&a);
                }

            }
            if (!aux.empty()){
                Nodes::VenationPoint new_ven = Math::get_newNode(ven.first, aux, step);
//                std::cout <<"generating" << std::endl;
                for (auto &a : aux){
                    if (Math::get_distance(*a, new_ven) < Math::get_distance(*a, ven.first)){
                        a->closest = new_ven;
                    }
                }
                new_nodes.push_back(new_ven);
                ven.second.push_back(new_ven);
            }
        }

        for (auto &node : new_nodes){
            VenationsList[node] = {};
        }
    }


    void Creation::get_closest(Nodes::AuxinPoint *a) {
        std::vector<Nodes::VenationPoint > key_list = {};

        for (auto &pairs : VenationsList){
            key_list.push_back(pairs.first);
        }
//        std::cout << "searching for nearest" << std::endl;

        unsigned int min_index = 0;
        for (unsigned int i = 0; i < key_list.size(); i++){
            if (Math::get_distance(key_list[i], *a) < Math::get_distance(*a, key_list[min_index]))
                min_index = i;
        }
        a->closest = key_list[min_index];
    }




    void Creation::grow_shape(unsigned int i) {

        if (shape.growth_size > 1.255)
            shape.growth_size -= pow(growth_step + shape.growth_size/100, 2);
        if (shape.growth_x > 1)
            shape.growth_x -= pow(growth_step + i/1000, 2);
        if (shape.growth_y > 1)
            shape.growth_y -= pow(growth_step + i/1000, 2);

    }

    void Creation::kill_auxins(){
        std::vector<Nodes::AuxinPoint > to_remove;
        for (auto &aux : AuxinsList){
            if (Math::get_distance(aux, aux.closest) < KD_venations)
                to_remove.push_back(aux);
        }
        for (auto &aux : to_remove){
            AuxinsList.erase(std::find(AuxinsList.begin(), AuxinsList.end(), aux));
        }
    }



    Nodes::VenNodePlot Creation::get_ventree() {
        Nodes::VenationPoint root = petiole;
        std::vector<Nodes::VenationPoint > childrens = VenationsList[root];
        std::vector<Nodes::VenNodePlot > venc_c = {};
        for (auto &c : childrens){
            venc_c.push_back(build_tree(c));
        }
        return Nodes::VenNodePlot(venc_c, root.pos);
    }


    Nodes::VenNodePlot Creation::build_tree(Nodes::VenationPoint c) {
        std::vector<Nodes::VenationPoint > childrens = VenationsList[c];
        if (childrens.empty())
            return Nodes::VenNodePlot({}, c.pos);
        else {
            std::vector<Nodes::VenNodePlot > ven_c;
            for (auto &c: childrens){
                ven_c.push_back(build_tree(c));
            }
            return Nodes::VenNodePlot(ven_c, c.pos);

        };
    }

}