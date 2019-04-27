//
// Created by revetoon on 3/1/19.
//

#include "Object.hh"

Object::Object(const std::string &name) : name(name) {}

Object::Object() {}

std::vector<Point3D*> &Object::getV() {
    return v;
}

std::vector<Point2D*> &Object::getVp() {
    return vp;
}

std::vector<Vector3D*> &Object::getVn() {
    return vn;
}

std::vector<Texture2D*> &Object::getVt() {
    return vt;
}

std::vector<FaceEl> &Object::getFaceEls() {
    return faceEls;
}

const std::vector<FaceEl> &Object::getFaceEls() const {
    return faceEls;
}

std::vector<LineEl> &Object::getLineEls() {
    return lineEls;
}

const std::vector<LineEl> &Object::getLineEls() const {
    return lineEls;
}

const std::string &Object::getName() const {
    return name;
}

void Object::push(const Point3D &p) {
    v.push_back(new Point3D(p));
}

void Object::push(const Point2D &p) {
    vp.push_back(new Point2D(p));
}

void Object::push(const Vector3D &v) {
    vn.push_back(new Vector3D(v));
}

void Object::push(const Texture2D &t) {
    vt.push_back(new Texture2D(t));
}

void Object::push(const FaceEl &f) {
    faceEls.push_back(f);
}

void Object::push(const LineEl &l) {
    lineEls.push_back(l);
}

Object::~Object() {
    // TODO free v vn vp vt
//    std::cout << "Object Destructor called" << std::endl;
}
