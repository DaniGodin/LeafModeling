//
// Created by revetoon on 3/1/19.
//

#include "FaceEl.hh"

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

void FaceEl::push(Point3D *p, int indexp) {
    vertices.push_back(std::make_tuple(
            std::make_tuple(indexp, p),
            std::make_tuple(0, nullptr),
            std::make_tuple(0, nullptr)));
}

void FaceEl::push(Point3D *p, int indexp, Texture2D *t, int indext) {
    vertices.push_back(std::make_tuple(
            std::make_tuple(indexp, p),
            std::make_tuple(indext, t),
            std::make_tuple(0, nullptr)));
}

void FaceEl::push(Point3D *p, int indexp, Texture2D *t, int indext, Vector3D *v, int indexv) {
    vertices.push_back(std::make_tuple(
            std::make_tuple(indexp, p),
            std::make_tuple(indext, t),
            std::make_tuple(indexv, v)));
}

void FaceEl::push(Point3D *p, int indexp, Vector3D *v, int indexv) {
    vertices.push_back(std::make_tuple(
            std::make_tuple(indexp, p),
            std::make_tuple(0, nullptr),
            std::make_tuple(indexv, v)));
}
