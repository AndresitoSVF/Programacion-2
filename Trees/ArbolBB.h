#pragma once
#include "ArbolBin.h"


template <class Element>
class ArbolBB : public ArbolBin<Element> {
private:
    void insertar(NodoAB<Element>*& nodoActual, const Element& info);
    bool consultar(NodoAB<Element>* nodoActual, const Element& info);
    void eliminar(NodoAB<Element>*& nodoActual, const Element& info);
    NodoAB<Element>* buscarMin(NodoAB<Element>* nodoActual);
    int setProfundidad(NodoAB<Element> *nodo);
public:
    void insertar(const Element& info);
    void eliminar(const Element& info);
    bool consultar(const Element& info);
    int calcularProfundidad();
};

#include "ArbolBB.cpp"