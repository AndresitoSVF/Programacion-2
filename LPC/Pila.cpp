#include "Pila.h"
#include <cstddef>
#include <iostream>

/// @brief Constructor por defecto.
///        Inicializa una pila vacía.
template<class Element>
Pila<Element>::Pila() : head(NULL), size(0){}


/// @brief Método auxiliar recursivo para realizar la copia profunda de la pila.
///        Recorre la pila de origen de forma recursiva y apila los elementos
///        en la pila actual para mantener el orden LIFO.
/// @param nodo El nodo desde el cual se inicia la copia.
template<class Element>
void Pila<Element>::copiar(Nodo<Element>* nodo) {
    if (nodo == NULL) {
        return;
    }
    copiar(nodo->getSig()); 
    this->apilar(nodo->getInfo());
}

/// @brief Constructor de copia.
///        Crea una nueva pila que es una copia profunda de 'otra'.
///        Utiliza el método auxiliar 'copiar' para mantener el orden LIFO.
/// @param otra La pila de la cual se va a copiar.
template<class Element>
Pila<Element>::Pila(const Pila& otra) : head(NULL), size(0) {
    copiar(otra.head);
}

/// @brief Destructor de la pila.
///        Libera toda la memoria asignada a los nodos de la pila.
template<class Element>
Pila<Element>::~Pila() {
    vaciar();
}

/// @brief Vacía la pila, eliminando todos sus elementos y liberando la memoria.
template<class Element>
void Pila<Element>::vaciar() {
    while (size > 0) {
        desapilar();
    }

}

/// @brief Inserta un nuevo elemento en la parte superior de la pila.
/// @param info El elemento a apilar.
template<class Element>
void Pila<Element>::apilar(Element &info){
    Nodo<Element> *nuevo = new Nodo<Element>(info);
    if (size <= 0) {
        head = nuevo;
    }
    else 
    {
        nuevo->setSig(head);
        head = nuevo;
    }
    size++;
}

/// @brief Consulta el elemento en la parte superior de la pila sin eliminarlo.
/// @return El elemento en la parte superior de la pila.
/// @throw std::out_of_range Si la pila está vacía.
template<class Element>
Element& Pila<Element>::getTop() const{
    //if (size <= 0) { return Element(); std::cout << "no tiene h";}
    if (size <= 0) throw std::out_of_range("Error: getTop() llamado en Pila vacia.");
    return head->getInfo();
}


/// @brief Elimina y retorna el elemento en la parte superior de la pila.
/// @return El elemento que ha sido desapilado.
/// @throw std::out_of_range Si la pila está vacía.
template<class Element>
void Pila<Element>::desapilar(){
    //if (size <= 0) { return Element(); std::cout << "no puede desenPilar vacia";}
    if (size <= 0) throw std::out_of_range("Error: desapilar() llamado en Pila vacia.");
    Nodo<Element> *temp = head;
    Element info(temp->getInfo());
    head = head->getSig();
    delete temp;
    size--;
}

/// @brief Verifica si la pila está vacía.
/// @return `true` si la pila no contiene elementos, `false` en caso contrario.
template<class Element>
bool Pila<Element>::esVacia() const{
    return size == 0;
}

/// @brief Obtiene el número de elementos actualmente en la pila.
/// @return La cantidad de elementos en la pila.    
template<class Element>
int Pila<Element>::getLongitud() const{
    return size;
}

/// @brief Elimina todos los elementos de la pila.
    /// @note Es un alias de la función 'vaciar', pero también resetea los punteros y el tamaño.
template<class Element>
void Pila<Element>::destroy() {
    vaciar();
    head=NULL;
    size=0;
}

/// @brief Muestra los elementos de la pila en la salida estándar.
/// @note Utiliza el operador de inserción `<<` del `Element` para imprimir.
template <class Element>
void Pila<Element>::mostrar() const{
    Nodo<Element> *temp = head;
    while (temp != NULL) {
        std::cout << temp->getInfo() << " ";
        temp = temp->getSig();
    }
}

/// @brief Sobrecarga del operador de inserción de flujo para imprimir la pila.
/// @param os Referencia al objeto `ostream`.
/// @param pila Referencia constante a la pila que se va a imprimir.
/// @return Una referencia al objeto `ostream` modificado.
template <class Element>
std::ostream& operator << (std::ostream& os, const Pila<Element>& pila) {
    if (pila.size <= 0) { // Usa el método público esVacia() si está disponible
        os << "[ ]";
        return os;
    }

    Nodo<Element>* current = pila.head; 
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

/// @brief Sobrecarga del operador de asignación.
///        Asigna el contenido de 'otra' pila a la pila actual, manejando la auto-asignación.
/// @param otra La pila que se va a asignar.
/// @return Una referencia a la pila actual.
template <class Element>
void Pila<Element>::operator=(const Pila& otra) {
    if (this != &otra) {
        vaciar();
        copiar(otra.head);
    }
}