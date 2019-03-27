//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_POINT3D_HH
#define OBJPARSER_POINT3D_HH


#include "Vector3D.hh"

class Point3D {
public:
    Point3D();

    Point3D(double x, double y, double z);

    Point3D(double x, double y, double z, double w);

    double getX() const;

    double getY() const;

    double getZ() const;

    double getW() const;

    bool operator==(const Point3D &rhs) const;

    bool operator!=(const Point3D &rhs) const;

    Point3D operator+(const Vector3D &rhs) const;

    Point3D operator*(const Vector3D &rhs) const;

    const Vector3D operator-(const Point3D &rhs) const;

private:
    double x;
    double y;
    double z;
    double w = 1.0; // weight
};


#endif //OBJPARSER_POINT3D_HH
