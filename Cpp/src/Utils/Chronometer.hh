//
// Created by revetoon on 4/27/19.
//

#ifndef OBJPARSER_CHRONOMETER_HH
#define OBJPARSER_CHRONOMETER_HH

#include <chrono>
#include <iostream>
#include <iomanip>

class Chronometer {
    typedef std::chrono::time_point<std::chrono::steady_clock> timePt;

public:
    Chronometer();
    Chronometer(const std::string &name);

    ~Chronometer();

private:
    std::string name = "";
    timePt start = std::chrono::steady_clock().now();
};


#endif //OBJPARSER_CHRONOMETER_HH
