//
// Created by revetoon on 3/1/19.
//

#include <functional>
#include "Texture2D.hh"

double Texture2D::getU() const {
    return u;
}

double Texture2D::getV() const {
    return v;
}

double Texture2D::getW() const {
    return w;
}

bool Texture2D::operator==(const Texture2D &rhs) const {
    return u == rhs.u &&
           v == rhs.v &&
           w == rhs.w;
}

bool Texture2D::operator!=(const Texture2D &rhs) const {
    return !(rhs == *this);
}

std::size_t Texture2D::hash::operator()(const Texture2D &p) const {
    auto h1 = std::hash<double>{}(p.u);
    auto h2 = std::hash<double>{}(p.v);
    auto h3 = std::hash<double>{}(p.w);

    return h1 ^ h2 ^ h3;
}
