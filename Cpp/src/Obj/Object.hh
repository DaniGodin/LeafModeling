//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_OBJECT_HH
#define OBJPARSER_OBJECT_HH


#include <vector>
#include <unordered_map>
#include "Point2D.hh"
#include "Point3D.hh"
#include "Vector3D.hh"
#include "Texture2D.hh"
#include "Element.hh"

class FaceEl;
class LineEl;

class Object {
public:

    explicit Object(const std::string &name);
    Object();
    ~Object();

public:

    const std::vector<Point3D*> &getV() const;
    const std::vector<Point2D*> &getVp() const;

    const std::vector<Vector3D*> &getVn() const;

    const std::vector<Texture2D*> &getVt() const;

    std::vector<FaceEl> &getFaceEls() ;

    const std::vector<FaceEl> &getFaceEls() const;
    std::vector<LineEl> &getLineEls();

    const std::vector<LineEl> &getLineEls() const;
    const std::string &getName() const;

    int push(const Point3D &p);


    int push(const Point2D &p);
    int push(const Vector3D &v);
    int push(const Texture2D &t);
    int push(const FaceEl &f);
    int push(const LineEl &l);
    void autoGenNormal();

    bool isEmpty();

    void setUniformMaterial(Material *mat);
    void genUniformVTs(int w = 0, int h = 0, int margin = 0);

protected:
    friend class Element;
    friend class FaceEl;
    friend class LineEl;

    int find(const Point3D *p);
    int find(const Point2D *p);
    int find(const Vector3D *v);
    int find(const Texture2D *t);

protected:
    std::string name = "default";

    std::vector<Point3D*> v;      // geometric vertices
    std::vector<Point2D*> vp;     // parameter space vertices
    std::vector<Vector3D*> vn;    // vertex normals
    std::vector<Texture2D*> vt;   // texture vertices

    std::vector<FaceEl> faceEls;
    std::vector<LineEl> lineEls;

    // duplicate Checking
    std::unordered_map<Point3D, int, Point3D::hash> v_map = std::unordered_map<Point3D, int, Point3D::hash>();
    std::unordered_map<Point2D, int, Point2D::hash> vp_map = std::unordered_map<Point2D, int, Point2D::hash>();
    std::unordered_map<Vector3D, int, Vector3D::hash> vn_map = std::unordered_map<Vector3D, int, Vector3D::hash>();
    std::unordered_map<Texture2D, int, Texture2D::hash> vt_map = std::unordered_map<Texture2D, int, Texture2D::hash>();
};

#include "FaceEl.hh"
#include "LineEl.hh"

#endif //OBJPARSER_OBJECT_HH
