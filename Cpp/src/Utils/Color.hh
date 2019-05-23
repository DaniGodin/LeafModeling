//
// Created by revetoon on 4/28/19.
//

#ifndef OBJPARSER_COLOR_HH
#define OBJPARSER_COLOR_HH


class Color {

public:
    Color(double r, double g, double b);
    Color(double rgb);
    Color() = default;


    static Color black() {
        return Color(0, 0, 0);
    }

    static Color white() {
        return Color(1, 1, 1);
    }

    static Color greenLeaf() {
        return Color(0.490196, 0.733333, 0.074510);
    }

    static Color darkGreenLeaf() {
        return Color(0.013967, 0.437500, 0.006639);
    }

    static Color darkRed() {
        return Color::from255(165, 14, 70);
    }

    static Color magenta() {
        return Color(1, 0, 1);
    }

    static Color red() {
        return Color(1, 0, 0);
    }

    static Color green() {
        return Color(0, 1, 0);
    }

    static Color blue() {
        return Color(0, 0, 1);
    }

    static Color from255(int r, int g, int b) {
        return Color(static_cast<double>(r) / 255.0, static_cast<double>(g) / 255.0, static_cast<double>(b) / 255.0);
    }

    double getR() const;

    double getG() const;

    double getB() const;

    double get255R() const;

    double get255G() const;

    double get255B() const;

    Color operator-(const Color &rhs) const;
    Color operator+(const Color &rhs) const;
    Color operator+(double factor) const;
    Color operator*(double factor) const;
    Color operator/(double factor) const;

    static Color distord(const Color &c, int coef);

private:
    double r = 1;
    double g = 1;
    double b = 1;
};


#endif //OBJPARSER_COLOR_HH
