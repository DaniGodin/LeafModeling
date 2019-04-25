//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_LINEEL_HH
#define OBJPARSER_LINEEL_HH


#include <vector>
#include <tuple>
#include "Point3D.hh"
#include "Texture2D.hh"
#include "Element.hh"

class LineEl : public Element {
    /*
    Specifies a line and its vertex reference numbers. You can
    optionally include the texture vertex reference numbers. Although
    lines cannot be shaded or rendered, they are used by other Advanced
    Visualizer programs.
    */

public:
    std::vector<std::tuple<Point3D_i, Texture2D_i>> &getVertices();
    const std::vector<std::tuple<Point3D_i, Texture2D_i>> &getVertices() const;

    void push(Point3D *p, int indexp);
    void push(Point3D *p, int indexp, Texture2D *t, int indext);

private:
// pseudo JSON representation
//  [
//      {
//          { index: 1, Point3D_Ptr : 0x754635},
//          { index: 2, Texture3DPtr: 0x75A321}
//      },
//      ...
//  ]
    std::vector<std::tuple<Point3D_i, Texture2D_i>> vertices;
};


#endif //OBJPARSER_LINEEL_HH
