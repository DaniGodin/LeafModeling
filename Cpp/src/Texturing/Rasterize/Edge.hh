//
// Created by revetoon on 5/12/19.
//

#ifndef OBJPARSER_EDGE_HH
#define OBJPARSER_EDGE_HH


#include "../../Utils/Color.hh"

class Edge {
public:
    Edge(double x1, double y1, double x2, double y2);
    Edge(double x1, double y1, double x2, double y2, const Color &col1, const Color &col2);

public:
    double x1, x2;
    double y1, y2;
    Color col1, col2;
};


#endif //OBJPARSER_EDGE_HH
