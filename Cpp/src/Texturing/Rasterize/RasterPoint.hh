//
// Created by revetoon on 5/14/19.
//

#ifndef OBJPARSER_RASTERPOINT_HH
#define OBJPARSER_RASTERPOINT_HH


#include "../../Utils/Color.hh"

class RasterPoint {
public:
    RasterPoint(int x, int y, const Color &col);

public:
    int x;
    int y;
    Color col;
};


#endif //OBJPARSER_RASTERPOINT_HH
