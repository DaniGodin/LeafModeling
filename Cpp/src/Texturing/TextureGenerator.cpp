//
// Created by revetoon on 5/12/19.
//

#include "TextureGenerator.hh"
#include "Rasterize/Draw.hh"
#include <cmath>
#include <cfloat>

std::vector<double> TextureGenerator::gaussianMatrix(int w, int h, int centerX, int centerY, int std) {
    auto res = std::vector<double>(w * h);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            res[y * w + x] = gaussian(x - centerX, y - centerY, std);
        }
    }
    normalize(res, w * h);
    return res;
}

double TextureGenerator::gaussian(int x, int y, int std) {
    return (1) / (2 * M_PI * pow(std, 2)) * exp((-1) / (2 * pow(std, 2)) * (pow(x, 2) + pow(y, 2)));
}

void TextureGenerator::normalize(std::vector<double> &mat, int size) {
    double min = DBL_MAX;
    double max = DBL_MIN;
    for (int i = 0; i < size; ++i) {
        if (min > mat[i])
            min = mat[i];
        if (max < mat[i]) {
            max = mat[i];
        }
    }

    for (int i = 0; i < size; ++i) {
        mat[i] = (mat[i] - min) / max;
    }
}

Texture TextureGenerator::fromObject(int w, int h,
                                     const Object &obj,
                                     int textureMargin,
                                     TextureGenerator::TextureAxis axis) {
    Texture tex(w, h, 3, Color::darkGreenLeaf());

    // calc bounds
    double minx = DBL_MAX;
    double maxx = DBL_MIN;
    double miny = DBL_MAX;
    double maxy = DBL_MIN;

    for (const Point3D *p: obj.getV()) {
        if (p->getX() < minx)
            minx = p->getX();
        if (p->getX() > maxx)
            maxx = p->getX();
        if (p->getY() < miny)
            miny = p->getY();
        if (p->getY() > maxy)
            maxy = p->getY();
    }

    double margin = textureMargin;
    double ratiox = (w - 2 * margin) / (maxx - minx);
    double ratioy = (h - 2 * margin) / (maxy - miny);
    double ratio = std::min(ratiox, ratioy);

    for (const FaceEl &f: obj.getFaceEls()) {
        Draw::drawTriangle(tex,
                           RasterPoint((f.getPt(0)->getX() - minx) * ratio + margin, h - ((f.getPt(0)->getY() - miny) * ratio + margin), Color::greenLeaf()),
                           RasterPoint((f.getPt(1)->getX() - minx) * ratio + margin, h - ((f.getPt(1)->getY() - miny) * ratio + margin), Color::darkGreenLeaf()),
                           RasterPoint((f.getPt(2)->getX() - minx) * ratio + margin, h - ((f.getPt(2)->getY() - miny) * ratio + margin), Color::darkGreenLeaf()));
    }

    return tex;
}
