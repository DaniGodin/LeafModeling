//
// Created by revetoon on 3/1/19.
//

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
