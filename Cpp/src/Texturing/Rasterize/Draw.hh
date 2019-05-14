//
// Created by revetoon on 5/12/19.
//

#ifndef OBJPARSER_DRAW_HH
#define OBJPARSER_DRAW_HH

#include <cstdint>
#include <vector>
#include "Edge.hh"

class Draw {

public:
    static uint8_t *drawTriangle(double x1, double y1,
                                 double x2, double y2,
                                 double x3, double y3,
                                 int width, int height);

    static uint8_t *drawTriangle(double x1, double y1,
                                 double x2, double y2,
                                 double x3, double y3,
                                 int width, int height, double ratio);

private:
    // TODO add img in params
    static void drawSpan(const Edge &e1, const Edge &e2, uint8_t *img, int w);
};


#endif //OBJPARSER_DRAW_HH
