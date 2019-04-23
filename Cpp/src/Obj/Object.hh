//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_OBJECT_HH
#define OBJPARSER_OBJECT_HH


#include <vector>
#include "Point2D.hh"
#include "Point3D.hh"
#include "Vector3D.hh"
#include "Texture2D.hh"
#include "Element.hh"
#include "FaceEl.hh"
#include "LineEl.hh"

class Object {
public:
    explicit Object(const std::string &name);
    Object();

public:
    std::vector<Point3D> &getV() ;

    std::vector<Point2D> &getVp() ;

    std::vector<Vector3D> &getVn() ;

    std::vector<Texture2D> &getVt() ;

    std::vector<FaceEl> &getFaceEls() ;
    const std::vector<FaceEl> &getFaceEls() const;

    std::vector<LineEl> &getLineEls();
    const std::vector<LineEl> &getLineEls() const;

    const std::string &getName() const;


    void push(const Point3D &p);
    void push(const Point2D &p);
    void push(const Vector3D &v);
    void push(const Texture2D &t);
    void push(const FaceEl &f);
    void push(const LineEl &l);

protected:
    std::string name = "default";

    std::vector<Point3D> v;      // geometric vertices
    std::vector<Point2D> vp;     // parameter space vertices
    std::vector<Vector3D> vn;    // vertex normals
    std::vector<Texture2D> vt;   // texture vertices

    std::vector<FaceEl> faceEls;
    std::vector<LineEl> lineEls;
};


#endif //OBJPARSER_OBJECT_HH
