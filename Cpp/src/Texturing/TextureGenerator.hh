//
// Created by revetoon on 5/12/19.
//

#ifndef OBJPARSER_TEXTUREGENERATOR_HH
#define OBJPARSER_TEXTUREGENERATOR_HH

#include <vector>

class TextureGenerator {

public:

    static void normalize(std::vector<double> &mat, int size);
    static std::vector<double> gaussianMatrix(int w, int h, int centerX, int centerY, int std);

    // TODO fromObject
//    static

private:
    static double gaussian(int x, int y, int std);


};


#endif //OBJPARSER_TEXTUREGENERATOR_HH
