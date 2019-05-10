//
// Created by revetoon on 3/1/19.
//

#include "Element.hh"

Element::Element(Object *parent)
    : parent(parent)
{}

Element::Element(Object *parent, Material *mat)
    :parent(parent), mat(mat)
{}

void Element::setMat(Material *mat) {
    Element::mat = mat;
}

Material *Element::getMat() const {
    return mat;
}
