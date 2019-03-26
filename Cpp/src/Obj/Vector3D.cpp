//
// Created by revetoon on 3/1/19.
//

#include "Vector3D.hh"
#include <cmath>

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


double Vector3D::scalar(const Vector3D &rhs) const {
    return x * rhs.x +  y * rhs.y + z * rhs.z;
}

Vector3D Vector3D::crossProduct(const Vector3D &rhs) const {
    return Vector3D(y * rhs.z - z * rhs.y,
                   z * rhs.x - x * rhs.z,
                   x * rhs.y - y * rhs.x);
}

double Vector3D::length() const {
    return sqrt(x*x + y*y + z*z);
}

Vector3D &Vector3D::normalize() {
    double len = length();
    double inv = 1;
    if (len > 0) {
        inv = 1/len;
    }
    x *= inv;
    y *= inv;
    z *= inv;

    return *this;
}

const Vector3D Vector3D::normalized() const {
    double len = length();
    double inv = 1;
    if (len > 0) {
        inv = 1/len;
    }
    return Vector3D(x * inv, y * inv, z * inv);
}

Vector3D Vector3D::operator*(const double &rhs) {
    return Vector3D(x * rhs, y * rhs, z * rhs);
}
