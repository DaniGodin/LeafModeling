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
