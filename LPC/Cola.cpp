#include "Cola.h"
#include <cstddef>
#include <iostream>
/// @brief Constructor por defecto de la clase Cola.
///        Inicializa una cola vacía.
template<class Element>
Cola<Element>::Cola() : head(NULL), tail(NULL), size(0){}

/// @brief Constructor de copia de la clase Cola.
///        Crea una nueva cola que es una copia profunda de 'otra' cola.
/// @param otra La cola de la cual se va a copiar.
template<class Element>
Cola<Element>::Cola(const Cola& otra) : head(NULL), tail(NULL), size(0){
    Nodo<Element> *temp = otra.head;
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

/// @brief Destructor de la clase Cola.
/// Libera toda la memoria asignada a los nodos de la cola.
template<class Element>
Cola<Element>::~Cola() {
    vaciar();
}

/// @brief Vacía la cola, eliminando todos sus elementos y liberando la memoria.
template<class Element>
void Cola<Element>::vaciar() {
    while (size > 0) {
        desencolar();
    }

}

/// @brief Inserta un nuevo elemento al final de la cola (en la parte trasera).
/// @param info El elemento a encolar.
template<class Element>
void Cola<Element>::encolar(Element &info){
    Nodo<Element> *nuevo = new Nodo<Element>(info);
    if (size <= 0) {
        tail = nuevo;
        head = tail;
    }
    else {
        tail->setSig(nuevo);
        tail = nuevo;
    }

    size++;
}

/// @brief Consulta el elemento en el frente de la cola sin eliminarlo.
/// @return El elemento en el frente de la cola.
/// @throw std::out_of_range Si la cola está vacía.
template<class Element>
Element& Cola<Element>::getHead() const{
    //if (size <= 0) { return Element(); std::cout << "no tiene h";}
    if (size <= 0) throw std::out_of_range("Error: getHead() llamado en cola vacia.");
    return head->getInfo();
}

/// @brief Consulta el elemento en la parte trasera de la cola sin eliminarlo.
/// @return El elemento en la parte trasera de la cola.
/// @throw std::out_of_range Si la cola está vacía.
template<class Element>
Element& Cola<Element>::getTail() const{
    //if (size <= 0) { return Element(); std::cout << "no tiene c";}
    if (size <= 0) throw std::out_of_range("Error: getTail() llamado en cola vacia.");
    return tail->getInfo();
}

/// @brief Elimina el elemento del frente de la cola.
/// @return El elemento que ha sido desencolado.
/// @throw std::out_of_range Si la cola está vacía.
template<class Element>
void Cola<Element>::desencolar(){
    //if (size <= 0) { return Element(); std::cout << "no puede desencolar vacia";}
    if (size <= 0) throw std::out_of_range("Error: desencolar() llamado en cola vacia.");
    Nodo<Element> *temp = head;
    Element info;
    head = head->getSig();
    info = temp->getInfo();
    delete temp;
    if (size == 1) {
        tail = NULL;
    }
    size--;
    return info;
}

/// @brief Verifica si la cola está vacía.
/// @return `true` si la cola no contiene elementos, `false` en caso contrario.
template<class Element>
bool Cola<Element>::esVacia() const{
    return size == 0;
}

/// @brief Obtiene el número de elementos actualmente en la cola.
/// @return La cantidad de elementos en la cola.
template<class Element>
int Cola<Element>::getLongitud() const{
    return size;
}

/// @brief Muestra los elementos de la cola en la salida estándar (cout).
/// @note Utiliza el operador de inserción `<<` del `Element` para imprimir cada elemento.
template <class Element>
void Cola<Element>::mostrar() const{
    Nodo<Element> *temp = head;
    while (temp != NULL) {
        std::cout << temp->getInfo() << " ";
        temp = temp->getSig();
    }
}

/// @brief Sobrecarga del operador de inserción de flujo para imprimir la cola.
/// @param os Referencia al objeto `ostream` (por ejemplo, `std::cout`).
/// @param cola Referencia constante a la cola que se va a imprimir.
/// @return Una referencia al objeto `ostream` modificado.
/// @note Imprime la cola en formato `[elemento1, elemento2, ..., elementoN]` o `[ ]`.
template <class Element>
std::ostream& operator << (std::ostream& os, const Cola<Element>& cola) {
    if (cola.size <= 0) { // Usa el método público esVacia() si está disponible
        os << "[ ]";
        return os;
    }

    Nodo<Element>* current = cola.head; 
    os << "[";
    while (current != NULL) {
        os << current->getInfo(); // si se usan estructuras raras que no se pueden imprimir lloro
        if (current->getSig() != NULL) {
            os << ", ";
        }
        current = current->getSig();
    }
    os << "]";
    return os;
}