//
// Created by revetoon on 3/1/19.
//

#include "Vector3D.hh"

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

double Vector3D::getX() const {
    return x;
}

double Vector3D::getY() const {
    return y;
}

double Vector3D::getZ() const {
    return z;
}

bool Vector3D::operator==(const Vector3D &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z;
}

bool Vector3D::operator!=(const Vector3D &rhs) const {
    return !(rhs == *this);
}

Vector3D::Vector3D() {}