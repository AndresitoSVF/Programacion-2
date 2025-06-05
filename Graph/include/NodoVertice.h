#pragma once
#include "NodoArco.h"

template<class element>
class NodoVertice
{
private:
    element info;
    NodoVertice *sig;
    NodoArco *listAdy;
public:
    NodoVertice(/* args */);
    ~NodoVertice();
};

template<class element>
NodoVertice<element>::NodoVertice()
{
    sig = NULL;
    listAdy = NULL;
}

template<class element>
NodoVertice<element>::~NodoVertice()
{
}
