#pragma once
#include <cstddef>
template <class Element>
class Nodo
{
private:
    Nodo *sig;
    Nodo *ant;
    Element info;
public:
    Nodo();
    Nodo(const Element &info, Nodo *sig = NULL, Nodo * ant = NULL);
    Element& getInfo();
    Nodo *getSig();
    Nodo *getAnt();
    void setInfo(const Element &info);
    void setSig(Nodo *sig);
    void setAnt(Nodo *ant);
};
#include "Nodo.cpp"