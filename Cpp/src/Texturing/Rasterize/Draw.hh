//
// Created by revetoon on 5/12/19.
//

#ifndef OBJPARSER_DRAW_HH
#define OBJPARSER_DRAW_HH

#include <cstdint>
#include <vector>
#include "Edge.hh"
#include "../Texture.hh"
#include "Point2D.hh"

class Draw {

public:
    static uint8_t *drawTriangle(uint8_t *pxls,
                                 double x1, double y1,
                                 const Color &col1,
                                 double x2, double y2,
                                 const Color &col2,
                                 double x3, double y3,
                                 const Color &col3,
                                 int width, int height,
                                 int colorCount = 1, double ratio = 1);

    static uint8_t *drawTriangle(Texture &tex,
                                 double x1, double y1,
                                 double x2, double y2,
                                 double x3, double y3,
                                 double ratio = 1);

    static uint8_t *drawTriangle(Texture &tex,
                                 const Point2D &p1,
                                 const Point2D &p2,
                                 const Point2D &p3,
                                 double ratio = 1);

private:

    // TODO add img in params
    static void drawSpan(const Edge &e1, const Edge &e2, uint8_t *img, int w, int colorCount);
};


#endif //OBJPARSER_DRAW_HH
