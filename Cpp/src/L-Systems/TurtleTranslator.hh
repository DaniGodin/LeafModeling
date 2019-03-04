//
// Created by revetoon on 3/4/19.
//

#ifndef OBJPARSER_TURTLETRANSLATOR_HH
#define OBJPARSER_TURTLETRANSLATOR_HH


#include "LTranslator.hh"

class TurtleTranslator : public LTranslator<std::string> {

public:
    TurtleTranslator(const std::string &left, const std::string &right, const std::string &forward);

    Object transcript(LObject<std::string> lobj) override;

private:
    double DegreesToRadians(double degrees);

    Vector3D rotateDir(Vector3D dir, double angle);


private:
    std::string left;
    std::string right;
    std::string forward;
    Object obj;
    Vector3D dir;
    Point3D curr;
};

#include "TurtleTranslator.hxx"

#endif //OBJPARSER_TURTLETRANSLATOR_HH
