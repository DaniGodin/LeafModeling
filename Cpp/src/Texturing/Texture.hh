//
// Created by revetoon on 5/12/19.
//

#ifndef OBJPARSER_TEXTURE_HH
#define OBJPARSER_TEXTURE_HH


#include <cstdint>
#include <vector>
#include <string>
#include "../Obj/Color.hh"

class Texture {

public:
    Texture(int width, int height);

    Texture(int width, int height, int colorCount, uint8_t *pxls);

    virtual ~Texture();

//    Create an RGB image using a matrix of coefficients of size (W * H), a foreground color and a background color
    void fillPxls(const std::vector<double> &vals, const Color &background, const Color &foreground);

    std::string writeToFile(const std::string &filename);
private:
    int width;
    int height;
    int colorCount = 3;
    uint8_t *pxls = nullptr;
};


#endif //OBJPARSER_TEXTURE_HH
