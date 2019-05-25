#include <iostream>

#include "leaf_object.hh"
#include "particle_object.hh"
#include "gen_random.hh"

void display_venations(algoLeaf::venationPoint v, int recursion_depth){
    if( recursion_depth < 30) {
        std::cout << v.position << std::endl;
        std::cout << "Recursion: " << recursion_depth << std::endl;
        for (auto &c : v.childrens) {
            display_venations(*c, recursion_depth + 1);
        }
    }
}

int main() {

    std::vector<particles::Particle > p_list = gen_rand::gen_triangle(Point3D(-3, 0, 0), Point3D(0, 6, 0), Point3D(3, 0, 0), 3);

    particles::Particle_set p_set = particles::Particle_set(p_list, Point3D(0,0,0));


    //std::cout << p_set;
    bool moving = true;
    while (moving ) {
        moving = p_set.move_particles(0.1, 1, 2, 0.1);
    }
    //std::cout << "after one iteration";

    //std::cout << p_set;
    std::vector<algoLeaf::venationPoint* > v = p_set.get_venations();
    algoLeaf::venationPoint *root = v[0];
    display_venations(*root, 0);

    
    return 0;
}