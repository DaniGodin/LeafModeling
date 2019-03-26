//
// Created by dany on 24/03/19.
//

#ifndef ALGOLEAF_MATH_STUFF_HH
#define ALGOLEAF_MATH_STUFF_HH

#endif //ALGOLEAF_MATH_STUFF_HH

#include "../Obj/Point3D.hh"
#include "../Obj/Vector3D.hh"
#include "particle_object.hh"



namespace math {

    Point3D get_translation(Point3D p, Vector3D dir, float stepsize);

    Vector3D compute_dir(Vector3D dir_t, Vector3D dir_n, float weight_n, float weight_t);

    Vector3D get_unit_vector(Point3D p1, Point3D p2);

    double get_distance(particles::Particle p1, particles::Particle p2);

    Point3D merge_pos(particles::Particle p1, particles::Particle p2);

}