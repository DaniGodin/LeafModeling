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
        // TODO ADD MORE TYPES
        ERROR
    };


public:
    explicit Parser(std::string filename);

    Scene *parse();

private:
    lineType parseType(std::ifstream &s);
    Point3D parseV(std::ifstream &s);
    Vector3D parseVn(std::ifstream &s);
    FaceEl parseF(std::ifstream &s, Object *currObj);
    Object *parseO(std::ifstream &s);

private:
    std::string filename;
};


#endif //OBJPARSER_PARSER_HH
