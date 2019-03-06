//
// Created by revetoon on 3/4/19.
//

#include <cmath>
#include "TurtleTranslator.hh"

TurtleTranslator::TurtleTranslator(const std::string &rleft,
                                   const std::string &rright,
                                   const std::string &forward)
        : rleft({rleft}), rright({rright}), forward({forward}) {}


TurtleTranslator::TurtleTranslator(const std::vector<std::string> &rleft,
                                   const std::vector<std::string> &rright,
                                   const std::vector<std::string> &forward)
        : rleft(rleft), rright(rright), forward(forward) {}


TurtleTranslator::TurtleTranslator(const std::vector<std::string> &rleft, const std::vector<std::string> &rright,
                                   const std::vector<std::string> &rup, const std::vector<std::string> &rdown,
                                   const std::vector<std::string> &rrolll, const std::vector<std::string> &rrollr,
                                   const std::vector<std::string> &rturnaround, const std::vector<std::string> &forward)
        : rleft(rleft), rright(rright), rup(rup), rdown(rdown), rrolll(rrolll), rrollr(rrollr),
          rturnaround(rturnaround), forward(forward) {}

TurtleTranslator::TurtleTranslator(double angle) : angle(angle) {}


Object TurtleTranslator::transcript(LObject<std::string> lobj) {

    unsigned index = 0;
    bool turtleMoved = false;
    double angleR = DegreesToRadians(angle);
    obj.getV().push_back(std::move(turtle.curr));
    for (const LNode<std::string> &n : lobj.getNodes()) {
        turtleMoved = false;
        // each node
        if (compareAll(n.getId(), forward)) {
            // go forward
            turtle.curr = turtle.curr + turtle.tHeading;
            turtleMoved = true;
        } else if (compareAll(n.getId(), rleft)) {
            // turn left 90°
            rotateDir(turtle.tUp, angleR);
        } else if (compareAll(n.getId(), rright)) {
            // turn right 90°
            rotateDir(turtle.tUp, -angleR);
        } else if (compareAll(n.getId(), rup)) {
            // turn right 90°
            rotateDir(turtle.tLeft, -angleR);
        } else if (compareAll(n.getId(), rdown)) {
            // turn right 90°
            rotateDir(turtle.tLeft, angleR);
        } else if (compareAll(n.getId(), rrolll)) {
            // turn right 90°
            rotateDir(turtle.tHeading, angleR);
        } else if (compareAll(n.getId(), rrollr)) {
            // turn right 90°
            rotateDir(turtle.tHeading, -angleR);
        } else if (compareAll(n.getId(), rturnaround)) {
            // turn right 90°
            rotateDir(turtle.tUp, DegreesToRadians(180));
        } else if (compareAll(n.getId(), puturtle)) {
            // turn right 90°
            pushturtle();
        } else if (compareAll(n.getId(), poturtle)) {
            // turn right 90°
            popturtle();
        } else {
            // NOTHING
        }

        // create line
        if (turtleMoved) {
            obj.getV().push_back(std::move(turtle.curr));
            turtle.oldVIndex = turtle.currVIndex;
            turtle.currVIndex = obj.getV().size() - 1;
            LineEl l = LineEl();
            l.getVertices().push_back(
                    std::make_tuple(
                            std::make_tuple<int, Point3D*>(turtle.oldVIndex + 0, &obj.getV()[turtle.oldVIndex]),
                            std::make_tuple<int, Texture2D*>(0, nullptr)
                    )
            );
            l.getVertices().push_back(
                    std::make_tuple(
                            std::make_tuple<int, Point3D*>(turtle.currVIndex + 0, &obj.getV()[turtle.currVIndex]),
                            std::make_tuple<int, Texture2D*>(0, nullptr)
                    )
            );
            // push to obj
            obj.getLineEls().push_back(std::move(l));
        }
    }
    return std::move(obj);
}


double TurtleTranslator::DegreesToRadians(double degrees)
{
    return degrees * M_PIf64 / 180;
}

void TurtleTranslator::rotateDir(double angle) {
    rotateDir(turtle.tUp, angle);
}

