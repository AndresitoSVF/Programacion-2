#include "NodoAN.h"
#include <iostream>
#include <cstddef>
template <class Element>
NodoAN<Element>::NodoAN() : hijoIzq(NULL), herDer(NULL), info() {}

template <class Element>
NodoAN<Element>::NodoAN(const Element &info, NodoAN<Element> *hijoIzq, NodoAN<Element> *herDer) : info(info), hijoIzq(hijoIzq), herDer(herDer) {}
    
template <class Element>
Element& NodoAN<Element>::getInfo() {return info;}
    
template <class Element>
NodoAN<Element> *NodoAN<Element>::getHijoIzq(){return hijoIzq;}
    
template <class Element>
NodoAN<Element> *NodoAN<Element>::getHerDer() {return herDer;}
    
template <class Element>
void NodoAN<Element>::setInfo(const Element &info) {this->info = info;}
    
template <class Element>
void NodoAN<Element>::setHijoIzq(NodoAN<Element> *nuevoHijoIzq) {hijoIzq = nuevoHijoIzq;}
    
template <class Element>
void NodoAN<Element>::setHerDer(NodoAN<Element> *nuevoHerDer) {herDer = nuevoHerDer;}
