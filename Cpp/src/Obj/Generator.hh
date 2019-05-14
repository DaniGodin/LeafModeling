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
#include "../Tree/Node.hh"
#include "Object.hh"
#include "Scene.hh"

class Generator {
public:
    explicit Generator(const std::string &filename);
    Generator(const std::string &filename, const std::string &mtlfilename);


    void write(Scene *s);

    std::string writeObj(std::vector<Object *> objs);
    std::string writeMtl(std::vector<Material *> mtls);

private:

    void writeMtllib(std::ofstream &s, const std::string &mtllib);
    void writeO(std::ofstream &s, Object &o);
    void writeV(std::ofstream &s, Point3D &v);
    void writeVt(std::ofstream &s, Texture2D &vt);
    void writeVn(std::ofstream &s, Vector3D &vn);
    void writeVp(std::ofstream &s, Point2D &vp);
    void writeL(std::ofstream &s, LineEl &l, Object &o);
    void writeF(std::ofstream &s, FaceEl &f, Object &o);
    void writeUsemtl(std::ofstream &s, Material &m);
    void writenewMtl(std::ofstream &s, const std::string &name);
    void writeDbl(std::ofstream &s, const std::string &name, double dbl);
    void writeInt(std::ofstream &s, const std::string &name, int i);
    void writeColor(std::ofstream &s, const std::string &name, Color &c);
    void writeString(std::ofstream &s, const std::string &name, const std::string &value);

    std::unordered_map<Material *, std::vector<FaceEl *>> classifyByMaterial(Object *s);

private:
    std::string filename;

    std::string mtlfilename = "";

    unsigned globalVCount = 1;
    unsigned globalVnCount = 1;
    unsigned globalVtCount = 1;
    unsigned globalVpCount = 1;

};


#endif //OBJPARSER_GENERATOR_HH
