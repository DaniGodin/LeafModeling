//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_VECTOR3D_HH
#define OBJPARSER_VECTOR3D_HH


#include <cstddef>

class Vector3D {
public:
    Vector3D();

    Vector3D(double x, double y, double z);

    double getX() const;

    double getY() const;

    double getZ() const;

    bool operator==(const Vector3D &rhs) const;

    bool operator!=(const Vector3D &rhs) const;

    Vector3D operator+(const double &rhs) const;

    double scalar(const Vector3D &rhs) const;

    Vector3D crossProduct(const Vector3D &rhs) const;

    double length() const;

    Vector3D &normalize();

    const Vector3D normalized() const;

    Vector3D operator*(const double &rhs) const;

    static Vector3D up(double intensity);
    static Vector3D up();

    static double angle(const Vector3D &lhs, const Vector3D &rhs);

    bool isEmpty();

    struct hash {
        std::size_t operator () (const Vector3D &p) const;
    };

private:
    double x;
    double y;
    double z;
};


#endif //OBJPARSER_VECTOR3D_HH
