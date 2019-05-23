//
// Created by revetoon on 5/23/19.
//

#include <stdexcept>
#include <cmath>
#include "Morphology.hh"

unsigned char unitErode(const std::vector<unsigned char> &vals) {
    for (const auto &v : vals) {
        if (v == 0)
            return 0;
    }
    return 255;
}

unsigned char unitDilate(const std::vector<unsigned char> &vals) {
    for (const auto &v : vals) {
        if (v != 0)
            return 255;
    }
    return 0;
}

Texture Morphology::erode(Texture &img, const std::vector<std::vector<unsigned char>> &kernel, unsigned iteration) {
    if (iteration == 0)
        return img;
    Texture r = convolute(img, kernel, unitErode, 255);
    for (int i = 1; i < iteration; ++i) {
        r = convolute(r, kernel, unitErode, 255);

    }
    return r;
}

Texture Morphology::dilate(Texture &img, const std::vector<std::vector<unsigned char>> &kernel, unsigned iteration) {
    if (iteration == 0)
        return img;
    Texture r = convolute(img, kernel, unitDilate, 0);
    for (int i = 1; i < iteration; ++i) {
        r = convolute(r, kernel, unitDilate, 0);
    }
    return r;
}

Texture Morphology::convolute(Texture &img, const std::vector<std::vector<unsigned char>> &kernel,
                            morphTransfo morphFunction, int oobVal) {
    Texture newImg = Texture(img.getWidth(), img.getHeight(), 1);
    int centery = kernel[0].size() / 2;
    int centerx = kernel.size() / 2;
    std::vector<unsigned char> vals = std::vector<unsigned char>();
    for (int y = 0; y < img.getHeight(); ++y) {
        for (int x = 0; x < img.getWidth(); ++x) {
            vals.clear();
            for (int n = 0; n < kernel.size(); ++n) {
                for (int m = 0; m < kernel[0].size(); ++m) {
                    // skip if point in kernel in a zero
                    if (kernel[n][m] == 0)
                        continue;
                    if ((x + m - centerx) < 0 ||
                        (x + m - centerx) >= img.getWidth() ||
                        (y + n - centery) < 0 ||
                        (y + n - centery) >= img.getHeight()) {
                        // outside the image pixels are interpreted are zeros
                        vals.push_back(oobVal);
                    } else {
                        vals.push_back(img.getPixel((x + m - centerx), (y + n - centery)));
                    }
                }
            }
            unsigned char r = morphFunction(vals);
            newImg.setPixel(x, y, r);
        }
    }
    return newImg;
}

std::vector<std::vector<unsigned char>> Morphology::kerSquare(int side) {
    return kerSquare(side, side);
}

std::vector<std::vector<unsigned char>> Morphology::kerSquare(int x, int y) {
    auto res = std::vector<std::vector<unsigned char>>(y, std::vector<unsigned char>(x, 1));
    return res;
}

std::vector<std::vector<unsigned char>> Morphology::kerCircle(int side) {
    auto res = std::vector<std::vector<unsigned char>>(side, std::vector<unsigned char>(side, 0));
    int mid = side / 2;
    for (int y = 0; y < side; ++y) {
        for (int x = 0; x < side; ++x) {
            res[y][x] = std::pow((y - mid), 2) + std::pow((x - mid), 2) <= std::pow(mid, 2);
        }
    }
    return res;
}
