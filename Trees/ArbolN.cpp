#pragma once
#include "ArbolN.h"
#include <cstddef>
#include <list>
#include <queue>
#include <stdexcept>
#include <vector>

template <class Element>
NodoAN<Element>* ArbolN<Element>::copiarNodos(NodoAN<Element> *raiz) {
    NodoAN<Element>* nodoAct = NULL;
    if (raiz != NULL) {
        nodoAct = new NodoAN<Element>(raiz->getInfo());

        nodoAct->setHijoIzq(copiarNodos(raiz->getHijoIzq()));

        nodoAct->setHerDer(copiarNodos(raiz->getHerDer()));
    }
    return nodoAct;
}

template <class Element>
std::list<Element> ArbolN<Element>::recorrerPreorden() const{
    std::list<Element> resultado = std::list<Element>();
    recorrerPreorden(resultado, raiz);
    return resultado;
}

template <class Element>
void ArbolN<Element>::recorrerPreorden(std::list<Element> &resultado, NodoAN<Element> *nodoActual) const{
    if (nodoActual != NULL) {
        resultado.push_back(nodoActual->getInfo());
        recorrerPreorden(resultado, nodoActual->getHijoIzq());
        recorrerPreorden(resultado, nodoActual->getHerDer());
    }
}

template <class Element>
std::list<Element> ArbolN<Element>::recorrerInorden() const{
    std::list<Element> resultado = std::list<Element>();
    recorrerInorden(resultado, raiz);
    return resultado;
}

template <class Element>
void ArbolN<Element>::recorrerInorden(std::list<Element> &resultado, NodoAN<Element> *nodoActual) const{
    if (nodoActual != NULL) {
        // Recorrer el primer hijo (subárbol más a la izquierda)
        if (nodoActual->getHijoIzq() != NULL) {
            recorrerInorden(resultado, nodoActual->getHijoIzq());
        }
        
        // Visitar la raíz
        resultado.push_back(nodoActual->getInfo());
        
        // Recorrer los hermanos del primer hijo (resto de hijos)
        if (nodoActual->getHijoIzq() != NULL) {
            NodoAN<Element> *hermano = nodoActual->getHijoIzq()->getHerDer();
            while (hermano != NULL) {
                recorrerInorden(resultado, hermano);
                hermano = hermano->getHerDer();
            }
        }
    }
}

template <class Element>
std::list<Element> ArbolN<Element>::recorrerPostorden() const{
    std::list<Element> resultado = std::list<Element>();
    recorrerPostorden(resultado, raiz);
    return resultado;
}

template <class Element>
void ArbolN<Element>::recorrerPostorden(std::list<Element> &resultado, NodoAN<Element> *nodoActual) const {
    if (nodoActual != NULL) {
        recorrerPostorden(resultado, nodoActual->getHijoIzq());
        resultado.push_back(nodoActual->getInfo());
        recorrerPostorden(resultado, nodoActual->getHerDer());
    }
}

template <class Element>
std::list<Element> ArbolN<Element>::recorrerNiveles() const {
    std::list<Element> resultado;
    std::queue<NodoAN<Element>* > hijos;
    hijos.push(this->raiz);
    while(!hijos.empty()) {
        NodoAN<Element> *nodoAct = hijos.front();
        while(nodoAct != NULL) 
        {
            if(nodoAct->getHijoIzq() != NULL) {
                hijos.push(nodoAct->getHijoIzq());
            }
            resultado.push_back(nodoAct->getInfo());
            nodoAct = nodoAct->getHerDer();
        }
        hijos.pop();
    }
    return resultado;
}

template <class Element>
void ArbolN<Element>::mostrarPreorden() const{
    std::cout << std::endl;std::cout << std::endl;
    mostrarPreorden(raiz);
    std::cout << std::endl;std::cout << std::endl;
}

template <class Element>
void ArbolN<Element>::mostrarPreorden(NodoAN<Element> *nodoActual) const{
    if (nodoActual != NULL) {
        std::cout << "[" << nodoActual->getInfo() << "]";
        if ( nodoActual->getHijoIzq() != NULL) {
            NodoAN<Element> *nodo = nodoActual->getHijoIzq();
            while (nodo != NULL) {
                std::cout << " -> " << nodo->getInfo();
                nodo = nodo->getHerDer();
            }
            std::cout << std::endl;
            mostrarPreorden(nodoActual->getHijoIzq());
        }
        else {
            std::cout << " -> * "<<std::endl;
        }
        mostrarPreorden(nodoActual->getHerDer());
    }
}

template <class Element>
std::list<Element> ArbolN<Element>::getHojas() const {
    std::list<Element> resultado;
    getHojas(resultado, this->raiz);
    return resultado;
}

template <class Element>
void ArbolN<Element>::getHojas(std::list<Element> &resultado, NodoAN<Element> *nodoActual) const{
    if (nodoActual != NULL) {
        if (nodoActual->getHijoIzq() == NULL) {
            resultado.push_back(nodoActual->getInfo());
        }
        else  {
            getHojas(resultado, nodoActual->getHijoIzq());
        }
        getHojas(resultado, nodoActual->getHerDer());
    }
}

