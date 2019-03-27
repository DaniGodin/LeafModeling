//
// Created by revetoon on 3/26/19.
//

#ifndef OBJPARSER_CYLINDER_HH
#define OBJPARSER_CYLINDER_HH


#include "../Point3D.hh"
#include "../Object.hh"

class Cylinder : public Object {

public:
    Cylinder(const Point3D &pos, const Vector3D &up, double height, double radius);
    Cylinder(const Point3D &pos, const Point3D &pos2, double height, double radius);
    Cylinder(const Point3D &pos, const Vector3D &up, double height, double radius, std::string name);
    Cylinder(const Point3D &pos, const Vector3D &up, double height, double radius, std::string name, int subdiv);


    const Point3D getCenterUp() const;
    const Point3D getCenterDown() const;

private:
    void initGeom();
    void genGeometry(int subdiv);

private:
    Point3D pos;
    Vector3D up;
    double height;
    double radius;

    int subdiv = 12;
    Vector3D right;
    Vector3D forward;
};


#endif //OBJPARSER_CYLINDER_HH
