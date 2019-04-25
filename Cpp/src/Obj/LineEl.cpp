//
// Created by revetoon on 3/1/19.
//

#include "LineEl.hh"

std::vector<std::tuple<Point3D_i, Texture2D_i>> &LineEl::getVertices() {
    return vertices;
}

const std::vector<std::tuple<Point3D_i, Texture2D_i>> &LineEl::getVertices() const {
    return vertices;
}

void LineEl::push(Point3D *p, int indexp) {
    vertices.push_back(std::make_tuple(
            std::make_tuple(indexp, p),
            std::make_tuple(0, nullptr)
            ));
}

void LineEl::push(Point3D *p, int indexp, Texture2D *t, int indext) {
    vertices.push_back(std::make_tuple(
            std::make_tuple(indexp, p),
            std::make_tuple(0, nullptr)
            ));
}
