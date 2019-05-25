//
// Created by dany on 24/03/19.
//

#include <cmath>
#include <random>
#include "gen_random.hh"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);


namespace gen_rand{


    std::vector<particles::Particle> gen_triangle(Point3D v1, Point3D v2, Point3D v3, unsigned int num_particle){

        std::vector<particles:: Particle> p_list = {};

        for (int i = 0; i < num_particle; i++){

            double r1 = dis(gen);
            double r2 = dis(gen);

            double x_rand = (1 - pow(r1, 2)) * v1.getX() + pow(r1, 2) * (1 - r2) * v2.getX() + v3.getX() * r2 * pow(r1, 2);
            double y_rand = (1 - pow(r1, 2)) * v1.getY() + pow(r1, 2) * (1 - r2) * v2.getY() + v3.getY() * r2 * pow(r1, 2);

            particles::Particle P = particles::Particle(Point3D(x_rand, y_rand, 0));
            p_list.push_back(P);

        }

        return p_list;

    }



}