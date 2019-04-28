//
// Created by revetoon on 3/1/19.
//

#include "PointEl.hh"

PointEl::PointEl(Object *parent) : Element(parent) {}


std::vector<Point3D_i> &PointEl::getVertices() {
    return vertices;
}

