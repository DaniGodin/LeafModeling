//
// Created by revetoon on 3/1/19.
//

#include <cfloat>
#include "Object.hh"

Object::Object(const std::string &name) : name(name) {}

Object::Object() {}

const std::vector<Point3D*> &Object::getV() const {
    return v;
}

const std::vector<Point2D*> &Object::getVp() const {
    return vp;
}

const std::vector<Vector3D*> &Object::getVn() const {
    return vn;
}

const std::vector<Texture2D*> &Object::getVt() const {
    return vt;
}

std::vector<FaceEl> &Object::getFaceEls() {
    return faceEls;
}

const std::vector<FaceEl> &Object::getFaceEls() const {
    return faceEls;
}

std::vector<LineEl> &Object::getLineEls() {
    return lineEls;
}

const std::vector<LineEl> &Object::getLineEls() const {
    return lineEls;
}

const std::string &Object::getName() const {
    return name;
}

int Object::push(const Point3D &p) {
    auto a = new Point3D(p);
    auto[it, b] = v_map.insert(std::pair(*a, static_cast<int>(v.size())));
    if (!b)
        return (*it).second;
    v.push_back(a);
    return v.size() - 1;
}

int Object::push(const Point2D &p) {
    auto a = new Point2D(p);
    auto[it, b] = vp_map.insert(std::pair(*a, vp.size()));
    if (!b)
        return (*it).second;
    vp.push_back(a);
    return vp.size() - 1;
}

int Object::push(const Vector3D &v) {
    auto a = new Vector3D(v);
    auto[it, b] = vn_map.insert(std::pair(*a, vn.size()));
    if (!b)
        return (*it).second;
    vn.push_back(a);
    return vn.size() - 1;

}

int Object::push(const Texture2D &t) {
    auto a = new Texture2D(t);
    auto[it, b] = vt_map.insert(std::pair(*a, vt.size()));
    if (!b)
        return (*it).second;
    vt.push_back(a);
    return vt.size() - 1;
}

int Object::push(const FaceEl &f) {
    faceEls.push_back(f);
    return faceEls.size() - 1;
}

int Object::push(const LineEl &l) {
    lineEls.push_back(l);
    return lineEls.size() - 1;
}

Object::~Object() {
    // TODO free v vn vp vt
    std::cout << "Object Destructor called" << std::endl;
}

void Object::autoGenNormal() {
    if (v.size() < 2)
        throw std::out_of_range("Not enough vertices");
     for (auto &f : faceEls) {
         if (f.getVertices().size() < 3)
             continue;
         Vector3D norm = (*f.getPt(1) - *f.getPt(0)).crossProduct(*f.getPt(2) - *f.getPt(0)).normalized();
         int index = push(norm);
         f.setGlobalNormal(vn[index], index);
     }
}

int Object::find(const Point3D *p) {
    if (p == nullptr)
        return -1;
    auto r = v_map.find(*p);
    return r == v_map.end() ? -1 : (*r).second;
}

int Object::find(const Point2D *p) {
    if (p == nullptr)
        return -1;
    auto r = vp_map.find(*p);
    return r == vp_map.end() ? -1 : (*r).second;
}

int Object::find(const Vector3D *v) {
    if (v == nullptr)
        return -1;
    auto r = vn_map.find(*v);
    return r == vn_map.end() ? -1 : (*r).second;
}

int Object::find(const Texture2D *t) {
    if (t == nullptr)
        return -1;
    auto r = vt_map.find(*t);
    return r == vt_map.end() ? -1 : (*r).second;
}

bool Object::isEmpty() {
    return v.empty() && vn.empty() && vp.empty() && vt.empty();
}

void Object::setUniformMaterial(Material *mat) {
    for (FaceEl &f : faceEls) {
        f.setMat(mat);
    }
}

void Object::genUniformVTs(int w, int h, int margin) {

    if (w == 0 || h == 0) {
        for (FaceEl &f : faceEls) {
            f.genUniformVT();
        }
        return;
    }

    // calc bounds
    double minx = DBL_MAX;
    double maxx = DBL_MIN;
    double miny = DBL_MAX;
    double maxy = DBL_MIN;

    for (const Point3D *p: getV()) {
        if (p->getX() < minx)
            minx = p->getX();
        if (p->getX() > maxx)
            maxx = p->getX();
        if (p->getY() < miny)
            miny = p->getY();
        if (p->getY() > maxy)
            maxy = p->getY();
    }

    double ratiox = ((w - 2 * margin) / (maxx - minx)) / w;
    double ratioy = ((h - 2 * margin) / (maxy - miny)) / h;
    double ratio = std::min(ratiox, ratioy);

    for (FaceEl &f : faceEls) {
        f.genUniformVT(minx + margin, miny + margin, ratio);
    }
}