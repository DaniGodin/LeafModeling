//
// Created by revetoon on 3/1/19.
//

#include <tuple>
#include <sstream>
#include "Parser.hh"
#include "Utils/Strutils.hh"

Parser::Parser(std::string filename) : filename(filename) {}

Parser::lineType Parser::parseType(std::ifstream &s) {
    const int kwSize = 9;
    const std::tuple<std::string, lineType> keywords[kwSize] = {
            std::make_tuple("v", lineType::V),
            std::make_tuple("vt", lineType::VT),
            std::make_tuple("vn", lineType::VN),
            std::make_tuple("vp", lineType::VP),
            std::make_tuple("f", lineType::F),
            std::make_tuple("l", lineType::L),
            std::make_tuple("p", lineType::P),
            std::make_tuple("o", lineType::O),
            std::make_tuple("#", lineType::SHARP)
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
    std::ifstream s = std::ifstream(filename);
    Object *currObj = new Object();
    bool firstObjectEmpty = true;
    Scene *scene = new Scene();

    // buffer line for SHARP
    std::string line;

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
                if (!firstObjectEmpty)
                    scene->push(currObj);
//                    scene->getObjects().push_back(std::move(currObj));
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
                currObj->push(parseF(s, currObj));
//                currObj.getFaceEls().push_back(parseF(s, currObj));
                break;

            case lineType::SHARP:
                // shouldnt happen
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
            case lineType::ERROR:break;
        }
        firstObjectEmpty = false;
    }
    scene->push(currObj);
//    scene->getObjects().push_back(std::move(currObj));
    return scene;
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

FaceEl Parser::parseF(std::ifstream &s, Object *currObj) {
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
        el.push(tuple[0] == INT32_MIN ? nullptr : currObj->getV ()[tuple[0] - globalVCount], tuple[0] - globalVCount,
                tuple[1] == INT32_MIN ? nullptr : currObj->getVt()[tuple[1] - globalVtCount], tuple[1] - globalVtCount,
                tuple[2] == INT32_MIN ? nullptr : currObj->getVn()[tuple[2] - globalVnCount], tuple[2] - globalVnCount);
//        el.getVertices().push_back(std::make_tuple(
//                std::make_tuple<int, Point3D*>(tuple[0] - 1, tuple[0] == INT32_MIN ? nullptr : &currObj.getV ()[tuple[0] - 1]),
//                std::make_tuple<int, Texture2D*>(tuple[1] - 1, tuple[1] == INT32_MIN ? nullptr : &currObj.getVt()[tuple[1] - 1]),
//                std::make_tuple<int, Vector3D*>(tuple[2] - 1, tuple[2] == INT32_MIN ? nullptr : &currObj.getVn()[tuple[2] - 1])));
    }
    return el;
}

Object *Parser::parseO(std::ifstream &s) {
    std::string line;
    getline(s, line);
    line = Strutils::trim(line);
    return new Object(line);;
}
