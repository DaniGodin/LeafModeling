//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_POINT2D_HH
#define OBJPARSER_POINT2D_HH


class Point2D {
public:
    double getU() const;

    double getV() const;

    double getW() const;

    bool operator==(const Point2D &rhs) const;

    bool operator!=(const Point2D &rhs) const;

private:
    double u;
    double v;
    double w = 1.0; // weight
};


#endif //OBJPARSER_POINT2D_HH
