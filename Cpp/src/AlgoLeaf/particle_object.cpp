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

        out << "position: " << std::endl << p.position;

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


    unsigned int Particle_set::get_closest(particles::Particle p) {

        unsigned int closest =  math::get_neighbour(p, particles);
        return closest;
    }


    bool Particle_set::move_particles(float stepsize, float weight_n, float weight_t, float merge_dist) {

        std::cout << "number of particles: " << particles.size() << std::endl;
        if (particles.size() < 2)
            return false;

        for (auto &p : particles){

            unsigned int closest = get_closest(p);
            if (math::get_distance(p, particles[closest]) < merge_dist){
                p.last_venation = algoLeaf::venationPoint(math::merge_pos(p, particles[closest]), {&p.last_venation, &particles[closest].last_venation});
                particles.erase(particles.begin() + closest);
            } else {
                Vector3D dir_closer = math::get_unit_vector(p.position, particles[closest].position);
                p.move(dir_closer, stepsize, weight_n, weight_t);
            }
        }

        init_vector();
        return true;
    }


    std::vector<algoLeaf::venationPoint* > Particle_set::get_venations() {

        std::vector<algoLeaf::venationPoint* > first_venations = {};
        for (auto &p : particles){
            first_venations.push_back(&p.last_venation);
        }

        return first_venations;

    }

    std::ostream& operator<<(std::ostream& out, Particle_set& p_set){

        for (auto &p : p_set.particles){

            out << p << std::endl;

        }
    }




}

