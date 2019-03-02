//
// Created by revetoon on 3/1/19.
//

#include "FaceEl.hh"

std::vector<std::tuple<Point3D_i, Texture2D_i, Vector3D_i>> &FaceEl::getVertices() {
    return vertices;
}
