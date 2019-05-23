//
// Created by revetoon on 4/28/19.
//

#include "Color.hh"
#include <random>


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

double Color::get255R() const {
    return r * 255;
}

double Color::get255G() const {
    return g * 255;
}

double Color::get255B() const {
    return b * 255;
}

Color Color::operator-(const Color &rhs) const {
    return Color(r - rhs.r, g - rhs.g, b - rhs.b);
}

Color Color::operator+(const Color &rhs) const {
    return Color(r + rhs.r, g + rhs.g, b + rhs.b);
}

Color Color::operator+(double factor) const {
    return Color(r + factor, g + factor, b + factor);
}

Color Color::operator*(double factor) const {
    return Color(r * factor, g * factor, b * factor);
}

Color Color::operator/(double factor) const {
    return Color(r / factor, g / factor, b / factor);
}

Color Color::distord(const Color &c, int coef) {
    if (coef <= 0)
        return c;
    int i;
    // TODO FINISH
//    float r = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
    i = (std::rand()%coef)+1;
    i -= coef;
    float f = static_cast<double>(i) / 255.0;
    double r = c.r, g = c.g, b = c.b;
    r = (f + r > 1.0 ? 1.0 : (f + r < 0.0 ? 0.0 : f + r));
    g = (f + g > 1.0 ? 1.0 : (f + g < 0.0 ? 0.0 : f + g));
    b = (f + b > 1.0 ? 1.0 : (f + b < 0.0 ? 0.0 : f + b));
    return Color(r, g, b);
}
