//
// Created by revetoon on 3/2/19.
//

#include <iomanip>
#include "Generator.hh"

Generator::Generator(const std::string &filename) : filename(filename) {

}


std::string Generator::write(Scene *s) {
    std::ofstream os = std::ofstream(filename);
    os << std::fixed << std::setprecision(8);

    // line write order
    // 1) object
    // 2) v
    // 2) vt
    // 2) vn
    // 2) vp
    // 3) usemtl
    // 4) s
    // 5) p
    // 5) l
    // 5) f

    for (auto &o : s->getObjects()) {

        // v, vn, vt, vp count per object
        unsigned objectVCount = 0;
        unsigned objectVnCount = 0;
        unsigned objectVtCount = 0;
        unsigned objectVpCount = 0;


        // write o
        writeO(os, o);
        // write v
        for (auto &v : o.getV()) {
            writeV(os, *v);
            ++objectVCount;
        }
        // write vt
        for (auto &vt : o.getVt()) {
            writeVt(os, *vt);
            ++objectVtCount;
        }

        // write vn
        for (auto &vn : o.getVn()) {
            writeVn(os, *vn);
            ++objectVnCount;
        }

        // write vp
        for (auto &vp : o.getVp()) {
            writeVp(os, *vp);
            ++objectVpCount;
        }

        // write usemtl
        // TODO

        // write s
        // TODO

        // write p
        // TODO for (auto &p : o.getPoints()) {}

        // write l
        for (auto &l : o.getLineEls()) {
            writeL(os, l, o);
        }

        // write f
        for (auto &f : o.getFaceEls()) {
            writeF(os, f, o);
        }

        // update global v, vn, vt, vp count with current object count
        globalVCount += objectVCount;
        globalVnCount += objectVnCount;
        globalVtCount += objectVtCount;
        globalVpCount += objectVpCount;
    }

    return filename;
}

void Generator::writeO(std::ofstream &s, Object &o) {
    s << "o " << o.getName() <<std::endl;
}

void Generator::writeV(std::ofstream &s, Point3D &v) {
    s << "v " << v.getX() << " " << v.getY() << " " << v.getZ();
    if (v.getW() != 1.0)
        s << " " << v.getW();
    s << std::endl;
}

void Generator::writeVt(std::ofstream &s, Texture2D &vt) {
    s << "vt " << vt.getU();
    if(vt.getV() != 0 || vt.getW() != 0) {
        s << " " << vt.getV();
        if (vt.getW() != 0)
            s << " " << vt.getW();
    }
    s << std::endl;
}

void Generator::writeVn(std::ofstream &s, Vector3D &vn) {
    s << "vn " << vn.getX() << " " << vn.getY() << " " << vn.getZ() << std::endl;
}

void Generator::writeVp(std::ofstream &s, Point2D &vp) {
    s << "vp " << vp.getU() << " " << vp.getV();
    if (vp.getW() != 1.0)
        s << " " << vp.getW();
    s << std::endl;
}

void Generator::writeL(std::ofstream &s, LineEl &l, Object &o) {
    s << "l";
    for (auto &tuple : l.getVertices()) {
        s << " ";
        // write index of v
        Point3D_i &v = std::get<0>(tuple);
        if (std::get<1>(v) != nullptr) {
            s << std::get<0>(v) + globalVCount;
        }
        s << "/";
        // write index of vt
        Texture2D_i &vt = std::get<1>(tuple);
        if (std::get<1>(vt) != nullptr) {
            s << std::get<0>(vt) + globalVtCount;
        }
    }
    s << std::endl;
}

void Generator::writeF(std::ofstream &s, FaceEl &f, Object &o) {
    s << "f";
    for (auto &tuple : f.getVertices()) {
        s << " ";
        // write index of v
        Point3D_i &v = std::get<0>(tuple);
        if (std::get<1>(v) != nullptr) {
            s << std::get<0>(v) + globalVCount;
        }
        s << "/";
        // write index of vt
        Texture2D_i &vt = std::get<1>(tuple);
        if (std::get<1>(vt) != nullptr) {
            s << std::get<0>(vt) + globalVtCount;
        }
        s << "/";
        // write index of vn
        Vector3D_i &vn = std::get<2>(tuple);
        if (std::get<1>(vn) != nullptr) {
            s << std::get<0>(vn) + globalVnCount;
        } else if (std::get<1>(f.getGlobalNormal()) != nullptr) {
            // global normal set
            s << std::get<0>(f.getGlobalNormal()) + globalVnCount;
        }
    }
    s << std::endl;
}


