//
// Created by revetoon on 4/27/19.
//

#include <cmath>
#include "dblutils.hh"

double dblutils::trunc(double num, double dec) {
    double p = pow(10, dec);
    return std::trunc(num * p) / p;
}

double dblutils::sum(const std::vector<double> &vect) {
    double sum = 0;
    for (double d : vect)
        sum += d;
    return sum;
}


double dblutils::mean(const std::vector<double> &vect) {
    return sum(vect) / vect.size();
}

int dblutils::argmean(const std::vector<double> &vect) {
    double mean = dblutils::mean(vect);
    for (int i = 0; i < vect.size(); ++i)
        if (vect[i] >= mean)
            return i;
}
