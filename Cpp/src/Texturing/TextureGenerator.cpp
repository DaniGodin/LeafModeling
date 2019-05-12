//
// Created by revetoon on 5/12/19.
//

#include "TextureGenerator.hh"
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
