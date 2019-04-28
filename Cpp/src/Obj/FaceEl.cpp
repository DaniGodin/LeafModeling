//
// Created by revetoon on 3/1/19.
//

#include <stdexcept>
#include "FaceEl.hh"

FaceEl::FaceEl(Object *parent) : Element(parent) {}


std::vector<std::tuple<Point3D_i, Texture2D_i, Vector3D_i>> &FaceEl::getVertices() {
    return vertices;
}

const std::vector<std::tuple<Point3D_i, Texture2D_i, Vector3D_i>> &FaceEl::getVertices() const {
    return vertices;
}

Point3D *FaceEl::getPt(int index) {
    return std::get<1>(std::get<0>(vertices[index]));
}

const Point3D *FaceEl::getPt(int index) const {
    return std::get<1>(std::get<0>(vertices[index]));
}

int FaceEl::getIndex(int index) {
    return std::get<0>(std::get<0>(vertices[index]));
}

const int FaceEl::getIndex(int index) const {
    return std::get<0>(std::get<0>(vertices[index]));
}

void FaceEl::push(Point3D *p) {
    auto indexp = parent->find(p);
    if (p != nullptr && indexp == -1)
        throw std::invalid_argument("Couldn't find p in object.");
    vertices.push_back(std::make_tuple(
            std::make_tuple<int, Point3D*>(indexp + 0, std::move(p)),
            std::make_tuple<int, Texture2D*>(0, nullptr),
            std::make_tuple<int, Vector3D*>(0, nullptr)));
}

void FaceEl::push(Point3D *p, Texture2D *t) {
    auto indexp = parent->find(p);
    if (p != nullptr && indexp == -1)
        throw std::invalid_argument("Couldn't find p in object.");
    auto indext = parent->find(t);
    if (t != nullptr && indext == -1)
        throw std::invalid_argument("Couldn't find t in object.");
    vertices.push_back(std::make_tuple(
            std::make_tuple<int, Point3D*>(indexp + 0, std::move(p)),
            std::make_tuple<int, Texture2D*>(indext + 0, std::move(t)),
            std::make_tuple<int, Vector3D*>(0, nullptr)));
}

void FaceEl::push(Point3D *p, Texture2D *t, Vector3D *v) {
    auto indexp = parent->find(p);
    if (p != nullptr && indexp == -1)
        throw std::invalid_argument("Couldn't find p in object.");
    auto indext = parent->find(t);
    if (t != nullptr && indext == -1)
        throw std::invalid_argument("Couldn't find t in object.");
    auto indexv = parent->find(v);
    if (v != nullptr && indexv == -1)
        throw std::invalid_argument("Couldn't find v in object.");
    vertices.push_back(std::make_tuple(
            std::make_tuple<int, Point3D*>(indexp + 0, std::move(p)),
            std::make_tuple<int, Texture2D*>(indext + 0, std::move(t)),
            std::make_tuple<int, Vector3D*>(indexv + 0, std::move(v))));
}

void FaceEl::push(Point3D *p, Vector3D *v) {
    auto indexp = parent->find(p);
    if (p != nullptr && indexp == -1)
        throw std::invalid_argument("Couldn't find p in object.");
    auto indexv = parent->find(v);
    if (v != nullptr && indexv == -1)
        throw std::invalid_argument("Couldn't find v in object.");
    vertices.push_back(std::make_tuple(
            std::make_tuple<int, Point3D*>(indexp + 0, std::move(p)),
            std::make_tuple<int, Texture2D*>(0, nullptr),
            std::make_tuple<int, Vector3D*>(indexv + 0, std::move(v))));
}

void FaceEl::setGlobalNormal(Vector3D *v, int indexv) {
    globalNormal = std::make_tuple<int, Vector3D*>(indexv + 0, std::move(v));
}

const Vector3D_i &FaceEl::getGlobalNormal() const {
    return globalNormal;
}

