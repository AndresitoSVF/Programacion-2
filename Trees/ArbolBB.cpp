#include "ArbolBB.h"

template <class Element>
void ArbolBB<Element>::insertar(const Element& info) {
    if (this->raiz == NULL) {
        this->raiz = new NodoAB<Element>(info);
    } else {
        insertar(this->raiz, info);
    }
    this->profundidad = calcularProfundidad();
    //std::cout << this->profundidad << std::endl;
}

template <class Element>
void ArbolBB<Element>::insertar(NodoAB<Element>*& nodoActual, const Element& info) {
    if (nodoActual == NULL) {
        nodoActual = new NodoAB<Element>(info);
    } else if (info < nodoActual->getInfo()) {
        insertar(nodoActual->getHijoIzqRef(), info);
    } else if (info > nodoActual->getInfo()) {
        insertar(nodoActual->getHijoDerRef(), info);
    }
}

template <class Element>
bool ArbolBB<Element>::consultar(const Element& info) {
    return consultar(this->raiz, info);
}

template <class Element>
bool ArbolBB<Element>::consultar(NodoAB<Element>* nodoActual, const Element& info) {
    if (nodoActual == NULL) {
        return false;
    }
    if (info == nodoActual->getInfo()) {
        return true;
    }
    if (info < nodoActual->getInfo()) {
        return consultar(nodoActual->getHijoIzqRef(), info);
    } else {
        return consultar(nodoActual->getHijoDerRef(), info);
    }
}

template <class Element>
void ArbolBB<Element>::eliminar(const Element& info) {
    eliminar(this->raiz, info);
    this->profundidad = calcularProfundidad();
    //std::cout << this->profundidad << std::endl;

}

template <class Element>
void ArbolBB<Element>::eliminar(NodoAB<Element>*& nodoActual, const Element& info) {
    if (nodoActual == NULL) {
        return; // El elemento no se encuentra
    }

    if (info < nodoActual->getInfo()) {
        eliminar(nodoActual->getHijoIzqRef(), info);
    } else if (info > nodoActual->getInfo()) {
        eliminar(nodoActual->getHijoDerRef(), info);
    } else { // Se encontró el nodo a eliminar
        NodoAB<Element>* aEliminar = nodoActual;

        if (nodoActual->getHijoIzqRef() == NULL) {
            nodoActual = nodoActual->getHijoDerRef();
        } else if (nodoActual->getHijoDerRef() == NULL) {
            nodoActual = nodoActual->getHijoIzqRef();
        } else { // Caso 3: Dos hijos
            NodoAB<Element>* sucesor = buscarMin(nodoActual->getHijoDerRef());
            nodoActual->setInfo(sucesor->getInfo());
            eliminar(nodoActual->getHijoDerRef(), sucesor->getInfo());
            return;
        }
        delete aEliminar;
    }
}

template <class Element>
NodoAB<Element>* ArbolBB<Element>::buscarMin(NodoAB<Element>* nodoActual) {
    if (nodoActual == NULL || nodoActual->getHijoIzqRef() == NULL) {
        return nodoActual;
    }
    return buscarMin(nodoActual->getHijoIzqRef());
}

template <class Element>
int ArbolBB<Element>::setProfundidad(NodoAB<Element> *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return 1 + max(setProfundidad(nodo->getHijoIzq()), setProfundidad(nodo->getHijoIzq()));
}

template <class Element>
int ArbolBB<Element>::calcularProfundidad() {
    return setProfundidad(this->raiz);
}

template <class Element>
int ArbolBB<Element>::max(int a, int b) {
    return a > b ? a : b;
}