template <class Element>
ArbolN<Element>::ArbolN() : raiz(NULL), profundidad(0)
{

}

template <class Element>
ArbolN<Element>::ArbolN(const Element &info, const std::list<ArbolN<Element> > &hijos) {
    this->raiz = new NodoAN<Element>(info);
    if (hijos.empty()) {
        this->profundidad = 1;
        return;
    }
    
    if (!hijos.empty()) {
        NodoAN<Element>* nodoActual = NULL;
        
        typename std::list<ArbolN<Element> >::const_iterator it = hijos.begin();
        
        raiz->setHijoIzq(copiarNodos((*it).raiz));
        nodoActual = raiz->getHijoIzq();
        it++;
        
        for (; it != hijos.end(); ++it) {
            nodoActual->setHerDer(copiarNodos((*it).raiz));
            nodoActual = nodoActual->getHerDer();
        }
    }
    this->profundidad = calcularProfundidad();
}

template <class Element>
ArbolN<Element>::ArbolN(const ArbolN<Element> &otro) {
    this->raiz = copiarNodos(otro.raiz);
    this->profundidad = otro.profundidad;
}

template <class Element>
ArbolN<Element>::~ArbolN<Element>(){
    vaciar();
}

template <class Element>
void ArbolN<Element>::vaciar() {
    vaciar(this->raiz);
    this->profundidad = 0;
    this->raiz = NULL;
}

template <class Element>
void ArbolN<Element>::vaciar(NodoAN<Element> *nodo) {
    if (nodo != NULL) {
        vaciar(nodo->getHijoIzq());
        vaciar(nodo->getHerDer());
        delete nodo;
    }
}


template <class Element>
void ArbolN<Element>::copiar(const ArbolN<Element> &otro) {
    vaciar();
    this->raiz = copiarNodos(otro.raiz);
    this->profundidad = otro.profundidad;
    
}


template <class Element>
ArbolN<Element> ArbolN<Element>::construirNodo(const Element& elem, const std::unordered_map<Element, std::list<Element> >& mapa) {
    typename std::unordered_map<Element, std::list<Element> >::const_iterator it = mapa.find(elem);
    std::list<ArbolN<Element> > hijosArbol;
    if (it != mapa.end()) {
        for (typename std::list<Element>::const_iterator itHijo = it->second.begin(); itHijo != it->second.end(); ++itHijo) {
            hijosArbol.push_back(construirNodo(*itHijo, mapa));
        }
    }
    return ArbolN<Element>(elem, hijosArbol);
}

template <class Element>
ArbolN<Element> ArbolN<Element>::construirDesdeMapa(const std::unordered_map<Element, std::list<Element> >& mapa) {
    if (mapa.empty()) {
        return ArbolN<Element>();
    }

    std::set<Element> hijos;
    for (typename std::unordered_map<Element, std::list<Element> >::const_iterator itMapa = mapa.begin(); itMapa != mapa.end(); ++itMapa) {
        for (typename std::list<Element>::const_iterator itHijo = itMapa->second.begin(); itHijo != itMapa->second.end(); ++itHijo) {
            hijos.insert(*itHijo);
        }
    }

    Element raiz;
    bool encontrada = false;
    for (typename std::unordered_map<Element, std::list<Element> >::const_iterator itMapa = mapa.begin(); itMapa != mapa.end(); ++itMapa) {
        if (hijos.find(itMapa->first) == hijos.end()) {
            if (encontrada) {
                throw std::invalid_argument("El mapa tiene múltiples raíces");
            }
            raiz = itMapa->first;
            encontrada = true;
        }
    }

    if (!encontrada) {
        throw std::invalid_argument("No se encontró la raíz en el mapa");
    }

    return construirNodo(raiz, mapa);
}

template <class Element>
bool ArbolN<Element>::esVacio() const{
    return this->profundidad == 0;
}

template <class Element>
Element& ArbolN<Element>::getRaiz() {
    if (raiz == NULL) {
        throw std::runtime_error("El árbol está vacío, no se puede obtener la raíz.");
    }
    return raiz->getInfo();
}

template <class Element>
std::list<ArbolN<Element> > ArbolN<Element>::getHijos() {
    if (raiz == NULL) {
        throw std::runtime_error("El árbol está vacío, no se puede obtener hijos.");
    }

    if (raiz->getHijoIzq() == NULL) {
        //std::cout << "prof: " << profundidad << std::endl; 
        return std::list<ArbolN<Element> >();
    }

    /* if (profundidad <= 1) {
        return std::list<ArbolN<Element> >();
    } */

    std::list<ArbolN<Element> > hijos;
    NodoAN<Element> *hijoAct = raiz->getHijoIzq();
    while (hijoAct != NULL) {
        ArbolN<Element> a;
        a.raiz = new NodoAN<Element>(hijoAct->getInfo());
        a.raiz->setHijoIzq(copiarNodos(hijoAct->getHijoIzq()));
        a.profundidad = a.calcularProfundidad();
        hijos.push_back(a);
        hijoAct = hijoAct->getHerDer();
    }
    return hijos;
}

