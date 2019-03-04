//
// Created by revetoon on 3/4/19.
//

//#include "LNode.hh"

template <typename T>
T LNode<T>::getId() const {
    return id;
}

template <typename T>
LNode<T>::LNode(T id) : id(id) {}

template<typename T>
bool LNode<T>::operator==(const LNode &rhs) const {
    return id == rhs.id;
}

template<typename T>
bool LNode<T>::operator!=(const LNode &rhs) const {
    return !(rhs == *this);
}
