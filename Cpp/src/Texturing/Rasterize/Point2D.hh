//
// Created by revetoon on 5/14/19.
//

#ifndef OBJPARSER_POINT2D_HH
#define OBJPARSER_POINT2D_HH


#include "../../Utils/Color.hh"

class Point2D {
public:
    Point2D(int x, int y, const Color &col);

public:
    int x;
    int y;
    Color col;
};


#endif //OBJPARSER_POINT2D_HH
