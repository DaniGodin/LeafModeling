//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_TEXTURE2D_HH
#define OBJPARSER_TEXTURE2D_HH


class Texture2D {
public:
    double getU() const;

    double getV() const;

    double getW() const;

    bool operator==(const Texture2D &rhs) const;

    bool operator!=(const Texture2D &rhs) const;

private:
    double u;       // horizontal
    double v = 0;   // optional vertical
    double w = 0;   // depth of the texture
};


#endif //OBJPARSER_TEXTURE2D_HH
