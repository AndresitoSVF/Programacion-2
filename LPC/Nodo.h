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
    Nodo(Nodo *otro);
    Nodo(Element info, Nodo *sig = NULL);
    Element getInfo();
    Nodo *getSig();
    void setInfo(Element info);
    void setSig(Nodo *sig);
};

// Constructor por defecto
template <class Element>
Nodo<Element>::Nodo() : sig(NULL), info(Element()) {}

// Constructor de copia
// Crea un nuevo nodo con la misma información que otro nodo
template <class Element>
Nodo<Element>::Nodo(Nodo *otro) : info(Element(otro->info)) {
    if (otro->sig)
    {
        sig = new Nodo<Element>(otro->sig);
    }
    else
    {
        sig = NULL;
    }
    
}

#include "Nodo.cpp"