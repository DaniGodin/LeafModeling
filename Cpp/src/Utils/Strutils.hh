//
// Created by revetoon on 3/1/19.
//

#ifndef OBJPARSER_STRUTILS_HH
#define OBJPARSER_STRUTILS_HH

#include <string>

class Strutils {

public:
    static std::string trim(const std::string& str);

    static std::string rmExtension(const std::string &str);

    static std::string getPath(const std::string &fullpath);
};


#endif //OBJPARSER_STRUTILS_HH
