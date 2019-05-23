//
// Created by revetoon on 5/12/19.
//

#ifndef OBJPARSER_TEXTURE_HH
#define OBJPARSER_TEXTURE_HH


#include <cstdint>
#include <vector>
#include <string>
#include "../Utils/Color.hh"

class Texture {
public:
    enum class Channel : int {
        R = 0,
        G = 1,
        B = 2,
    };

public:
    Texture(int width, int height);

    Texture(int width, int height, int colorCount);

    Texture(int width, int height, const Color &bg);

    Texture(int width, int height, int colorCount, const Color &bg);

    Texture(int width, int height, const Color &bg, int noise);

    Texture(int width, int height, int colorCount, uint8_t *pxls);

    virtual ~Texture();

//    Create an RGB image using a matrix of coefficients of size (W * H), a foreground color and a background color
    void fillPxls(const std::vector<double> &vals, const Color &background, const Color &foreground);

    std::string writeToFile(const std::string &filename);

    static Texture monoChannel(const Texture &t, Channel selectedChannel = Channel::R);

    uint8_t *getUnderlyingPixels();

    uint8_t getPixel(int x, int y);
    bool setPixel(int x, int y, uint8_t val);

    int getWidth() const;

    int getHeight() const;

    int getColorCount() const;

private:
    int width;
    int height;
    int colorCount = 3;
    uint8_t *pxls = nullptr;
};


#endif //OBJPARSER_TEXTURE_HH
