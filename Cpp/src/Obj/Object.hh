//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_OBJECT_HH
#define OBJPARSER_OBJECT_HH


#include <vector>
#include "Point2D.hh"
#include "Point3D.hh"
#include "Vector3D.hh"
#include "Texture2D.hh"
#include "Element.hh"
#include "FaceEl.hh"
#include "LineEl.hh"

class Object {
public:
    explicit Object(const std::string &name);
    Object();

public:
    std::vector<Point3D> &getV();

    const std::vector<Point3D> &getVConst() const;

    std::vector<Point2D> &getVp();

    std::vector<Vector3D> &getVn();

    std::vector<Texture2D> &getVt();

    std::vector<FaceEl> &getFaceEls();

    std::vector<LineEl> &getLineEls();

    const std::string &getName() const;

private:
    std::string name = "default";

    std::vector<Point3D> v;      // geometric vertices
    std::vector<Point2D> vp;     // parameter space vertices
    std::vector<Vector3D> vn;    // vertex normals
    std::vector<Texture2D> vt;   // texture vertices

    std::vector<FaceEl> faceEls;
    std::vector<LineEl> lineEls;
};


#endif //OBJPARSER_OBJECT_HH
