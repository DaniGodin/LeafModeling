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

void Span::draw(int y, uint8_t *img, int w, int colorCount) {
    double xSize = x2 - x1;
    if (xSize == 0)
        return;

    // color calculation
    Color colordiff = col2 - col1;
    float factor = 0.0f;
    float factorStep = 1.0f / xSize;

    for (int x = x1; x < x2; ++x) {
        Color curr = col1 + (colordiff * factor);
        img[(y * w + x) * colorCount] = curr.get255R();
        img[(y * w + x) * colorCount + 1] = curr.get255G();
        img[(y * w + x) * colorCount + 2] = curr.get255B();
        factor += factorStep;
    }
}

Span::Span(double x1_, double x2_, const Color &col1_, const Color &col2_) {
    if (x1_ < x2_) {
        x1 = x1_;
        x2 = x2_;
        col1 = col1_;
        col2 = col2_;
    } else {
        x1 = x2_;
        x2 = x1_;
        col1 = col2_;
        col2 = col1_;
    }
}
