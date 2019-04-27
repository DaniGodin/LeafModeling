//
// Created by revetoon on 4/27/19.
//

#include <cmath>
#include "dblutils.hh"

double dblutils::trunc(double num, double dec) {
    double p = pow(10, dec);
    return std::trunc(num * p) / p;
}

