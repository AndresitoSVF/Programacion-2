#include "ArbolBin.h"
#include <list>
#include <cstddef>
#include <iostream>
#include <unordered_map>

template <class Element>
void ArbolBin<Element>::mostrarArbol() {
    mostrarArbol(raiz);
}

template <class Element>
void ArbolBin<Element>::mostrarArbol(NodoAB<Element> *nodo) {
    if (nodo == NULL) {
        return;
    }

    if (nodo->getHijoIzq() != NULL){
        std::cout << nodo->getHijoIzq()->getInfo();
    } else {
        std::cout << " * ";
    }
    
    std::cout << " <- [ " << nodo->getInfo() << " ] -> " ;

    if (nodo->getHijoDer() != NULL){
        std::cout << nodo->getHijoDer()->getInfo();
    } else {
        std::cout << " * ";
    }

    std::cout << std::endl;

    mostrarArbol(nodo->getHijoIzq());
    mostrarArbol(nodo->getHijoDer());
}

template <class Element>
NodoAB<Element>* ArbolBin<Element>::copiarNodos(NodoAB<Element> *raiz) {
    NodoAB<Element>* nodoAct = NULL;
    if (raiz != NULL) {
        nodoAct = new NodoAB<Element>(raiz->getInfo());

        nodoAct->setHijoIzq(copiarNodos(raiz->getHijoIzq()));

        nodoAct->setHijoDer(copiarNodos(raiz->getHijoDer()));

    }
    return nodoAct;
}

template <class Element>
ArbolBin<Element>::ArbolBin() : raiz(NULL), profundidad(0) {}

template <class Element>
ArbolBin<Element>::ArbolBin(const Element &info, const ArbolBin<Element> &A1, const ArbolBin<Element> &A2) {
    this->raiz = new NodoAB<Element>(info);
    this->profundidad = 1 + max(A1.profundidad, A2.profundidad);
    this->raiz->setHijoIzq(copiarNodos(A1.raiz));
    this->raiz->setHijoDer(copiarNodos(A2.raiz));
}

template <class Element>
ArbolBin<Element>::ArbolBin(const ArbolBin<Element> &otro) {
    this->raiz = copiarNodos(otro.raiz);
    this->profundidad = otro.profundidad;
}

template <class Element>
ArbolBin<Element>::~ArbolBin() {
    vaciar();
}

template <class Element> 
void ArbolBin<Element>::vaciar() {
    vaciar(this->raiz);
    profundidad = 0;
    raiz = NULL;
}

template <class Element> 
void ArbolBin<Element>::vaciar(NodoAB<Element>* nodo) {
    if (nodo != NULL) {
        vaciar(nodo->getHijoIzq());
        vaciar(nodo->getHijoDer());
        delete nodo;
    }
}

template <class Element>
Element& ArbolBin<Element>::getRaiz() {
    if (raiz == NULL) {
        throw std::runtime_error("El árbol está vacío, no se puede obtener la raíz.");
    }
    return raiz->getInfo();
}

template <class Element>
ArbolBin<Element> ArbolBin<Element>::getHijoIzq() {
    ArbolBin<Element> arbol;
    if (raiz == NULL) {
        throw std::runtime_error("El árbol está vacío, no se puede obtener el hijo izquierdo.");
    }
    arbol.profundidad = this->profundidad > 0 ? this->profundidad - 1 : 0;
    arbol.raiz = copiarNodos(raiz->getHijoIzq());
    return arbol;
}

template <class Element>
ArbolBin<Element> ArbolBin<Element>::getHijoDer() {
    ArbolBin<Element> arbol;
    if (raiz == NULL) {
        throw std::runtime_error("El árbol está vacío, no se puede obtener el hijo derecho.");
    }
    arbol.profundidad = this->profundidad > 0 ? this->profundidad - 1 : 0;
    arbol.raiz = copiarNodos(raiz->getHijoDer());
    return arbol;
}

template <class Element>
int ArbolBin<Element>::getProfundidad() {
    return profundidad;
}

template <class Element>
bool ArbolBin<Element>::esVacio() {
    return profundidad == 0;
}

// recorrido ..

template <class Element>
std::list<Element> ArbolBin<Element>::recorrerPreorden() {
    std::list<Element> resultado = std::list<Element>();
    recorrerPreorden(resultado, raiz);
    return resultado;
}

template <class Element>
void ArbolBin<Element>::recorrerPreorden(std::list<Element> &resultado, NodoAB<Element> *nodoActual) {
    if (nodoActual != NULL) {
        resultado.push_back(nodoActual->getInfo());
        recorrerPreorden(resultado, nodoActual->getHijoIzq());
        recorrerPreorden(resultado, nodoActual->getHijoDer());
    }
}

template <class Element>
std::list<Element> ArbolBin<Element>::recorrerInorden() {
    std::list<Element> resultado = std::list<Element>();
    recorrerInorden(resultado, raiz);
    return resultado;
}

template <class Element>
void ArbolBin<Element>::recorrerInorden(std::list<Element> &resultado, NodoAB<Element> *nodoActual) {
    if (nodoActual != NULL) {
        recorrerInorden(resultado, nodoActual->getHijoIzq());
        resultado.push_back(nodoActual->getInfo());
        recorrerInorden(resultado, nodoActual->getHijoDer());
    }
}

template <class Element>
std::list<Element> ArbolBin<Element>::recorrerPostorden() {
    std::list<Element> resultado = std::list<Element>();
    recorrerPostorden(resultado, raiz);
    return resultado;
}

