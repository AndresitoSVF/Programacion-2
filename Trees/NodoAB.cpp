#include "NodoAB.h"
#include <cstddef>

template <class Element>
NodoAB<Element>::NodoAB() : hijoDer(NULL), hijoIzq(NULL), info() {}

template <class Element>
NodoAB<Element>::NodoAB(const Element &info, NodoAB<Element> *hijoIzq, NodoAB<Element> *hijoDer) : info(info), hijoIzq(hijoIzq), hijoDer(hijoDer){}

template <class Element>
Element& NodoAB<Element>::getInfo() { return info;}

template <class Element>
NodoAB<Element> *NodoAB<Element>::getHijoIzq() { return hijoIzq;}

template <class Element>
NodoAB<Element>*& NodoAB<Element>::getHijoIzqRef() { return hijoIzq; }

template <class Element>
NodoAB<Element> *NodoAB<Element>::getHijoDer() { return hijoDer;}

template <class Element>
NodoAB<Element>*& NodoAB<Element>::getHijoDerRef() { return hijoDer; }

template <class Element>
void NodoAB<Element>::setInfo(const Element &info) { this->info = info;}

template <class Element>
void NodoAB<Element>::setHijoIzq(NodoAB<Element> *nuevoHijoIzq) { hijoIzq = nuevoHijoIzq;}

template <class Element>
void NodoAB<Element>::setHijoDer(NodoAB<Element> *nuevoHijoDer) { hijoDer = nuevoHijoDer;}