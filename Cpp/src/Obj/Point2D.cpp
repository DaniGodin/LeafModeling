//
// Created by revetoon on 3/1/19.
//

#include "Point2D.hh"

double Point2D::getU() const {
    return u;
}

double Point2D::getV() const {
    return v;
}

double Point2D::getW() const {
    return w;
}

bool Point2D::operator==(const Point2D &rhs) const {
    return u == rhs.u &&
           v == rhs.v &&
           w == rhs.w;
}

bool Point2D::operator!=(const Point2D &rhs) const {
    return !(rhs == *this);
}