void TurtleTranslator::rotateDir(Vector3D rotVect, double angle) {
//    auto rotMat = std::vector<double> { std::cos(angle), -std::sin(angle),
//                                        std::sin(angle), std::cos(angle) };
    auto rotMatU = std::vector<double> { std::cos(angle),  std::sin(angle), 0,
                                         -std::sin(angle), std::cos(angle), 0,
                                         0,                0,               1};

    auto rotMatL = std::vector<double> { std::cos(angle),  0, -std::sin(angle),
                                         0,                1,                0,
                                         std::sin(angle),  0,  std::cos(angle)};

    auto rotMatH = std::vector<double> { 1,               0,                0,
                                         0, std::cos(angle), -std::sin(angle),
                                         0, std::sin(angle),  std::cos(angle) };

    double x, y, z;

    // TODO Clean up this mess

    if (rotVect == turtle.tUp) { // U
        x = turtle.tHeading.getX() * rotMatU[0] + turtle.tHeading.getY() * rotMatU[1] + turtle.tHeading.getZ() * rotMatU[2];
        y = turtle.tHeading.getX() * rotMatU[3] + turtle.tHeading.getY() * rotMatU[4] + turtle.tHeading.getZ() * rotMatU[5];
        z = turtle.tHeading.getX() * rotMatU[6] + turtle.tHeading.getY() * rotMatU[7] + turtle.tHeading.getZ() * rotMatU[8];
        turtle.tHeading = Vector3D(x, y, z);
        x = turtle.tLeft.getX() * rotMatU[0] + turtle.tLeft.getY() * rotMatU[1] + turtle.tLeft.getZ() * rotMatU[2];
        y = turtle.tLeft.getX() * rotMatU[3] + turtle.tLeft.getY() * rotMatU[4] + turtle.tLeft.getZ() * rotMatU[5];
        z = turtle.tLeft.getX() * rotMatU[6] + turtle.tLeft.getY() * rotMatU[7] + turtle.tLeft.getZ() * rotMatU[8];
        turtle.tLeft = Vector3D(x, y, z);
        x = turtle.tUp.getX() * rotMatU[0] + turtle.tUp.getY() * rotMatU[1] + turtle.tUp.getZ() * rotMatU[2];
        y = turtle.tUp.getX() * rotMatU[3] + turtle.tUp.getY() * rotMatU[4] + turtle.tUp.getZ() * rotMatU[5];
        z = turtle.tUp.getX() * rotMatU[6] + turtle.tUp.getY() * rotMatU[7] + turtle.tUp.getZ() * rotMatU[8];
        turtle.tUp = Vector3D(x, y, z);
    }
    if (rotVect == turtle.tLeft) { // L
        x = turtle.tHeading.getX() * rotMatL[0] + turtle.tHeading.getY() * rotMatL[1] + turtle.tHeading.getZ() * rotMatL[2];
        y = turtle.tHeading.getX() * rotMatL[3] + turtle.tHeading.getY() * rotMatL[4] + turtle.tHeading.getZ() * rotMatL[5];
        z = turtle.tHeading.getX() * rotMatL[6] + turtle.tHeading.getY() * rotMatL[7] + turtle.tHeading.getZ() * rotMatL[8];
        turtle.tHeading = Vector3D(x, y, z);
        x = turtle.tLeft.getX() * rotMatL[0] + turtle.tLeft.getY() * rotMatL[1] + turtle.tLeft.getZ() * rotMatL[2];
        y = turtle.tLeft.getX() * rotMatL[3] + turtle.tLeft.getY() * rotMatL[4] + turtle.tLeft.getZ() * rotMatL[5];
        z = turtle.tLeft.getX() * rotMatL[6] + turtle.tLeft.getY() * rotMatL[7] + turtle.tLeft.getZ() * rotMatL[8];
        turtle.tLeft = Vector3D(x, y, z);
        x = turtle.tUp.getX() * rotMatL[0] + turtle.tUp.getY() * rotMatL[1] + turtle.tUp.getZ() * rotMatL[2];
        y = turtle.tUp.getX() * rotMatL[3] + turtle.tUp.getY() * rotMatL[4] + turtle.tUp.getZ() * rotMatL[5];
        z = turtle.tUp.getX() * rotMatL[6] + turtle.tUp.getY() * rotMatL[7] + turtle.tUp.getZ() * rotMatL[8];
        turtle.tUp = Vector3D(x, y, z);
    }
    if (rotVect == turtle.tHeading) { // H
        x = turtle.tHeading.getX() * rotMatH[0] + turtle.tHeading.getY() * rotMatH[1] + turtle.tHeading.getZ() * rotMatH[2];
        y = turtle.tHeading.getX() * rotMatH[3] + turtle.tHeading.getY() * rotMatH[4] + turtle.tHeading.getZ() * rotMatH[5];
        z = turtle.tHeading.getX() * rotMatH[6] + turtle.tHeading.getY() * rotMatH[7] + turtle.tHeading.getZ() * rotMatH[8];
        turtle.tHeading = Vector3D(x, y, z);
        x = turtle.tLeft.getX() * rotMatH[0] + turtle.tLeft.getY() * rotMatH[1] + turtle.tLeft.getZ() * rotMatH[2];
        y = turtle.tLeft.getX() * rotMatH[3] + turtle.tLeft.getY() * rotMatH[4] + turtle.tLeft.getZ() * rotMatH[5];
        z = turtle.tLeft.getX() * rotMatH[6] + turtle.tLeft.getY() * rotMatH[7] + turtle.tLeft.getZ() * rotMatH[8];
        turtle.tLeft = Vector3D(x, y, z);
        x = turtle.tUp.getX() * rotMatH[0] + turtle.tUp.getY() * rotMatH[1] + turtle.tUp.getZ() * rotMatH[2];
        y = turtle.tUp.getX() * rotMatH[3] + turtle.tUp.getY() * rotMatH[4] + turtle.tUp.getZ() * rotMatH[5];
        z = turtle.tUp.getX() * rotMatH[6] + turtle.tUp.getY() * rotMatH[7] + turtle.tUp.getZ() * rotMatH[8];
        turtle.tUp = Vector3D(x, y, z);
    }
//    return newDir;
}


bool TurtleTranslator::compareAll(const std::string &l, const std::vector<std::string> &r) {
    for (auto &s : r) {
        if (l.compare(s) == 0)
            return true;
    }
    return false;
}

void TurtleTranslator::pushturtle() {
    turtles.push(std::move(turtle));
}

void TurtleTranslator::popturtle() {
    turtle = turtles.top();
    turtles.pop();
}


