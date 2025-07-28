#pragma once
#include <cstddef>
template <class Element>
class Nodo
{
private:
    Nodo *sig;
    Element info;
public:
    Nodo();
    Nodo(const Nodo *otro);
    Nodo(Element info, Nodo *sig = NULL);
    Element getInfo();
    Nodo *getSig();
    void setInfo(Element info);
    void setSig(Nodo *sig);
    template <typename T> friend std::ostream& operator << (std::ostream& os, const Nodo<T>* nodo);
};
#include "Nodo.cpp"