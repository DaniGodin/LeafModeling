//
// Created by revetoon on 4/28/19.
//

#include "Color.hh"

Color::Color(double r, double g, double b) : r(r), g(g), b(b) {}

Color::Color(double rgb)
    :r(rgb), g(rgb), b(rgb)
{}

double Color::getR() const {
    return r;
}

double Color::getG() const {
    return g;
}

double Color::getB() const {
    return b;
}
