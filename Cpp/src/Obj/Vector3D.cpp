//
// Created by revetoon on 3/1/19.
//

#include "Vector3D.hh"
#include "../Utils/dblutils.hh"
#include "../Constants.hh"
#include <cmath>
#include <functional>

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

Vector3D::Vector3D()
    : x(0.0), y(0.0), z(0.0)
{}


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

Vector3D Vector3D::operator*(const double &rhs) const {
    return Vector3D(x * rhs, y * rhs, z * rhs);
}

Vector3D Vector3D::up(double intensity = 1) {
    return Vector3D(0, intensity, 0);
}

Vector3D Vector3D::up() {
    return Vector3D(0, 1, 0);
}

bool Vector3D::isEmpty() {
    return x == 0 && y == 0 && z == 0;
}

double Vector3D::angle(const Vector3D &lhs, const Vector3D &rhs) {
    return (
            acos(
                    std::fabs((lhs.scalar(rhs))
                              /
                              (lhs.length() * rhs.length()))
            ) / M_PI) * 180.0;
}

Vector3D Vector3D::operator+(const double &rhs) const {
    return Vector3D(x + rhs, y + rhs, z + rhs);
}

std::size_t Vector3D::hash::operator()(const Vector3D &p) const {
    auto h1 = std::hash<double>{}(dblutils::trunc(p.x, constants::OBJ_DBL_PRECISION));
    auto h2 = std::hash<double>{}(dblutils::trunc(p.y, constants::OBJ_DBL_PRECISION));
    auto h3 = std::hash<double>{}(dblutils::trunc(p.z, constants::OBJ_DBL_PRECISION));

    return h1 ^ h2 ^ h3;
}
