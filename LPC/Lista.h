#pragma once
#include "Nodo.h"

template <class Element>
class Lista
{
private:
    Nodo<Element> *head;
    Nodo<Element> *tail;
    int size;
    
public:
    Lista();
    Lista(Lista *otra);
    ~Lista() { destroy(); }
    void vaciar();
    void insertar(Element info, int pos = -1);
    Element consultar(int pos);
    Element eliminar(int pos);
    bool esVacia();
    int getLongitud();
    void destroy();
    void mostrar();
};

#include "Lista.cpp"