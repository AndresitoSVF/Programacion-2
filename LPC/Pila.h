#pragma once
#include "Nodo.h"

template <class Element>
class Pila {
private:
    Nodo<Element> *head;
    int size;

public:
    Pila();
    Pila(const Pila &otra);
    ~Pila();
    void copiar(Nodo<Element>* nodo);
    void vaciar();
    void apilar(Element &info);
    Element& getTop() const;
    void desapilar();
    bool esVacia() const;
    int getLongitud() const;
    void destroy();
    void mostrar() const;

    template <typename E> friend std::ostream& operator << (std::ostream& os, const Pila<E>& pila);//
    void operator = (const Pila<Element> &otra);
};

#include "Pila.cpp"