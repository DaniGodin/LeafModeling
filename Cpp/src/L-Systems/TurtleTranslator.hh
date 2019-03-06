//
// Created by revetoon on 3/4/19.
//

#ifndef OBJPARSER_TURTLETRANSLATOR_HH
#define OBJPARSER_TURTLETRANSLATOR_HH


#include <stack>
#include "LTranslator.hh"
#include "Turtle.hh"

class TurtleTranslator : public LTranslator<std::string> {

public:

    TurtleTranslator(const std::string &rleft, const std::string &rright, const std::string &forward);

    TurtleTranslator(const std::vector<std::string> &rleft, const std::vector<std::string> &rright,
                     const std::vector<std::string> &forward);

    TurtleTranslator(const std::vector<std::string> &rleft, const std::vector<std::string> &rright,
                     const std::vector<std::string> &rup, const std::vector<std::string> &rdown,
                     const std::vector<std::string> &rrolll, const std::vector<std::string> &rrollr,
                     const std::vector<std::string> &rturnaround, const std::vector<std::string> &forward);

    TurtleTranslator(double angle);

    Object transcript(LObject<std::string> lobj) override;

private:
    double DegreesToRadians(double degrees);

    void rotateDir(Vector3D rotVect, double angle);

    void rotateDir(double angle);

    bool compareAll(const std::string &l, const std::vector<std::string> &r);

    void pushturtle();

    void popturtle();

private:
    std::vector<std::string> rleft              = {"+"};
    std::vector<std::string> rright             = {"-"};
    std::vector<std::string> rup                = {"^"};
    std::vector<std::string> rdown              = {"&"};
    std::vector<std::string> rrolll             = {"\\"};
    std::vector<std::string> rrollr             = {"/"};
    std::vector<std::string> rturnaround        = {"|"};
    std::vector<std::string> forward            = {"F"};
    std::vector<std::string> puturtle           = {"["};
    std::vector<std::string> poturtle           = {"]"};
    Object obj;
    Turtle turtle;
    std::stack<Turtle> turtles;
    double angle = 90.0; // degree
};

#include "TurtleTranslator.hxx"

#endif //OBJPARSER_TURTLETRANSLATOR_HH
