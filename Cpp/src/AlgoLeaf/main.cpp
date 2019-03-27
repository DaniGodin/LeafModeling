#include <iostream>

#include "leaf_object.hh"
#include "particle_object.hh"
#include "gen_random.hh"


int main() {

    std::vector<particles::Particle > p_list = gen_rand::gen_triangle(Point3D(-3, 0, 0), Point3D(0, 6, 0), Point3D(3, 0, 0), 10);

    particles::Particle_set p_set = particles::Particle_set(p_list, Point3D(0,0,0));


    //std::cout << p_set;

    for (int i = 0; i < 30; i++ ) {
        p_set.move_particles(0.1, 1, 2, 0.1);
    }
    //std::cout << "after one iteration";

    //std::cout << p_set;

    

    return 0;
}