template <class Element>
void ArbolN<Element>::insertarSubArbol(const ArbolN<Element> &subArbol) {
    if (this->raiz == NULL) {
        throw std::runtime_error("No se puede insertar subarbol en un arbol sin hijos");
    }
    
    NodoAN<Element> *nodo = copiarNodos(subArbol.raiz);
    
    NodoAN<Element> *ant = NULL;
    NodoAN<Element> *act = this->raiz->getHijoIzq();
    while (act != NULL) {
        ant = act;
        act = act->getHerDer();
    }
    if (ant == NULL) {
        this->raiz->setHijoIzq(nodo);
    }
    else {
        ant->setHerDer(nodo);
    }
    this->profundidad = max(subArbol.getProfundidad() + 1, this->profundidad);
}

// pos va de 0 a size-1
template <class Element>
void ArbolN<Element>::eliminarSubArbol(const int pos) {
    if (profundidad <= 1) {
        throw std::runtime_error("No se puede eliminar subarbol en un arbol sin hijos");
    }
    if (pos < 0) {
        throw std::runtime_error("No se puede eliminar subarbol al pasar una posicion negativa");
    }
    NodoAN<Element> *ant = NULL;
    NodoAN<Element> *act = this->raiz->getHijoIzq();
    int i = 0;
    while (act != NULL && i != pos) {
        ant = act;
        act = act->getHerDer();
        i++;
    }
    if (i == pos) 
    {
        if ( act == raiz->getHijoIzq()) {
            raiz->setHijoIzq(act->getHerDer());
            vaciar(act->getHijoIzq());
            delete act;
        }
        else {
            if (act == NULL) {
                throw std::runtime_error("El subarbol en la posicion especificada es nulo");
            }
            else {
                ant->setHerDer(act->getHerDer());
                vaciar(act->getHijoIzq());
                delete act;
            }
        }
        this->profundidad = calcularProfundidad();
    }
    else {
        throw std::runtime_error("Posicion inválida de eliminación de subarbol");
    }

}

template <class Element>
int ArbolN<Element>::getProfundidad() const{
    return this->profundidad;
}

template <class Element>
int ArbolN<Element>::calcularProfundidad() {
    return getProfundidad(raiz);
}

// consigue la profundidad recorriendo el arbol
template <class Element>
int ArbolN<Element>::getProfundidad(NodoAN<Element> * nodo) {
    if (nodo == NULL) {
        return 0;
    }

    int profHijo = getProfundidad(nodo->getHijoIzq());
    int profHermano = getProfundidad(nodo->getHerDer());

    return max(1 + profHijo, profHermano);
}


template <class Element>
ArbolN<Element>& ArbolN<Element>::operator=(const ArbolN<Element>& otro) {
    if (this != &otro) { // Evitar la auto-asignación
        copiar(otro);
    }
    return *this;
}

template <class Element>
int ArbolN<Element>::max(int a, int b) {
    return a > b ? a : b;
}

// calcular el msi
template <class Element>
int ArbolN<Element>::msi() {
    if (this->raiz == NULL) {
        return 0;
    }

    int raizI, raizE;

    msi(this->raiz, raizI, raizE);

    return max(raizI, raizE);
}

// funcion para calcular el msi
template <class Element>
void ArbolN<Element>::msi(NodoAN<Element> *nodo, int &incluido, int &excluido) {
    if (nodo == NULL) {
        incluido = 0;
        excluido = 0;
        return;
    }

    incluido = nodo->getInfo() + 0;
    excluido = 0;

    NodoAN<Element>* hijo = nodo->getHijoIzq();

    while (hijo != NULL) {
        int hijoInc, hijoExc;

        msi(hijo, hijoInc, hijoExc);

        incluido += hijoExc;

        excluido += max(hijoInc, hijoExc);

        hijo = hijo->getHerDer();
    }
}

// funcion para calcular el balance
template <class Element>
int ArbolN<Element>::balance() {
    if (this->raiz == NULL) {
        return 0;
    }

    int balance = 0;
    std::queue<std::pair<NodoAN<Element>*, int> > q;

    q.push(std::make_pair(this->raiz, 0));

    while (!q.empty()) {
        NodoAN<Element>* nodoAct = q.front().first;
        int profundidad = q.front().second;

        q.pop();
        
        NodoAN<Element>* hijo = nodoAct->getHijoIzq();

        if (hijo == NULL) {
            if (profundidad % 2 == 0) {
                balance++;
            } else {
                balance--;
            }
        }
        else {
            while (hijo != NULL) {
                q.push(std::make_pair(hijo, profundidad + 1));
                hijo = hijo->getHerDer();
            }
        }
    }

    return balance;
}
