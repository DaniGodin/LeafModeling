//
// Created by dany on 24/03/19.
//

#include "particle_object.hh"
#include "math_stuff.hh"

namespace particles {


    

    bool Particle::operator==(const particles::Particle &p) {
        return position == p.position;
    }


    void Particle::move(Vector3D dir_closer, float stepsize, float weight_n, float weight_t) {

        Vector3D direction = math::compute_dir(dir_to_p, dir_closer, weight_n, weight_t);
        position = math::get_translation(position, direction, stepsize);
        std::vector<algoLeaf::venationPoint* > child = {&last_venation};
        last_venation = algoLeaf::venationPoint(position, child);

    }

    std::ostream& operator<<(std::ostream& out, const Particle &p){

        out << "position" << p.position;

    }


    void Particle_set::init_vector() {

        for (auto &p : particles){

            p.dir_to_p = math::get_unit_vector(p.position, petiole);
        }

    }


    void Particle_set::init_venation() {

        for (auto &p: particles){

            p.last_venation = algoLeaf::venationPoint(p.position, {});

        }

    }


    Particle Particle_set::get_closest(particles::Particle p) {



    }


    void Particle_set::move_particles(float stepsize, float weight_n, float weight_t) {


    }


    std::vector<algoLeaf::venationPoint* > Particle_set::get_venations() {




    }




}

