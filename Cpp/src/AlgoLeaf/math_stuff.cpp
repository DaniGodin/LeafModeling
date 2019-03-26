//
// Created by dany on 24/03/19.
//

#include <cmath>
#include "math_stuff.hh"


namespace math {

    Point3D math::get_translation(Point3D p, Vector3D dir, float stepsize){


        double x = p.getX() + stepsize * dir.getX();
        double y = p.getY() + stepsize * dir.getY();
        double z = p.getZ() + stepsize * dir.getZ();

        return Point3D(x, y , z);


    }


    Vector3D math::compute_dir(Vector3D dir_t, Vector3D dir_n, float weight_n, float weight_t){

        double x = (dir_t.getX() * weight_t + dir_n.getX() * weight_n) / (weight_t + weight_n);
        double y = (dir_t.getY() * weight_t + dir_n.getY() * weight_n) / (weight_t + weight_n);
        double z = (dir_t.getY() * weight_t + dir_n.getY() * weight_n) / (weight_t + weight_n);
        double norme = sqrt(x*x + y*y + z*z);

        return Vector3D(x / norme, y / norme, z / norme);


    }


    Vector3D math::get_unit_vector(Point3D p1, Point3D p2){

        double x = p2.getX() - p1.getX();
        double y = p2.getY() - p1.getY();
        double z = p2.getZ() - p1.getZ();

        double norme = sqrt(x*x + y*y + z*z);

        return Vector3D(x / norme, y / norme, z / norme);


    }

    /*
    particles::Particle math::get_neighbour(particles::Particle p, particles::Particle_set set){



    }
    */

    double math::get_distance(particles::Particle p1, particles::Particle p2) {

        double x = p2.position.getX() - p1.position.getX();
        double y = p2.position.getY() - p1.position.getY();
        double z = p2.position.getZ() - p1.position.getZ();

        return sqrt(x*x + y*y + z*z);
    }

    Point3D math::merge_pos(particles::Particle p1, particles::Particle p2){

        double x = (p1.position.getX() + p2.position.getX()) / 2;
        double y = (p1.position.getY() + p2.position.getY()) / 2;
        double z = (p1.position.getZ() + p2.position.getZ()) / 2;

        return Point3D(x, y , z);

    }




}

