//
// Created by revetoon on 5/12/19.
//

#ifndef OBJPARSER_TEXTUREGENERATOR_HH
#define OBJPARSER_TEXTUREGENERATOR_HH

#include <vector>
#include "Texture.hh"
#include "../Obj/Object.hh"

class TextureGenerator {

public:

    enum class TextureAxis {
        XY = 0,
        YZ,
        XZ
    };

    static void normalize(std::vector<double> &mat, int size);
    static std::vector<double> gaussianMatrix(int w, int h, int centerX, int centerY, int std);

    // TODO fromObject
    static Texture fromObject(int w, int h, const Object &obj, int textureMargin = 0, TextureAxis axis = TextureAxis::XY);

private:
    static double gaussian(int x, int y, int std);


};


#endif //OBJPARSER_TEXTUREGENERATOR_HH
