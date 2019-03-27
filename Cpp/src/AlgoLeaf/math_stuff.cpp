//
// Created by dany on 24/03/19.
//

#include <cmath>
#include <algorithm>
#include "math_stuff.hh"


namespace math {

    Point3D get_translation(Point3D p, Vector3D dir, float stepsize){


        double x = p.getX() + stepsize * dir.getX();
        double y = p.getY() + stepsize * dir.getY();
        double z = p.getZ() + stepsize * dir.getZ();

        return Point3D(x, y , z);


    }


    Vector3D compute_dir(Vector3D dir_t, Vector3D dir_n, float weight_n, float weight_t){

        double x = (dir_t.getX() * weight_t + dir_n.getX() * weight_n) / (weight_t + weight_n);
        double y = (dir_t.getY() * weight_t + dir_n.getY() * weight_n) / (weight_t + weight_n);
        double z = (dir_t.getZ() * weight_t + dir_n.getZ() * weight_n) / (weight_t + weight_n);
        double norme = sqrt(x*x + y*y + z*z);

        return Vector3D(x / norme, y / norme, z / norme);


    }


    Vector3D get_unit_vector(Point3D p1, Point3D p2){

        double x = p2.getX() - p1.getX();
        double y = p2.getY() - p1.getY();
        double z = p2.getZ() - p1.getZ();



        double norme = sqrt(x*x + y*y + z*z);

        return Vector3D(x / norme, y / norme, z / norme);


    }

    double get_distance(const Point3D& a,const  Point3D& b){

        return sqrt(pow(b.getX() - a.getX(), 2) + pow(b.getY() - a.getY(), 2) + pow(b.getZ() - a.getZ(), 2));
    }


    unsigned int get_neighbour(particles::Particle p, std::vector<particles::Particle> vec){


        unsigned int p_index = std::distance(vec.begin(), std::find(vec.begin(), vec.end(), p));

        unsigned int min_index = p_index + 1 == vec.size() ? p_index - 1 : p_index + 1;

        for (unsigned int i = 0; i < vec.size(); i++){
            if (i != p_index && get_distance(p.position, vec[i].position) < get_distance(p, vec[min_index].position))
                min_index = i;
        }

        return min_index;

    }


    double get_distance(particles::Particle p1, particles::Particle p2) {

        double x = p2.position.getX() - p1.position.getX();
        double y = p2.position.getY() - p1.position.getY();
        double z = p2.position.getZ() - p1.position.getZ();

        return sqrt(x*x + y*y + z*z);
    }

    Point3D merge_pos(particles::Particle p1, particles::Particle p2){

        double x = (p1.position.getX() + p2.position.getX()) / 2;
        double y = (p1.position.getY() + p2.position.getY()) / 2;
        double z = (p1.position.getZ() + p2.position.getZ()) / 2;

        return Point3D(x, y , z);

    }




}

