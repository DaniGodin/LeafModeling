//
// Created by dany on 24/03/19.
//

#ifndef ALGOLEAF_GEN_RANDOM_HH
#define ALGOLEAF_GEN_RANDOM_HH

#include "particle_object.hh"
#include "../Obj/Point3D.hh"

#include <vector>


namespace gen_rand{

    std::vector<particles::Particle> gen_triangle(Point3D v1, Point3D v2, Point3D v3, unsigned int num_particle);

}
#endif //ALGOLEAF_GEN_RANDOM_HH


