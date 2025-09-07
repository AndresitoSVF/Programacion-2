#pragma once
#include <cstddef>

template <class Element>
class NodoAN {
private:
    Element info;
    NodoAN<Element>* hijoIzq;
    NodoAN<Element>* herDer;
public:
    NodoAN();
    NodoAN(const Element &info, NodoAN<Element> *hijoIzq = NULL, NodoAN<Element> *herDer = NULL);
    Element& getInfo();
    NodoAN<Element> *getHijoIzq();
    NodoAN<Element> *getHerDer();
    void setInfo(const Element &info);
    void setHijoIzq(NodoAN<Element> *sig);
    void setHerDer(NodoAN<Element> *sig);
};
#include "NodoAN.cpp"