//
// Created by revetoon on 5/12/19.
//

#include "Texture.hh"
#include "../../include/jpge.h"

Texture::Texture(int width, int height)
        : width(width), height(height), pxls(new uint8_t[width * height * colorCount])
{}

Texture::Texture(int width, int height, int colorCount, uint8_t *pxls)
        : width(width), height(height), colorCount(colorCount), pxls(pxls)
{}

void Texture::fillPxls(const std::vector<double> &vals, const Color &background, const Color &foreground) {

    for (int i, ii = 0; i < width * height * colorCount; i+=3, ++ii) {
        pxls[i]     = (background.getR() * (1.0 - vals[ii]) + foreground.getR() * vals[ii]) * 255;
        pxls[i + 1] = (background.getG() * (1.0 - vals[ii]) + foreground.getG() * vals[ii]) * 255;
        pxls[i + 2] = (background.getB() * (1.0 - vals[ii]) + foreground.getB() * vals[ii]) * 255;
    }
}

std::string Texture::writeToFile(const std::string &filename) {
    jpge::compress_image_to_jpeg_file(filename.c_str(), width, height, colorCount, pxls);
    return filename;
}

Texture::~Texture() {
    delete pxls;
}

