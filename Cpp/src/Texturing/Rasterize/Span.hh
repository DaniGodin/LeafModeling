//
// Created by revetoon on 5/12/19.
//

#ifndef OBJPARSER_SPAN_HH
#define OBJPARSER_SPAN_HH


#include <cstdint>
#include <vector>

class Span {

public:
    Span(double x1, double x2);

    void draw(int y, uint8_t *img, int w, int colorCount);

public:
    double x1, x2;
};


#endif //OBJPARSER_SPAN_HH
