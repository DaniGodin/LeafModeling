//
// Created by revetoon on 5/12/19.
//

#include "Span.hh"

Span::Span(double x1_, double x2_)
{
    if (x1_ < x2_) {
        x1 = x1_;
        x2 = x2_;
    } else {
        x1 = x2_;
        x2 = x1_;
    }
}

void Span::draw(int y, uint8_t *img, int w) {
    double xSize = x2 - x1;
    if (xSize == 0)
        return;
    for (int x = x1; x < x2; ++x) {
        img[y * w + x] = 255;
    }
}
