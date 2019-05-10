//
// Created by revetoon on 3/1/19.
//

#include "Strutils.hh"

std::string Strutils::trim(const std::string& str)
{
    unsigned long first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::string Strutils::rmExtension(const std::string &str) {
    return str.substr(0, str.rfind('.'));
}

std::string Strutils::getPath(const std::string &fullpath) {
    auto i = fullpath.rfind('/');
    if (i == std::string::npos) {
        return fullpath;
    }
    return fullpath.substr(0, i+1);
}