template <class Element>
void ArbolBin<Element>::recorrerPostorden(std::list<Element> &resultado, NodoAB<Element> *nodoActual) {
    if (nodoActual != NULL) {
        recorrerPostorden(resultado, nodoActual->getHijoIzq());
        recorrerPostorden(resultado, nodoActual->getHijoDer());
        resultado.push_back(nodoActual->getInfo());
    }
}

// creación ..

template <class Element>
void ArbolBin<Element>::postorden(std::list<Element> &listaInorden, std::list<Element> &listaPostorden) {
    if (listaInorden.size() != listaPostorden.size()){
        throw std::runtime_error("Las listas que forman el arbol tienen longitudes distintas");
    }

    vaciar();

    if (listaInorden.empty()) {
        return; 
    }

    typename std::list<Element>::reverse_iterator iteradorPostorden = listaPostorden.rbegin();
    std::unordered_map<Element, int> inordenMap;
    int i = 0;
    
    for (typename std::list<Element>::iterator it = listaInorden.begin(); it != listaInorden.end(); it++) {
        inordenMap[*it] = i;
        i++;
    }

    int p = 0;
    this->raiz = new NodoAB<Element>(*iteradorPostorden); 
    iteradorPostorden++;
    crearPostorden(this->raiz, inordenMap, listaPostorden, iteradorPostorden, p, 0, listaInorden.size() - 1);
    this->profundidad = p;
}

template <class Element>
void ArbolBin<Element>::crearPostorden(NodoAB<Element>* nodoPadre,
                                       std::unordered_map<Element, int> &inordenMap,
                                       std::list<Element> &listaPostorden, 
                                       typename std::list<Element>::reverse_iterator &iteradorPostorden, 
                                       int &profundidad,
                                       int inicio,
                                       int fin) {
    int i = inordenMap[nodoPadre->getInfo()];
    
    int profundidadIzq = 0, profundidadDer = 0;

    if (i < fin && iteradorPostorden != listaPostorden.rend()){
        NodoAB<Element>* nuevoNodo = new NodoAB<Element>(*iteradorPostorden);
        nodoPadre->setHijoDer(nuevoNodo);
        iteradorPostorden++;
        crearPostorden(nuevoNodo, inordenMap, listaPostorden, iteradorPostorden, profundidadDer, i + 1, fin);
    }
    
    if (inicio < i && iteradorPostorden != listaPostorden.rend()){
        NodoAB<Element>* nuevoNodo = new NodoAB<Element>(*iteradorPostorden);
        nodoPadre->setHijoIzq(nuevoNodo);
        iteradorPostorden++;
        crearPostorden(nuevoNodo, inordenMap, listaPostorden, iteradorPostorden, profundidadIzq, inicio, i - 1);
    }

    profundidad = 1 + max(profundidadIzq, profundidadDer);
}

template <class Element>
void ArbolBin<Element>::preorden(std::list<Element> &listaInorden, std::list<Element> &listaPreorden) {
    if (listaInorden.size() != listaPreorden.size()){
        throw std::runtime_error("Las listas que forman el arbol tienen longitudes distintas");
    }

    vaciar();

    if (listaInorden.empty()) {
        return; 
    }

    typename std::list<Element>::iterator iteradorPreorden = listaPreorden.begin();
    std::unordered_map<Element, int> inordenMap;
    int i = 0;
    
    for (typename std::list<Element>::iterator it = listaInorden.begin(); it != listaInorden.end(); it++) {
        inordenMap[*it] = i;
        i++;
    }

    int p = 0;
    this->raiz = new NodoAB<Element>(*iteradorPreorden); 
    iteradorPreorden++;
    crearPreorden(this->raiz, inordenMap, listaPreorden, iteradorPreorden, p, 0, listaInorden.size() - 1);
    this->profundidad = p;
}


template <class Element>
void ArbolBin<Element>::crearPreorden(NodoAB<Element>* nodoPadre,
                                       std::unordered_map<Element, int> &inordenMap,
                                       std::list<Element> &listaPreorden, 
                                       typename std::list<Element>::iterator &iteradorPreorden, 
                                       int &profundidad,
                                       int inicio,
                                       int fin) {

    if (inicio > fin || iteradorPreorden == listaPreorden.end()){
        profundidad = 0;
        return;
    }
    
    int i = inordenMap[nodoPadre->getInfo()];

    int profundidadIzq = 0, profundidadDer = 0;

    if (inicio <= i - 1 && iteradorPreorden != listaPreorden.end()){
        NodoAB<Element>* nuevoNodo = new NodoAB<Element>(*iteradorPreorden);
        nodoPadre->setHijoIzq(nuevoNodo);
        iteradorPreorden++;
        crearPreorden(nuevoNodo, inordenMap, listaPreorden, iteradorPreorden, profundidadIzq, inicio, i - 1);
    }
    
    if (i + 1 <= fin && iteradorPreorden != listaPreorden.end()){
        NodoAB<Element>* nuevoNodo = new NodoAB<Element>(*iteradorPreorden);
        nodoPadre->setHijoDer(nuevoNodo);
        iteradorPreorden++;
        crearPreorden(nuevoNodo, inordenMap, listaPreorden, iteradorPreorden, profundidadDer, i + 1, fin);
    }
    
    profundidad = 1 + max(profundidadIzq, profundidadDer);
}

template <class Element>
ArbolBin<Element>& ArbolBin<Element>::operator=(const ArbolBin<Element>& otro) {
    vaciar();
    this->raiz = copiarNodos(otro.raiz);
    this->profundidad = otro.profundidad;
    return *this;
}

template <class Element>
int ArbolBin<Element>::max(int a, int b) {
    return a > b ? a : b;
}
