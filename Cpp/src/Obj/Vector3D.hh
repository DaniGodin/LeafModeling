//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_VECTOR3D_HH
#define OBJPARSER_VECTOR3D_HH


class Vector3D {
public:
    Vector3D(double x, double y, double z);

    double getX() const;

    double getY() const;

    double getZ() const;

    bool operator==(const Vector3D &rhs) const;

    bool operator!=(const Vector3D &rhs) const;

private:
    double x;
    double y;
    double z;
};


#endif //OBJPARSER_VECTOR3D_HH
