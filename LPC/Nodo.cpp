#include "Nodo.h"
#include <iostream>
#include <cstddef>

// Constructor por defecto
template <class Element>
Nodo<Element>::Nodo() : sig(NULL), info(Element()) {}

// Constructor de copia
// Crea un nuevo nodo con la misma información que otro nodo
template <class Element>
Nodo<Element>::Nodo(const Nodo *otro) : info(Element(otro->info)) {
    if (otro->sig)
    {
        sig = new Nodo<Element>(otro->sig);
    }
    else
    {
        sig = NULL;
    }
    
}

// Constructor con información y siguiente nodo
// Crea un nuevo nodo con la información dada y el siguiente nodo dado
template <class Element>
Nodo<Element>::Nodo(Element info, Nodo *sig) : sig(sig), info(Element(info)) {}


// Métodos de acceso y modificación
// Devuelve la información del nodo
template <class Element>
Element Nodo<Element>::getInfo() {
    return info;
}

// Devuelve el siguiente nodo
// Devuelve un puntero al siguiente nodo
template <class Element>
Nodo<Element> *Nodo<Element>::getSig() {
    return sig;
}

// Establece la información del nodo
// Establece la información del nodo a la dada
template <class Element>
void Nodo<Element>::setInfo(Element info) {
    this->info = info;
}

// Establece el siguiente nodo
// Establece el siguiente nodo a la dada
template <class Element>
void Nodo<Element>::setSig(Nodo *sig) {
    this->sig = sig;
}

template <class Element>
std::ostream& operator << (std::ostream& os, const Nodo<Element>* nodo) {
    if (nodo == NULL) {
        os << "( Nodo vacío )";
        return os;
    }

    os << "( actual info: " << nodo->info << ", sig: "; 
    nodo = nodo->sig;
    while (nodo != NULL) {
        os << nodo->info;
        nodo = nodo->sig;
        if (nodo) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}
