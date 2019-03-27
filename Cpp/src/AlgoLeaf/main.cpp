#include <iostream>

#include "leaf_object.hh"
#include "particle_object.hh"


int main() {

    particles::Particle p1 = particles::Particle(Point3D(1, 1, 0));
    particles::Particle p2 = particles::Particle(Point3D(-1, 1, 0));
    particles::Particle p3 = particles::Particle(Point3D(0, 1.5, 0));


    particles::Particle_set p_set = particles::Particle_set({p1,p3,p2}, Point3D(0,0,0));


    std::cout << p_set;

    for (int i = 0; i < 15; i ++ ) {
        p_set.move_particles(0.1, 1, 2, 0.1);
    }
    std::cout << "after one iteration";

    std::cout << p_set;



    return 0;
}