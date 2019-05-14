//
// Created by revetoon on 3/2/19.
//

#include <iomanip>
#include "Generator.hh"
#include "../Constants.hh"
#include "../Utils/Strutils.hh"

Generator::Generator(const std::string &filename)
        : filename(filename)
{}

Generator::Generator(const std::string &filename, const std::string &mtlfilename)
        : filename(filename), mtlfilename(mtlfilename)
{}

void Generator::write(Scene *s) {
    if (mtlfilename.empty())
        if (s->getMtllib().empty())
            mtlfilename = Strutils::rmExtension(filename) + ".mtl";
        else
            mtlfilename = s->getMtllib();

    writeObj(s->getObjects());
    writeMtl(s->getMaterials());
}

std::string Generator::writeObj(std::vector<Object *> objs) {
    std::ofstream os = std::ofstream(filename);
    os << std::fixed << std::setprecision(constants::OBJ_DBL_PRECISION);

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

    // write mtllib
    writeMtllib(os, mtlfilename);

    for (auto *o : objs) {

        // v, vn, vt, vp count per object
        unsigned objectVCount = 0;
        unsigned objectVnCount = 0;
        unsigned objectVtCount = 0;
        unsigned objectVpCount = 0;

        // get classified elements
        auto classifiedFaces = classifyByMaterial(o);


        // write o
        writeO(os, *o);
        // write v
        for (auto &v : o->getV()) {
            writeV(os, *v);
            ++objectVCount;
        }
        // write vt
        for (auto &vt : o->getVt()) {
            writeVt(os, *vt);
            ++objectVtCount;
        }

        // write vn
        for (auto &vn : o->getVn()) {
            writeVn(os, *vn);
            ++objectVnCount;
        }

        // write vp
        for (auto &vp : o->getVp()) {
            writeVp(os, *vp);
            ++objectVpCount;
        }


        // write s
        // TODO

        // write p
        // TODO for (auto &p : o.getPoints()) {}

        // write l
        for (auto &l : o->getLineEls()) {
            writeL(os, l, *o);
        }

        // write f
//        for (auto &f : o->getFaceEls()) {
//            writeF(os, f, *o);
//        }
        // write f & usemtl
        for (auto&[mat, list] : classifiedFaces) {
            if (mat != nullptr)
                writeUsemtl(os, *mat);
            for (FaceEl *f : list) {
                writeF(os, *f, *o);
            }
        }

        // update global v, vn, vt, vp count with current object count
        globalVCount += objectVCount;
        globalVnCount += objectVnCount;
        globalVtCount += objectVtCount;
        globalVpCount += objectVpCount;
    }

    return filename;
}

std::string Generator::writeMtl(std::vector<Material *> mtls) {
    std::ofstream os = std::ofstream(mtlfilename);
    os << std::fixed << std::setprecision(constants::OBJ_DBL_PRECISION);

    for (auto *m : mtls) {

        // write newmtl
        writenewMtl(os, m->name);
        // write Ns
        writeDbl(os, "Ns", m->ns);
        // write Ka
        writeColor(os, "Ka", m->ka);
        // write Kd
        writeColor(os, "Kd", m->kd);
        // write Ks
        writeColor(os, "Ks", m->ks);
        // write Ke
        writeColor(os, "Ke", m->ke);
        // write Ni
        writeDbl(os, "Ni", m->ni);
        // write d
        writeDbl(os, "d", m->d);
        // write illum
        writeInt(os, "illum", m->illum);
        // write map_Kd
        writeString(os, "map_Kd", m->map_Kd);
        os << std::endl;
    }
    os.close();
    return mtlfilename;
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
    s << "vt " << vt.getU() << " " << vt.getV();
    if (vt.getW() != 0)
        s << " " << vt.getW();
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

std::unordered_map<Material *, std::vector<FaceEl *>> Generator::classifyByMaterial(Object *o) {
    auto elems = std::unordered_map<Material *, std::vector<FaceEl *>>();

    for (FaceEl &f : o->getFaceEls()) {
        elems.insert(std::make_pair(f.getMat(), std::vector<FaceEl *>()));
        elems[f.getMat()].push_back(&f);
    }

    return elems;
}

void Generator::writeMtllib(std::ofstream &s, const std::string &mtllib) {
    s << "mtllib " << mtllib << std::endl;
}

void Generator::writeUsemtl(std::ofstream &s, Material &m) {
    s << "usemtl " << m.name << std::endl;
}

void Generator::writenewMtl(std::ofstream &s, const std::string &name) {
    s << "newmtl " << name << std::endl;
}

void Generator::writeDbl(std::ofstream &s, const std::string &name, double dbl) {
    s << name << " " << dbl << std::endl;
}

void Generator::writeInt(std::ofstream &s, const std::string &name, int i) {
    s << name << " " << i << std::endl;
}

void Generator::writeColor(std::ofstream &s, const std::string &name, Color &c) {
    s << name << " " << c.getR() << " " << c.getG() << " " << c.getB() << std::endl;
}

void Generator::writeString(std::ofstream &s, const std::string &name, const std::string &value) {
    s << name << " " << value << std::endl;
}



