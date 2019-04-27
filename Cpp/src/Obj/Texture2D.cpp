//
// Created by revetoon on 3/1/19.
//

#include <functional>
#include "Texture2D.hh"
#include "../Utils/dblutils.hh"
#include "../Constants.hh"

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
    auto h1 = std::hash<double>{}(dblutils::trunc(p.u, constants::OBJ_DBL_PRECISION));
    auto h2 = std::hash<double>{}(dblutils::trunc(p.v, constants::OBJ_DBL_PRECISION));
    auto h3 = std::hash<double>{}(dblutils::trunc(p.w, constants::OBJ_DBL_PRECISION));

    return h1 ^ h2 ^ h3;
}
