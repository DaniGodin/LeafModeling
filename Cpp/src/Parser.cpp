//
// Created by revetoon on 3/1/19.
//

#include <tuple>
#include <sstream>
#include "Parser.hh"
#include "Utils/Strutils.hh"

Parser::Parser(const std::string &filename)
        : filepath(filename)
{
    mtlfilepath = Strutils::rmExtension(filename) + ".mtl";
}

Parser::Parser(const std::string &filename, const std::string &mtlfilename)
        : filepath(filename), mtlfilepath(mtlfilename)
{}

Parser::lineType Parser::parseType(std::ifstream &s) {
    const int kwSize = 11;
    const std::tuple<std::string, lineType> keywords[kwSize] = {
            std::make_tuple("v", lineType::V),
            std::make_tuple("vt", lineType::VT),
            std::make_tuple("vn", lineType::VN),
            std::make_tuple("vp", lineType::VP),
            std::make_tuple("f", lineType::F),
            std::make_tuple("l", lineType::L),
            std::make_tuple("p", lineType::P),
            std::make_tuple("o", lineType::O),
            std::make_tuple("#", lineType::SHARP),
            std::make_tuple("mtllib", lineType::MTLLIB),
            std::make_tuple("usemtl", lineType::USEMTL),
    };


    std::string word;
    s >> word;

    for (int i = 0; i < kwSize; ++i) {
        if (word.compare(std::get<0>(keywords[i])) == 0) {
            return std::get<1>(keywords[i]);
        }

    }


    return lineType::ERROR;
}

Scene *Parser::parse() {

    auto objs = parseObj();
    auto mtls = parseMtl();
    Scene *scene = new Scene(objs, mtls);

    scene->setMtllib(mtlfilename);

    return scene;
}

std::vector<Object *> Parser::parseObj() {
    std::ifstream s = std::ifstream(filepath);
    Object *currObj = new Object();
    // count mtl requested in the obj file
    int mtlCount = 0;
    auto objs = std::vector<Object *>();

    // buffer line for SHARP
    std::string line;
    Material *currMat = nullptr;

    unsigned objectVCount = 0;
    unsigned objectVnCount = 0;
    unsigned objectVtCount = 0;
    unsigned objectVpCount = 0;


    while (!s.eof()) {
        // line start
        lineType type = parseType(s);

        // exclude SHARP lines
        if (type == lineType::SHARP) {
            // ignore line
            getline(s, line);
            continue;
        }

        // Could not parse line -> "ERROR"
        if (type == lineType::ERROR) {
            // ignore line
            getline(s, line);
            std::cerr << "couldn't parse line: ... " << line << std::endl;
            continue;
        }

        switch (type) {

            case lineType::O:
                if (!currObj->isEmpty())
                    objs.push_back(currObj);

                currObj = parseO(s);

                // update global v, vn, vt, vp count with current object count
                globalVCount += objectVCount;
                globalVnCount += objectVnCount;
                globalVtCount += objectVtCount;
                globalVpCount += objectVpCount;
                // reset local count
                objectVCount = 0;
                objectVnCount = 0;
                objectVtCount = 0;
                objectVpCount = 0;
                break;

            case lineType::V:
                ++objectVCount;
                currObj->push(parseV(s));
//                currObj.getV().push_back(parseV(s));
                break;

            case lineType::VN:
                ++objectVnCount;
                currObj->push(parseVn(s));
//                currObj.getVn().push_back(parseVn(s));
                break;

            case lineType::F:
                currObj->push(parseF(s, currObj, currMat));
//                currObj.getFaceEls().push_back(parseF(s, currObj));
                break;

            case lineType::VT:      // TODO
                ++objectVtCount;
                break;
            case lineType::VP:      // TODO
                ++objectVpCount;
                break;
            case lineType::L:       // TODO
                break;
            case lineType::P:       // TODO
                break;

            case lineType::MTLLIB:
                parseMtllib(s);
                break;
            case lineType::USEMTL:
                currMat = parseUseMtl(s);
                break;
        }
    }
    objs.push_back(currObj);

    s.close();

    return objs;
}



Point3D Parser::parseV(std::ifstream &s) {
    std::string line;
    getline(s, line);
    std::istringstream is(line);
    double x = 0.0, y = 0.0, z = 0.0, w = 1.0;
    is >> x >> y >> z;
    if (!is.eof())
        is >> w;
    return Point3D(x, y, z, w);
}

Vector3D Parser::parseVn(std::ifstream &s) {
    std::string line;
    getline(s, line);
    std::istringstream is(line);
    double x = 0.0, y = 0.0, z = 0.0;
    is >> x >> y >> z;
    return Vector3D(x, y, z);
}

