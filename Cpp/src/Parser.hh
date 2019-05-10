//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_PARSER_HH
#define OBJPARSER_PARSER_HH

#include <iostream>
#include <fstream>
#include <string>
#include "Obj/Scene.hh"
#include "Obj/FaceEl.hh"
#include "Obj/Object.hh"

class Parser {
public:
    enum class lineType : int {
        V = 0,      // "v"
        VT = 1,         // "vt"
        VN = 2,         // "vn"
        VP,         // "vp"
        F,          // "f"
        L,          // "l"
        P,          // "p"
        O,          // "o"
        SHARP,      // "#"
        MTLLIB,     // "mtllib"
        USEMTL,     // "usemtl"
        // TODO ADD MORE TYPES
        ERROR
    };

    enum class mtlLineType : int {
        NS = 0,      // "Ns"
        KA,      // "Ka"
        KD,      // "Kd"
        KS,      // "Ks"
        KE,      // "Ke"
        NI,      // "Ni"
        D,      // "d"
        ILLUM,      // "illum"
        NEWMTL,     // "newmtl
        SHARP,      // "#"
        // TODO ADD MORE TYPES
        ERROR
    };


public:
    explicit Parser(const std::string &filename);
    explicit Parser(const std::string &filename, const std::string &mtlfilename);

    Scene *parse();

    std::vector<Object *> parseObj();

    std::vector<Material *> parseMtl();

private:

    lineType parseType(std::ifstream &s);
    Point3D parseV(std::ifstream &s);
    Vector3D parseVn(std::ifstream &s);
    FaceEl parseF(std::ifstream &s, Object *currObj, Material *currMat);
    Object *parseO(std::ifstream &s);
    void parseMtllib(std::ifstream &s);
    Material *parseUseMtl(std::ifstream &s);


    mtlLineType mtlParseType(std::ifstream &s);
    Material *parseMtl(std::ifstream &s);
    Color parseColor(std::ifstream &s);
    double parseDbl(std::ifstream &s);

    Material *findMtl(const std::string &name);

private:
    std::string filepath;
    std::string mtlfilepath;

    std::string mtlfilename = "";

    // list of materials needed here to link materials requested
    // in the OBJ file to the actual materials in the MTL
    std::vector<Material *> materials = std::vector<Material *>();

    unsigned globalVCount = 1;
    unsigned globalVnCount = 1;
    unsigned globalVtCount = 1;
    unsigned globalVpCount = 1;
};


#endif //OBJPARSER_PARSER_HH
