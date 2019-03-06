//
// Created by revetoon on 3/6/19.
//

#include "Turtle.hh"

Turtle::Turtle(const Point3D &curr, int currVIndex) : curr(curr), currVIndex(currVIndex), oldVIndex(currVIndex - 1) {}

Turtle::Turtle() {}
