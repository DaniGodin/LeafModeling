//
// Created by revetoon on 5/12/19.
//

#ifndef OBJPARSER_SPAN_HH
#define OBJPARSER_SPAN_HH


#include <cstdint>
#include <vector>
#include "../../Utils/Color.hh"

class Span {

public:
    Span(double x1, double x2);
    Span(double x1, double x2, const Color &col1, const Color &col2);
    Span(double x1, double x2, const Color &col1, const Color &col2, int noise);

    void draw(int y, uint8_t *img, int w, int colorCount);

public:
    int noise = 0;
    double x1, x2;
    Color col1, col2;
};


#endif //OBJPARSER_SPAN_HH
