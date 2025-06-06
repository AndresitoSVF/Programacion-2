#include "Lista.h"
#include <iostream>
#include <cstddef>
// Constructor por defecto
// Crea una lista vacía
template <class Element>
Lista<Element>::Lista() : head(NULL), tail(NULL), size(0){}

// Constructor de copia
// Crea una nueva lista con los mismos elementos que otra lista
template <class Element>
Lista<Element>::Lista(Lista *otra) : head(NULL), tail(NULL), size(0)
{
    Nodo<Element> *temp = otra->head;
    while (temp != NULL) {
        Nodo<Element> *nuevo = new Nodo<Element>(temp->getInfo());
        if (head == NULL) {
            head = nuevo;
            tail = nuevo;
        } else {
            tail->setSig(nuevo);
            tail = nuevo;
        }
        temp = temp->getSig();
        size++;
    }
}

template <class Element>
void Lista<Element>::destroy() {
    vaciar();
    head = NULL;
    tail = NULL;
    size = 0;
}

// Vacía la lista
// Elimina todos los nodos de la lista y libera la memoria
template <class Element>
void Lista<Element>::vaciar() {
    while (!esVacia()) {
        eliminar(0);
    }
}

template <class Element>
void Lista<Element>::insertar(Element info, int pos) 
{
    if (pos == -1)  // Si no se especifica la posición, se inserta al final
    {
        pos = size;
    }
    
    if (pos < 0 || pos > size) {
        std::cout << "Posición inválida de inserción" << std::endl;
        return;
    }
    Nodo<Element> *nuevo = new Nodo<Element>(info);
    if (pos == 0) {
        nuevo->setSig(head);
        head = nuevo;
        if (size == 0) {
            tail = nuevo;
        }
    } 
    else if (pos == size)  // Si la posición es igual al tamaño de la lista, se inserta al final
    {
        tail->setSig(nuevo);
        tail = nuevo;
    }
    else  // Insertar en el medio de la lista
    {
        Nodo<Element> *temp = head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->getSig();
        }
        nuevo->setSig(temp->getSig());
        temp->setSig(nuevo);
    }
    size++;
}

template <class Element>
Element Lista<Element>::consultar(int pos) 
{
    if (pos < 0 || pos >= size) {
        std::cout << "Posición inválida de consulta" << std::endl;
        return Element(); // Devuelve un valor por defecto
    }
    Nodo<Element> *temp = head;
    for (int i = 0; i < pos; i++) {
        temp = temp->getSig();
    }
    return temp->getInfo();
}

template <class Element>
Element Lista<Element>::eliminar(int pos) {
    if (pos < 0 || pos >= size) {
        std::cout << "Posición inválida de eliminación" << std::endl;
        return Element(); // Devuelve un valor por defecto
    }
    Nodo<Element> *temp = head;
    Element info;
    if (pos == 0) {
        head = head->getSig();
        info = temp->getInfo();
        delete temp;
        if (size == 1) {
            tail = NULL;
        }
    } 
    else {
        Nodo<Element> *prev = NULL;
        for (int i = 0; i < pos; i++) {
            prev = temp;
            temp = temp->getSig();
        }
        prev->setSig(temp->getSig());
        info = temp->getInfo();
        delete temp;
        if (pos == size - 1) {
            tail = prev;
        }
    }
    size--;
    return info;
}

template <class Element>
bool Lista<Element>::esVacia() {
    return size == 0;
}

template <class Element>
int Lista<Element>::getLongitud() {
    return size;
}

// mostrar la lista
template <class Element>
void Lista<Element>::mostrar() {
    Nodo<Element> *temp = this->head;
    while (temp != NULL) {
        std::cout << temp->getInfo() << " ";
        temp = temp->getSig();
    }
    std::cout << std::endl;
}