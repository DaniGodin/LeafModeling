//
// Created by revetoon on 4/27/19.
//

#ifndef OBJPARSER_DBLUTILS_HH
#define OBJPARSER_DBLUTILS_HH

#include <vector>

class dblutils {
public:

    static double trunc(double num, double dec);

    static double sum(const std::vector<double> &vect);
    static double mean(const std::vector<double> &vect);
    static int argmean(const std::vector<double> &vect);
};


#endif //OBJPARSER_DBLUTILS_HH
