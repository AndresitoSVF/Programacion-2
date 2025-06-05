#pragma once

template<class element>
class NodoArco
{
private:
    element peso;
    NodoVertice info;
    NodoArco sig;
public:
    NodoArco(/* args */);
    ~NodoArco();
};

NodoArco::NodoArco(/* args */)
{
}

NodoArco::~NodoArco()
{
}
