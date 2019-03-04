//
// Created by revetoon on 3/1/19.
//

#include "Point3D.hh"

Point3D::Point3D(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

Point3D::Point3D() {}

Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

double Point3D::getX() const {
    return x;
}

double Point3D::getY() const {
    return y;
}

double Point3D::getZ() const {
    return z;
}

double Point3D::getW() const {
    return w;
}

bool Point3D::operator==(const Point3D &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z &&
           w == rhs.w;
}

bool Point3D::operator!=(const Point3D &rhs) const {
    return !(rhs == *this);
}

Point3D Point3D::operator+(const Vector3D &rhs) const {
    return Point3D(x + rhs.getX(), y + rhs.getY(), z + rhs.getZ());
}

Point3D Point3D::operator*(const Vector3D &rhs) const {
    return Point3D(x * rhs.getX(), y * rhs.getY(), z * rhs.getZ());
}
