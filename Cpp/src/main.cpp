
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Examples.hh"

int main() {
    std::srand(std::time(nullptr));

    Examples::parametricExample();
//    Examples::treeExample();
//    Examples::algoLeafExample();
//    Examples::parseFileExample();
//    Examples::leafGrowthExample();
//    Examples::lSystemExample();
//    Examples::cylinderExample();
    return 0;
}