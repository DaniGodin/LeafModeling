//
// Created by revetoon on 3/2/19.
//

#ifndef OBJPARSER_GENERATOR_HH
#define OBJPARSER_GENERATOR_HH


#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Tree/Node.hh"
#include "Obj/Object.hh"
#include "Obj/Scene.hh"

class Generator {
public:
    explicit Generator(const std::string &filename);

    Object generate(Node *root, std::string name);

    std::string write(Scene *s);

private:
    void genTreeO(Node *n, Object &o, long rootIndex);

    void writeO(std::ofstream &s, Object &o);
    void writeV(std::ofstream &s, Point3D &v);
    void writeVt(std::ofstream &s, Texture2D &vt);
    void writeVn(std::ofstream &s, Vector3D &vn);
    void writeVp(std::ofstream &s, Point2D &vp);
    void writeL(std::ofstream &s, LineEl &l, Object &o);
    void writeF(std::ofstream &s, FaceEl &f, Object &o);


private:
    std::string filename;
};


#endif //OBJPARSER_GENERATOR_HH
