//
// Created by revetoon on 3/26/19.
//

#include "Cylinder.hh"
#include <cmath>

Cylinder::Cylinder(const Point3D &pos, const Vector3D &up, double height, double radius) : pos(pos), up(up.normalized()),
                                                                                           height(height),
                                                                                           radiusBottom(radius),
                                                                                           radiusTop(radius) {
    initGeom();
    genGeometry(subdiv);
}

Cylinder::Cylinder(const Point3D &pos, const Point3D &pos2, double height, double radius)
        : pos(pos),
          up((pos2 - pos).normalized()),
          height(height),
          radiusBottom(radius) {
    initGeom();
    genGeometry(subdiv);
}

Cylinder::Cylinder(const Point3D &pos, const Vector3D &up, double height, double radius, std::string name) : pos(pos),
                                                                                                             up(up.normalized()),
                                                                                                             height(height),
                                                                                                             radiusBottom(radius),
                                                                                                             radiusTop(radius),
                                                                                                             Object(name) {
    initGeom();
    genGeometry(subdiv);
}


Cylinder::Cylinder(const Point3D &pos, const Vector3D &up, double height, double radius, std::string name, int subdiv)
        : pos(pos),
          up(up.normalized()),
          height(height),
          radiusBottom(radius),
          radiusTop(radius),
          Object(name),
          subdiv(subdiv) {

    initGeom();
    genGeometry(subdiv);
}

Cylinder::Cylinder(const Point3D &pos, const Vector3D &up, double height, double radiusBottom, double radiusTop,
                   std::string name)
        : pos(pos),
          up(up.normalized()),
          height(height),
          radiusBottom(radiusBottom),
          radiusTop(radiusTop),
          Object(name)
{
    initGeom();
    genGeometry(subdiv);
}

Cylinder::Cylinder(const Point3D &pos, const Vector3D &up, double height, double radiusBottom, double radiusTop,
                   std::string name, int subdiv)
        : pos(pos),
          up(up.normalized()),
          height(height),
          radiusBottom(radiusBottom),
          radiusTop(radiusTop),
          Object(name),
          subdiv(subdiv)
{
    initGeom();
    genGeometry(subdiv);
}

void Cylinder::initGeom() {
    // create a "random" point o
    Point3D o = Point3D(pos.getX() - 2, pos.getY() - 2, pos.getZ());

    Vector3D dirO = o - pos; // towards o

    // vector in the normal plane of up
    right = up.crossProduct(dirO).normalize();
    forward = up.crossProduct(right).normalize();
}

void Cylinder::genGeometry(int subdiv) {

    double full = 2 * M_PI;
    double angle = full / static_cast<double>(subdiv);
    for (int i = 0; i < subdiv / 2; ++i) {
        Point3D pBottom = pos + (right * (cos(angle * i) * radiusBottom)) + (forward * (sin(angle * i) * radiusBottom));
        Point3D pTop = (pos + up * height) + (right * (cos(angle * i) * radiusTop)) + (forward * (sin(angle * i) * radiusTop));
        push(pBottom);
        push(pTop);
    }

    for (int i = 0; i < subdiv; i += 2) {
        Point3D pBottom = pos + (pos - *v[i]);
        Point3D pTop = (pos + up * height) + ((pos + up * height) - *v[i + 1]);
        push(pBottom);
        push(pTop);
    }


    for (int i = 0; i < subdiv * 2; i+= 2) {
        FaceEl face = FaceEl();

        // vertex bottom 1
        face.push(v[i], i);
//        face.getVertices().push_back(std::make_tuple(
//                std::make_tuple<int, Point3D*>(std::move(i), &v[i]),
//                std::make_tuple<int, Texture2D*>(0, nullptr),
//                std::make_tuple<int, Vector3D*>(0, nullptr)));

        // vertex top 1
        face.push(v[i + 1], i + 1);
//        face.getVertices().push_back(std::make_tuple(
//                std::make_tuple<int, Point3D*>(std::move(i + 1), &v[i + 1]),
//                std::make_tuple<int, Texture2D*>(0, nullptr),
//                std::make_tuple<int, Vector3D*>(0, nullptr)));

        // vertex top 2
        face.push(v[i + 3], (i + 3) % (subdiv * 2));
//        face.getVertices().push_back(std::make_tuple(
//                std::make_tuple<int, Point3D*>(std::move((i + 3) % (subdiv * 2)), &v[i + 3]),
//                std::make_tuple<int, Texture2D*>(0, nullptr),
//                std::make_tuple<int, Vector3D*>(0, nullptr)));

        // vertex bottom 2
        face.push(v[i + 2], (i + 2) % (subdiv * 2));
//        face.getVertices().push_back(std::make_tuple(
//                std::make_tuple<int, Point3D*>(std::move((i + 2) % (subdiv * 2)), &v[i + 2]),
//                std::make_tuple<int, Texture2D*>(0, nullptr),
//                std::make_tuple<int, Vector3D*>(0, nullptr)));

        faceEls.push_back(face);
    }

    // bottom circle
    FaceEl bot = FaceEl();
    for (int i = 0; i < subdiv * 2; i+= 2) {
        bot.push(v[i], i);
//        bot.getVertices().push_back(std::make_tuple(
//                std::make_tuple<int, Point3D*>(std::move(i), &v[i]),
//                std::make_tuple<int, Texture2D*>(0, nullptr),
//                std::make_tuple<int, Vector3D*>(0, nullptr)));
    }
    faceEls.push_back(bot);
    // top circle
    FaceEl top = FaceEl();
    for (int i = 1; i < subdiv * 2; i+= 2) {
        top.push(v[i], i);
//        top.getVertices().push_back(std::make_tuple(
//                std::make_tuple<int, Point3D*>(std::move(i), &v[i]),
//                std::make_tuple<int, Texture2D*>(0, nullptr),
//                std::make_tuple<int, Vector3D*>(0, nullptr)));
    }
    faceEls.push_back(top);

}

const Point3D Cylinder::getCenterDown() const {
    return Point3D(pos);
}

const Point3D Cylinder::getCenterUp() const {
    return Point3D(pos + (up * height));
}

double Cylinder::getRadiusBottom() const {
    return radiusBottom;
}

double Cylinder::getRadiusTop() const {
    return radiusTop;
}

