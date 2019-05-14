//
// Created by revetoon on 5/12/19.
//

#include "Edge.hh"

Edge::Edge(double x1_, double y1_, double x2_, double y2_)
{
    // sort by increasing y
    if (y1_ < y2_) {
        x1 = x1_;
        y1 = y1_;
        x2 = x2_;
        y2 = y2_;
    } else {
        x1 = x2_;
        y1 = y2_;
        x2 = x1_;
        y2 = y1_;
    }
}
