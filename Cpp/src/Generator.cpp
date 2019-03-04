//
// Created by revetoon on 3/2/19.
//

#include <iomanip>
#include "Generator.hh"

Generator::Generator(const std::string &filename) : filename(filename) {

}


Object Generator::generate(Node *root, std::string name) {
    Object o = Object(name);

    // push the root
    o.getV().push_back(std::move(root->getPt()));
    genTreeO(root, o, 0);
    return o;
}

void Generator::genTreeO(Node *n, Object &o, long rootIndex) {
    // root already pushed -> gotta find its index
//    auto it = std::find(o.getV().begin(), o.getV().end(), n);
//    if (it == std::end(o.getV())) {
//        std::cerr << "Error in getV" << std::endl;
//        return;
//    }
//    // index of root
//    long rootIndex = std::distance(o.getV().begin(), it);

    // iterate through children (tree structure so each child is a new node)
    for (auto &c : n->getChildren()) {
        // push child & get its index
        long index = o.getV().size();
        o.getV().push_back(std::move(c->getPt()));
        // create line elt from root to child
        LineEl l = LineEl();
        // root pt
        l.getVertices().push_back(
                std::make_tuple(
                        std::make_tuple<int, Point3D *>(rootIndex, &o.getV()[rootIndex]),
                        std::make_tuple<int, Texture2D *>(0, nullptr))
                );
        // child pt
        l.getVertices().push_back(
                std::make_tuple(
                        std::make_tuple<int, Point3D *>(index, &o.getV()[index]),
                        std::make_tuple<int, Texture2D *>(0, nullptr))
        );
        // push line elt
        o.getLineEls().push_back(std::move(l));
        // iterate through child
        genTreeO(c, o, index);
    }
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
        // write o
        writeO(os, o);
        // write v
        for (auto &v : o.getV()) {
            writeV(os, v);
        }
        // write vt
        for (auto &vt : o.getVt()) {
            writeVt(os, vt);
        }

        // write vn
        for (auto &vn : o.getVn()) {
            writeVn(os, vn);
        }

        // write vp
        for (auto &vp : o.getVp()) {
            writeVp(os, vp);
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
            s << std::get<0>(v) + 1;
        }
        s << "/";
        // write index of vt
        Texture2D_i &vt = std::get<1>(tuple);
        if (std::get<1>(vt) != nullptr) {
            s << std::get<0>(vt) + 1;
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
            s << std::get<0>(v) + 1;
        }
        s << "/";
        // write index of vt
        Texture2D_i &vt = std::get<1>(tuple);
        if (std::get<1>(vt) != nullptr) {
            s << std::get<0>(vt) + 1;
        }
        s << "/";
        // write index of vn
        Vector3D_i &vn = std::get<2>(tuple);
        if (std::get<1>(vn) != nullptr) {
            s << std::get<0>(vn) + 1;
        }
    }
    s << std::endl;
}
