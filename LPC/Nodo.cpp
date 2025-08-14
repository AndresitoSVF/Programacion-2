#include "Nodo.h"
#include <iostream>
#include <cstddef>

// Constructor por defecto
template <class Element>
Nodo<Element>::Nodo() : sig(NULL), ant(NULL),info() {}

// Constructor con elemento
template <class Element>
Nodo<Element>::Nodo(const Element &info, Nodo *sig, Nodo *ant) : sig(sig), ant(ant), info(info) {}


// Devuelve la información del nodo
template <class Element>
Element& Nodo<Element>::getInfo() { return info;}


// Devuelve un puntero al siguiente nodo
template <class Element>
Nodo<Element> *Nodo<Element>::getSig() { return sig;}


// Devuelve un puntero al anterior nodo
template <class Element>
Nodo<Element> *Nodo<Element>::getAnt() { return ant;}

// Establece la información del nodo

template <class Element>
void Nodo<Element>::setInfo(const Element &info) { this->info = info;}

// Establece el siguiente nodo
template <class Element>
void Nodo<Element>::setSig(Nodo *sig) { this->sig = sig;}

// Establece el nodo anterior
template <class Element>
void Nodo<Element>::setAnt(Nodo *ant) { this->ant = ant;}
