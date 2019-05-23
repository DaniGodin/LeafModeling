//
// Created by revetoon on 5/23/19.
//

#ifndef OBJPARSER_MORPHOLOGY_HH
#define OBJPARSER_MORPHOLOGY_HH

#include "../Texture.hh"

class Morphology {

    typedef unsigned char (*morphTransfo)(const std::vector<unsigned char> &);

public:
    static Texture erode(Texture &img, const std::vector<std::vector<unsigned char>> &kernel, unsigned iteration = 1);
    static Texture dilate(Texture &img, const std::vector<std::vector<unsigned char>> &kernel, unsigned iteration = 1);

    static std::vector<std::vector<unsigned char>> kerSquare(int side);
    static std::vector<std::vector<unsigned char>> kerSquare(int x, int y);
    static std::vector<std::vector<unsigned char>> kerCircle(int side);

private:
    static Texture convolute(Texture &img, const std::vector<std::vector<unsigned char>> &kernel, morphTransfo morphFunction, int oobVal);

};


#endif //OBJPARSER_MORPHOLOGY_HH
