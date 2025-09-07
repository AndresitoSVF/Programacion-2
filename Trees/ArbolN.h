#pragma once
#include <cstddef>
#include <list>
#include "NodoAN.h"

template <class Element>
class ArbolN {
private:
    NodoAN<Element>* raiz;
    int profundidad;

    NodoAN<Element>* copiarNodos(NodoAN<Element> *raiz);
    void recorrerPreorden(std::list<Element> &resultado, NodoAN<Element> *nodoActual) const;
    void recorrerInorden(std::list<Element> &resultado, NodoAN<Element> *nodoActual) const;
    void recorrerPostorden(std::list<Element> &resultado, NodoAN<Element> *nodoActual) const;
    void vaciar(NodoAN<Element> *nodo);
    void getHojas(std::list<Element> &resultado, NodoAN<Element> *nodoActual) const;
    void copiar(const ArbolN<Element> &otro); // n
    void mostrarPreorden(NodoAN<Element> *nodoActual) const;
    int getProfundidad(NodoAN<Element> * nodo);
    
public:
    ArbolN<Element>(); // 1
    ArbolN<Element>(const Element &info, const std::list<ArbolN<Element> > &hijos); // n
    ArbolN<Element>(const ArbolN<Element> &otro); // n
    ~ArbolN<Element>(); // n
    void vaciar();
    bool esVacio() const; // 1
    Element& getRaiz(); // 1
    std::list<ArbolN<Element> > getHijos(); // n
    void insertarSubArbol(const ArbolN<Element> &subArbol); // n
    void eliminarSubArbol(const int pos); // n
    int getProfundidad() const; // 1
    int calcularProfundidad(); // n
    std::list<Element> recorrerPreorden() const;
    std::list<Element> recorrerInorden() const;
    std::list<Element> recorrerPostorden() const;
    std::list<Element> recorrerNiveles() const;
    std::list<Element> getHojas() const;
    void mostrarPreorden() const;
    ArbolN<Element>& operator=(const ArbolN<Element>& otro);
};
#include "ArbolN.cpp"