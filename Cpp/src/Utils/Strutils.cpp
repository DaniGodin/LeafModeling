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