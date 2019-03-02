//
// Created by revetoon on 3/1/19.
//

#include "Object.hh"

std::vector<Point3D> &Object::getV() {
    return v;
}

const std::vector<Point3D> &Object::getVConst() const {
    return v;
}

std::vector<Point2D> &Object::getVp() {
    return vp;
}

std::vector<Vector3D> &Object::getVn() {
    return vn;
}

std::vector<Texture2D> &Object::getVt() {
    return vt;
}

std::vector<FaceEl> &Object::getFaceEls() {
    return faceEls;
}

Object::Object(const std::string &name) : name(name) {}

Object::Object() {}

std::vector<LineEl> &Object::getLineEls() {
    return lineEls;
}

const std::string &Object::getName() const {
    return name;
}
