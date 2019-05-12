
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Examples.hh"
#include "Chronometer.hh"

int main() {
    std::srand(std::time(nullptr));

    {
        // start a chronometer
        Chronometer c = Chronometer();

//        Examples::parametricExample();
//        Examples::polarExample();
//        Examples::treeExample();
        Examples::genJpeg();
//        Examples::algoLeafExample();
//        Examples::parseFileExample();
//        Examples::leafGrowthExample();
//        Examples::lSystemExample();
//        Examples::cylinderExample();
    }
    return 0;
}