FaceEl Parser::parseF(std::ifstream &s, Object *currObj, Material *currMat) {
    std::string line;
    getline(s, line);
    line = Strutils::trim(line);
    std::istringstream is(line);
    FaceEl el = FaceEl(currObj);
    std::string word;
    std::string num;
    auto tuple = std::vector<int>(3, INT32_MIN);
    while (!is.eof()) {
        getline(is, word, ' ');
        std::istringstream is2(word);
        for (int i = 0; !is2.eof() && i < 3; ++i) {
            getline(is2, num, '/');
            try {
                tuple[i] = std::stoi(num);
            } catch (const std::exception &unused) {}
        }
        el.push(tuple[0] == INT32_MIN ? nullptr : currObj->getV ()[tuple[0] - globalVCount],
                tuple[1] == INT32_MIN ? nullptr : currObj->getVt()[tuple[1] - globalVtCount],
                tuple[2] == INT32_MIN ? nullptr : currObj->getVn()[tuple[2] - globalVnCount]);
//        el.getVertices().push_back(std::make_tuple(
//                std::make_tuple<int, Point3D*>(tuple[0] - 1, tuple[0] == INT32_MIN ? nullptr : &currObj.getV ()[tuple[0] - 1]),
//                std::make_tuple<int, Texture2D*>(tuple[1] - 1, tuple[1] == INT32_MIN ? nullptr : &currObj.getVt()[tuple[1] - 1]),
//                std::make_tuple<int, Vector3D*>(tuple[2] - 1, tuple[2] == INT32_MIN ? nullptr : &currObj.getVn()[tuple[2] - 1])));
    }
    el.setMat(currMat);
    return el;
}

Object *Parser::parseO(std::ifstream &s) {
    std::string line;
    getline(s, line);
    line = Strutils::trim(line);
    return new Object(line);;
}

void Parser::parseMtllib(std::ifstream &s) {
    std::string line;
    getline(s, line);
    std::istringstream is(line);
    std::string name;
    is >> name;
    mtlfilepath = Strutils::getPath(filepath) + name;
    mtlfilename = name;
}

Material *Parser::parseUseMtl(std::ifstream &s) {
    std::string line;
    getline(s, line);
    std::istringstream is(line);
    std::string name;
    is >> name;
    Material *m = findMtl(name);
    if (m == nullptr) {
        m = new Material();
        m->name = name;
        materials.push_back(m);
    }
    return m;
}


Parser::mtlLineType Parser::mtlParseType(std::ifstream &s) {
    const int kwSize = 10;
    const std::tuple<std::string, mtlLineType> keywords[kwSize] = {
            std::make_tuple("Ns", mtlLineType::NS),
            std::make_tuple("Ka", mtlLineType::KA),
            std::make_tuple("Kd", mtlLineType::KD),
            std::make_tuple("Ks", mtlLineType::KS),
            std::make_tuple("Ke", mtlLineType::KE),
            std::make_tuple("Ni", mtlLineType::NI),
            std::make_tuple("d", mtlLineType::D),
            std::make_tuple("illum", mtlLineType::ILLUM),
            std::make_tuple("newmtl", mtlLineType::NEWMTL),
            std::make_tuple("#", mtlLineType::SHARP)
    };


    std::string word;
    s >> word;

    for (int i = 0; i < kwSize; ++i) {
        if (word.compare(std::get<0>(keywords[i])) == 0) {
            return std::get<1>(keywords[i]);
        }

    }


    return mtlLineType::ERROR;
}

std::vector<Material *> Parser::parseMtl() {

    std::ifstream s = std::ifstream(mtlfilepath);
    if (!s) {
        // no texture file found
        std::cerr << "No associated MTL file found." << std::endl;
        return materials;
    }
    std::string line;
    Material *currMat = nullptr;

    while (!s.eof()) {

        mtlLineType type = mtlParseType(s);

        // exclude SHARP lines
        if (type == mtlLineType::SHARP) {
            // ignore line
            getline(s, line);
            continue;
        }

        // Could not parse line -> "ERROR"
        if (type == mtlLineType::ERROR) {
            // ignore line
            getline(s, line);
            std::cerr << "couldn't parse line: ... " << line << std::endl;
            continue;
        }

        switch (type) {

            case mtlLineType::NEWMTL:
                currMat = parseMtl(s);
                break;

            case mtlLineType::NS:
                currMat->ns = parseDbl(s);
                break;

            case mtlLineType::KA:
                currMat->ka = parseColor(s);
                break;

            case mtlLineType::KD:
                currMat->kd = parseColor(s);
                break;

            case mtlLineType::KS:
                currMat->ks = parseColor(s);
                break;

            case mtlLineType::KE:
                currMat->ke = parseColor(s);
                break;

            case mtlLineType::NI:
                currMat->ni = parseDbl(s);
                break;

            case mtlLineType::D:
                currMat->d = parseDbl(s);
                break;
            case mtlLineType::ILLUM:break;
        }

    }

    s.close();
    return materials;
}

Material *Parser::parseMtl(std::ifstream &s) {
    std::string line;
    getline(s, line);
    std::istringstream is(line);
    std::string name;
    is >> name;
    Material *m = findMtl(name);
    if (m == nullptr) {
        m = new Material();
        m->name = name;
        materials.push_back(m);
    }
    return m;
}

Color Parser::parseColor(std::ifstream &s) {
    std::string line;
    getline(s, line);
    std::istringstream is(line);
    double r = 0.0, g = 0.0, b = 0.0;
    is >> r >> g >> b;
    return Color(r, g, b);
}

double Parser::parseDbl(std::ifstream &s) {
    std::string line;
    getline(s, line);
    std::istringstream is(line);
    double n = 0.0;
    is >> n;
    return n;
}

Material *Parser::findMtl(const std::string &name) {
    for (Material *mtl : materials) {
        if (mtl->name == name)
            return mtl;
    }
    return nullptr;
}

