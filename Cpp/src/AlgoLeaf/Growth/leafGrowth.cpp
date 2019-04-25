//
// Created by revetoon on 4/22/19.
//

#include <set>
#include <cmath>
#include <exception>
#include "leafGrowth.hh"

void leafGrowth::radialgrow(Object &leaf, double rate) {
    int sides = 3; // assuming triangles
    /*
     *  .-------. <- centerV
     *   \  b  / \
     *    \   / a \
     *     \./_____\.
     *      ^ p1    ^ p2
     *
     *    / <-grwth-> \
     *   v             v
     *
     */
    int centerV = leafCenterIndex(leaf);

    for (FaceEl &f : leaf.getFaceEls()) {
        for (int i = 0; i < sides; ++i) {
            if (f.getIndex(i) == centerV) {
                // this is the center point
                continue;
            } else {
                // get p1 or p2
                Point3D *p = f.getPt(i);
                // calc direction from center
                Vector3D dir = (*p - leaf.getV()[centerV]);
                // calc length
                double l = dir.length();
                // put p1 or p2 a further from center
                *p = *p + dir.normalized() * (l/5 * rate);
            }
        }
    }
}



int leafGrowth::leafCenterIndex(const Object &leaf) {

    // assuming triangles
    int sides = 3;
    int size = leaf.getFaceEls().size();
//    leaf.getFaceEls()[0];
    for (int i = 0; i < sides; ++i) {
        int found = 1; // counting the first one in [0]
        for (int j = 1; j < sides; ++j) {
            for (int k = 0; k < sides; ++k) {
                if (leaf.getFaceEls()[0].getPt(i) == leaf.getFaceEls()[j].getPt(k)) {
                    ++found;
                }
            }
        }
        if (found == sides)
            return leaf.getFaceEls()[0].getIndex(i);
    }
    throw std::invalid_argument("Zero common points were found.");
}

