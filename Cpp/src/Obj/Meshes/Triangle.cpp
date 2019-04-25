//
// Created by revetoon on 4/19/19.
//

#include "Triangle.hh"

Triangle::Triangle(const Point3D &p1, const Point3D &p2, const Point3D &p3, std::string name)
    : p1(p1), p2(p2), p3(p3), Object(name)
{}

Triangle::Triangle(const Point3D &p1, const Point3D &p2, const Point3D &p3, const Vector3D &norm, std::string name)
    : p1(p1), p2(p2), p3(p3), norm(norm), Object(name)
{}

Triangle::Triangle(const Point3D &p1, const Point3D &p2, const Point3D &p3, const Vector3D &norm)
    : p1(p1), p2(p2), p3(p3), norm(norm)
{}

Triangle::Triangle(const Point3D &p1, const Point3D &p2, const Point3D &p3)
    : p1(p1), p2(p2), p3(p3)
{}

const Point3D Triangle::getCenter() const {
    return p1; // TODO
}

void Triangle::initGeom() {
    if (norm.isEmpty()) {
        Vector3D dir1 = (p2 - p1).normalized();
        Vector3D dir2 = (p3 - p1).normalized();
        norm = dir1.crossProduct(dir2);
    }
}

void Triangle::genGeometry(int subdiv) {
    push(p1);
    push(p2);
    push(p3);
    FaceEl f = FaceEl();
    for (int i = 0; i < 3; ++i) {
        f.getVertices().push_back(std::make_tuple(
                std::make_tuple<int, Point3D*>(std::move(i), v[i]+ 0),
                std::make_tuple<int, Texture2D*>(0, nullptr),
                std::make_tuple<int, Vector3D*>(0, nullptr)
        ));
    }
    faceEls.push_back(f);
}

