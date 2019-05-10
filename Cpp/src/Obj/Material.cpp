//
// Created by revetoon on 3/1/19.
//

#include "Material.hh"

Material::Material(const std::string &name, double ns, const Color &ka, const Color &kd, const Color &ks,
                   const Color &ke, double ni, double d, int illum)
        : name(name), ns(ns), ka(ka), kd(kd), ks(ks), ke(ke), ni(ni), d(d), illum(illum)
{}

Material::Material(const std::string &name, const Color &ka, const Color &kd, const Color &ks)
        : name(name), ka(ka), kd(kd), ks(ks)
{}

Material::Material() {}

Material::Material(const std::string &name, const Color &ka, const Color &kd, const Color &ks,
                   const std::string &map_Kd) : name(name), ka(ka), kd(kd), ks(ks), map_Kd(map_Kd) {}
