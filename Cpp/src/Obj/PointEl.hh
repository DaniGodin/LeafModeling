//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_POINTEL_HH
#define OBJPARSER_POINTEL_HH


#include <vector>
#include "Point3D.hh"
#include "Element.hh"

class PointEl : public Element {
    /*
    Specifies a point element and its vertex. You can specify multiple
    points with this statement. Although points cannot be shaded or
    rendered, they are used by other Advanced Visualizer programs.
    */

public:
    std::vector<Point3D_i> &getVertices();

private:
// pseudo JSON representation
// [
//    Point3D_i: { index: 0, Point3DPtr: 0x75de23 },
//    ...
// ]
    std::vector<Point3D_i> vertices;
};


#endif //OBJPARSER_POINTEL_HH
