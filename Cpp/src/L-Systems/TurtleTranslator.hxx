//
// Created by revetoon on 3/4/19.
//

#include <cmath>
#include "TurtleTranslator.hh"

TurtleTranslator::TurtleTranslator(const std::string &left, const std::string &right, const std::string &forward)
        : left(left), right(right), forward(forward), dir(1, 0, 0) {}


Object TurtleTranslator::transcript(LObject<std::string> lobj) {

    unsigned index = 0;
    double angleR = DegreesToRadians(90);
    obj.getV().push_back(std::move(curr));
    for (const LNode<std::string> &n : lobj.getNodes()) {
        // each node
        if (n.getId().compare(forward) == 0) {
            // go forward
            curr = curr + dir;
        } else if (n.getId().compare(left) == 0) {
            // turn left 90°
            dir = rotateDir(dir, -angleR);
        } else if (n.getId().compare(right) == 0) {
            // turn right 90°
            dir = rotateDir(dir, angleR);
        } else {
            // NOTHING
        }
        obj.getV().push_back(std::move(curr));
        ++index;
        // create line
        LineEl l = LineEl();
        l.getVertices().push_back(
                std::make_tuple(
                        std::make_tuple<int, Point3D*>(index - 1, &obj.getV()[index - 1]),
                        std::make_tuple<int, Texture2D*>(0, nullptr)
                        )
            );
        l.getVertices().push_back(
                std::make_tuple(
                        std::make_tuple<int, Point3D*>(index, &obj.getV()[index]),
                        std::make_tuple<int, Texture2D*>(0, nullptr)
                )
        );
        // push to obj
        obj.getLineEls().push_back(std::move(l));
    }
    return std::move(obj);
}

double TurtleTranslator::DegreesToRadians(double degrees)
{
    return degrees * M_PIf64 / 180;
}

Vector3D TurtleTranslator::rotateDir(Vector3D dir, double angle) {
    auto rotMat = std::vector<double> { std::cos(angle), -std::sin(angle),
                                        std::sin(angle), std::cos(angle) };

    double x = dir.getX() * rotMat[0] + dir.getY() * rotMat[1];
    double y = dir.getX() * rotMat[2] + dir.getY() * rotMat[3];
    return Vector3D(x, y, 0);
}