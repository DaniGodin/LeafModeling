
#include <iostream>
#include <ctime>
#include <functional>
#include <cmath>
#include "LeafWriter.hh"
#include "Utils/Chronometer.hh"
#include "Obj/Point3D.hh"

int main() {
    std::srand(std::time(nullptr));
    {
        // start a chronometer
        Chronometer c = Chronometer();
//        LeafWriter::catalpa("LEAF", 1700, 10);
        std::function<double(Point3D, double)> customParametric = [] (Point3D a, double g) {return (
                -pow(pow(g * a.getX(), 2) + pow(g * a.getY() - 0.5, 2), 3) + 0.05 + pow(g * a.getX(), 2) * pow(g * a.getY() + 4, 2)
        );};

        LeafWriter::custom("LEAFCUSTOM", customParametric, 1200, 8, Point3D(0,0.1,0), 0.0001, 0.0001, Color::black(), Color::black(), Color::white(), Color::white());

//        Examples::parametricExample();
//        Examples::parametricExample();
//        Examples::polarExample();
//        Examples::treeExample();
//        Examples::genJpeg();
//        Examples::rasterizeExample();
//        Examples::parametricExample();
//        Examples::algoLeaf2Example();
//        Examples::algoLeafExample();
//        Examples::parseFileExample();
//        Examples::leafGrowthExample();
//        Examples::lSystemExample();
//        Examples::cylinderExample();
//        Examples::cylindersTexture();
//        Examples::morphologyExample();
    }

    return 0;
}