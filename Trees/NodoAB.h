#pragma once
#include <cstddef>

template <class Element>
class NodoAB {
private:
    Element info;
    NodoAB<Element>* hijoIzq;
    NodoAB<Element>* hijoDer;

public:
    NodoAB();
    NodoAB(const Element &info, NodoAB<Element> *hijoIzq = NULL, NodoAB<Element> *hijoDer = NULL);
    Element& getInfo();
    NodoAB<Element>* getHijoIzq();
    NodoAB<Element>*& getHijoIzqRef();
    NodoAB<Element>* getHijoDer();
    NodoAB<Element>*& getHijoDerRef();
    void setInfo(const Element &info);
    void setHijoIzq(NodoAB<Element> *sig);
    void setHijoDer(NodoAB<Element> *sig);
};
#include "NodoAB.cpp"