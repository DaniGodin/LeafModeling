//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_FACEEL_HH
#define OBJPARSER_FACEEL_HH


#include <vector>
#include <tuple>
#include "Point3D.hh"
#include "Texture2D.hh"
#include "Vector3D.hh"
#include "Element.hh"

class FaceEl : public Element {
    /*
    Specifies a face element and its vertex reference number. You can
    optionally include the texture vertex and vertex normal reference
    numbers.
    */

public:
    std::vector<std::tuple<Point3D_i, Texture2D_i, Vector3D_i>> &getVertices();
    const std::vector<std::tuple<Point3D_i, Texture2D_i, Vector3D_i>> &getVertices() const;

    void push(Point3D *p, int indexp);
    void push(Point3D *p, int indexp, Texture2D *t, int indext);
    void push(Point3D *p, int indexp, Texture2D *t, int indext, Vector3D *v, int indexv);
    void push(Point3D *p, int indexp, Vector3D *v, int indexv);

    Point3D *getPt(int index);
    const Point3D *getPt(int index) const;

    int getIndex(int index);
    const int getIndex(int index) const;

    void setGlobalNormal(Vector3D *v, int indexv);

    const Vector3D_i &getGlobalNormal() const;

protected:
// pseudo JSON representation
//  [
//      {
//          Point3D_i:   { index: 1, Point3D_Ptr : 0x754635},
//          Texture2D_i: { index: 2, Texture3DPtr: 0x75a321},
//          Vector3D_i:  { index: 1, Vector3DPtr : 0x75ad34}
//      },
//      ...
//  ]
    std::vector<std::tuple<Point3D_i, Texture2D_i, Vector3D_i>> vertices;
    Vector3D_i globalNormal = std::make_tuple<int, Vector3D*>(0, nullptr);
};


#endif //OBJPARSER_FACEEL_HH
