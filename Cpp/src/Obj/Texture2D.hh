//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_TEXTURE2D_HH
#define OBJPARSER_TEXTURE2D_HH


#include <cstddef>

class Texture2D {
public:
    Texture2D(double u, double v);

    Texture2D(double u, double v, double w);

    Texture2D(double u);

    double getU() const;

    double getV() const;

    double getW() const;

    bool operator==(const Texture2D &rhs) const;

    bool operator!=(const Texture2D &rhs) const;

    struct hash {
        std::size_t operator () (const Texture2D &p) const;
    };

private:
    double u;       // horizontal
    double v = 0;   // optional vertical
    double w = 0;   // depth of the texture
};


#endif //OBJPARSER_TEXTURE2D_HH
