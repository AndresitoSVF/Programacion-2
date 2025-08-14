#pragma once
#include "Nodo.h"

template <class Element>
class Cola {
private:
    Nodo<Element> *head;
    Nodo<Element> *tail;
    int size;

public:
    Cola();
    Cola(const Cola &otra);
    ~Cola();
    void vaciar();
    void encolar(Element &info);
    Element& getHead() const;
    Element& getTail() const;
    void desencolar();
    bool esVacia() const;
    int getLongitud() const;
    void destroy();
    void mostrar() const;
    template <typename E> friend std::ostream&      operator << (std::ostream& os, const Cola<E>& cola);//
};

#include "Cola.cpp"