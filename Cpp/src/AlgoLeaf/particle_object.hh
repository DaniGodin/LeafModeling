//
// Created by dany on 24/03/19.
//

#ifndef ALGOLEAF_PARTICLE_OBJECT_HH
#define ALGOLEAF_PARTICLE_OBJECT_HH


#include "../Obj/Point3D.hh"
#include "../Obj/Vector3D.hh"
#include "leaf_object.hh"


namespace particles {


    class Particle {

    public:

        Point3D position;
        algoLeaf::venationPoint last_venation;
        Vector3D dir_to_p;


    public:


        Particle(Point3D pos) {
            position = pos;
            dir_to_p = Vector3D(0,0,0);
        };

        bool operator==(const Particle& p);

        void move(Vector3D dir_closer, float stepsize, float weight_n, float weight_t);




    };

    std::ostream& operator<<(std::ostream& out, const Particle& p);


    class Particle_set {


    public:

        std::vector<particles::Particle > particles;
        Point3D petiole; // coordinate of the petiole;


    public:

        Particle_set(std::vector<Particle > p, Point3D pet_coord) : particles(p), petiole(pet_coord) {
            init_venation();
            init_vector();

        };

        void init_venation();

        void init_vector();



        unsigned int get_closest(Particle p);

        bool move_particles(float stepsize, float weight_n, float weight_t, float merge_dist);


        std::vector<algoLeaf::venationPoint* > get_venations();



    };

    std::ostream& operator<<(std::ostream& out, Particle_set& p_set);

}

#endif //ALGOLEAF_PARTICLE_OBJECT_HH
