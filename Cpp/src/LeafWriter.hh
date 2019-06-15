//
// Created by revetoon on 6/15/19.
//

#ifndef OBJPARSER_LEAFWRITER_HH
#define OBJPARSER_LEAFWRITER_HH


#include <string>
#include "Utils/Color.hh"
#include "Obj/Point3D.hh"

namespace LeafWriter {

    void catalpa(std::string outputName, int auxinsIterations = 1700, int simplify = 6);

    void tobacco(std::string outputName, int auxinsIterations = 1700, int simplify = 6);

    void custom(std::string outputName, std::function<double(Point3D, double)> fun,
                int auxinsIterations, int simplify,
                const Point3D &center,
                double parameticStep, double parameticAngleStep,
                const Color &veins1, const Color &veins2,
                const Color &leaf1, const Color &leaf2);

};


#endif //OBJPARSER_LEAFWRITER_HH
