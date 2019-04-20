//
// Created by revetoon on 4/19/19.
//

#ifndef OBJPARSER_TRIANGLE_HH
#define OBJPARSER_TRIANGLE_HH


#include "../Point3D.hh"
#include "../Object.hh"

class Triangle : public Object {

public:
    Triangle(const Point3D &p1, const Point3D &p2, const Point3D &p3, std::string name);
    Triangle(const Point3D &p1, const Point3D &p2, const Point3D &p3);

    Triangle(const Point3D &p1, const Point3D &p2, const Point3D &p3, const Vector3D &norm, std::string name);
    Triangle(const Point3D &p1, const Point3D &p2, const Point3D &p3, const Vector3D &norm);

    const Point3D getCenter() const;

private:
    void initGeom();
    void genGeometry(int subdiv);

private:
    Point3D p1;
    Point3D p2;
    Point3D p3;
    Vector3D norm = Vector3D();

    Point3D center;
//    Vector3D right;
//    Vector3D forward;
};


#endif //OBJPARSER_TRIANGLE_HH
