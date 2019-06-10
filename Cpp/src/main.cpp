
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Examples.hh"
#include "Utils/Chronometer.hh"

int main() {
    std::srand(std::time(nullptr));
    {
        // start a chronometer
        Chronometer c = Chronometer();

//        Examples::parametricExample();
//        Examples::polarExample();
//        Examples::treeExample();
//        Examples::genJpeg();
//        Examples::rasterizeExample();
        Examples::algoLeafExample();
//        Examples::cylindersTexture();
//        Examples::parseFileExample();
//        Examples::leafGrowthExample();
//        Examples::lSystemExample();
//        Examples::cylinderExample();
//        Examples::morphologyExample();
    }

    return 0;
}