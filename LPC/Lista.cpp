#include "Lista.h"
#include <iostream>
#include <cstddef>
#include <cassert>
#include <sstream>
#include <string>

template <typename T>
std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}


/// @brief Constructor por defecto de la clase Lista.
///        Inicializa una lista vacía.
/// @tparam Element Tipo de los elementos de la lista.
template <class Element>                                                                                                                     
Lista<Element>::Lista() : head(NULL), tail(NULL), size(0)
{
}

/// @brief Constructor de copia de la clase Lista.
///        Crea una nueva lista que es una copia profunda de 'otra' lista.
/// @tparam Element Tipo de los elementos de la lista.
/// @param otra La lista de la cual se va a copiar.
template <class Element>
Lista<Element>::Lista(const Lista &otra) : head(NULL), tail(NULL), size(0)
{
    if (otra.head != NULL) {
        Nodo<Element>* temp = otra.head;
        while (temp != NULL) {
            this->insertar(temp->getInfo(), size);
            temp = temp->getSig();
        }
    }
}

/// @brief Destructor de la clase Lista.
///        Libera toda la memoria asignada a los nodos de la lista.
/// @tparam Element Tipo de los elementos de la lista.
template <class Element>
Lista<Element>::~Lista() { 
    vaciar(); 
}


/// @brief Vacía la lista, eliminando todos sus elementos y liberando la memoria.
/// @tparam Element Tipo de los elementos de la lista.
template <class Element>
void Lista<Element>::vaciar() {
    while (size > 0) {
        eliminar(0);
    }
}


/// @brief Inserta un nuevo elemento en la lista en la posición especificada.
/// @tparam Element Tipo de los elementos de la lista.
/// @param info El elemento a insertar.
/// @param pos La posición (0-indexed) donde se insertará el elemento.
///            Si `pos` es 0, se inserta al inicio. Si `pos` es `getLongitud()`, se inserta al final.
/// @return Una referencia a la lista modificada, permitiendo el encadenamiento de llamadas.
/// @throw std::out_of_range Si la posición es negativa o mayor que el tamaño de la lista.
template <class Element>
Lista<Element>& Lista<Element>::insertar(const Element &info, int pos)
{
    if (pos < 0 || pos > size) {
        throw std::out_of_range("Posición inválida de insercion. Se intentó insertar en " + 
                              to_string(pos) + 
                              " en una lista de longitud " + 
                               to_string(size) +  ".");;
    }
    Nodo<Element> *nuevo = new Nodo<Element>(info);
    if (size == 0) {
        head = nuevo;
        tail = nuevo;
    }
    // Caso 2: Insertar al inicio
    else if (pos == 0) {
        nuevo->setSig(head);
        head->setAnt(nuevo);
        head = nuevo;
    }
    else if (pos == size)  // Si la posición es igual al tamaño de la lista, se inserta al final
    {
        tail->setSig(nuevo);
        nuevo->setAnt(tail);
        tail = nuevo;
    }
    else  // Insertar en el medio de la lista
    {
        Nodo<Element> *temp;
        if (pos <= size / 2){
            temp = head;
            for (int i = 0; i < pos - 1; i++) {
                temp = temp->getSig();
            }
            Nodo<Element>* siguiente = temp->getSig();
            nuevo->setSig(siguiente);
            nuevo->setAnt(temp);
            temp->setSig(nuevo);
            siguiente->setAnt(nuevo);
        }
        else {
            temp = tail;
            for (int i = size - 1; i > pos; i--) {
                temp = temp->getAnt();
            }

            nuevo->setAnt(temp->getAnt());
            nuevo->setSig(temp);
            temp->getAnt()->setSig(nuevo);
            temp->setAnt(nuevo);
        }
    }
    size++;
    return *this;
}

/// @brief Consulta el elemento en la posición especificada de la lista.
/// @tparam Element Tipo de los elementos de la lista.
/// @param pos La posición (0-indexed) del elemento a consultar.
/// @return El elemento en la posición `pos`.
/// @throw std::out_of_range Si la lista está vacía o la posición está fuera de rango.
template <class Element>
Element Lista<Element>::consultar(int pos) const
{
    if (pos < 0 || pos >= size) {
        throw std::out_of_range("Posición inválida de consulta. Se intentó consultar en " + 
                              to_string(pos) + 
                              " en una lista de longitud " + 
                               to_string(size) +  ".");;
    }

    if (pos == size-1) {
        return tail->getInfo();
    }

    if (pos <= size / 2){
        Nodo<Element> *temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->getSig();
        }
        return temp->getInfo();
    }
    else {
        Nodo<Element> *temp = tail;
        pos = size - 1 - pos;
        for (int i = 0; i < pos; i++) {
            temp = temp->getAnt();
        }
        return temp->getInfo();
        
    }

}

template <class Element>
Element& Lista<Element>::consultarRef(int pos)
{
    if (pos < 0 || pos >= size) {
        if (pos < 0 || pos >= size) {
        throw std::out_of_range("Posición inválida de consulta. Se intentó consultar en " + 
                              to_string(pos) + 
                              " en una lista de longitud " + 
                               to_string(size) +  ".");;
    }
    }

    if (pos == size-1) {
        return tail->getInfo();
    }

    if (pos <= size / 2){
        Nodo<Element> *temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->getSig();
        }
        return temp->getInfo();
    }
    else {
        Nodo<Element> *temp = tail;
        pos = size - 1 - pos;
        for (int i = 0; i < pos; i++) {
            temp = temp->getAnt();
        }
        return temp->getInfo();
        
    }
}

/// @brief Elimina el elemento en la posición especificada de la lista.
/// @tparam Element Tipo de los elementos de la lista.
/// @param pos La posición (0-indexed) del elemento a eliminar.
/// @return El elemento que ha sido eliminado de la lista.
/// @throw std::out_of_range Si la lista está vacía o la posición está fuera de rango.
template <class Element>
void Lista<Element>::eliminar(int pos)
{
    if (pos < 0 || pos >= size) {
        throw std::out_of_range("Posición inválida de eliminacion. Se intentó eliminar en " + 
                              to_string(pos) + 
                              " en una lista de longitud " + 
                               to_string(size) +  ".");
    }

    Nodo<Element>* aEliminar = head;

    // Caso 1: Eliminar el primer nodo
    if (pos == 0) {
        head = head->getSig();
        if (head != NULL) {
            head->setAnt(NULL);
        } else { // Si la lista se queda vacía
            tail = NULL;
        }
    }
    // Caso 2: Eliminar el último nodo
    else if (pos == size - 1) {
        aEliminar = tail;
        tail = tail->getAnt();
        if (tail != NULL) {
            tail->setSig(NULL);
        } else { // Si la lista se queda vacía
            head = NULL;
        }
    }
    // Caso 3: Eliminar un nodo en el medio
    else {
        // Encontrar el nodo a eliminar iterando desde el inicio
        for (int i = 0; i < pos; i++) {
            aEliminar = aEliminar->getSig();
        }
        Nodo<Element>* anterior = aEliminar->getAnt();
        Nodo<Element>* siguiente = aEliminar->getSig();

        anterior->setSig(siguiente);
        siguiente->setAnt(anterior);
    }
    
    delete aEliminar;
    size--;
}

/// @brief Verifica si la lista está vacía.
/// @tparam Element Tipo de los elementos de la lista.
/// @return `true` si la lista no contiene elementos, `false` en caso contrario.
template <class Element>
bool Lista<Element>::esVacia() const{
    return size == 0;
}

/// @brief Obtiene el número de elementos actualmente en la lista.
/// @tparam Element Tipo de los elementos de la lista.
/// @return La cantidad de elementos en la lista.
template <class Element>
int Lista<Element>::getLongitud() const{
    return size;
}

/// @brief Muestra los elementos de la lista en la salida estándar (cout).
/// @tparam Element Tipo de los elementos de la lista.
/// @note Utiliza el operador de inserción `<<` del `Element` para imprimir cada elemento.
template <class Element>
void Lista<Element>::mostrar() const{
    Nodo<Element> *temp = this->head;
    while (temp != NULL) {
        std::cout << temp->getInfo() << " ";
        temp = temp->getSig();
    }
    std::cout << std::endl;
}

/// @brief Copia el contenido de otra lista a la lista actual (copia profunda).
///        La lista actual se vacía antes de copiar los elementos de 'otra'.
/// @tparam Element Tipo de los elementos de la lista.
/// @param otro La lista de la cual se copiarán los elementos.
/// @return Una referencia a la lista modificada, permitiendo el encadenamiento de llamadas.
template <class Element>
Lista<Element>& Lista<Element>::copiar(const Lista &otra)
{
    if (otra.head != NULL) {
        Nodo<Element>* temp = otra.head;
        while (temp != NULL) {
            this->insertar(temp->getInfo(), size);
            temp = temp->getSig();
        }
    }
    return *this;
}

/// @brief Verifica si un elemento específico está presente en la lista.
/// @tparam Element Tipo de los elementos de la lista.
/// @param info El elemento a buscar. Se pasa como referencia constante para eficiencia.
/// @return `pos` si el elemento se encuentra en la lista, `-1` en caso contrario.
template <class Element>
int Lista<Element>::estaElemento(const Element& info) const{
    Nodo<Element> *iter = head;
    int pos = -1;
    while (iter != NULL) {
        pos++;
        if (iter->getInfo() == info) {
            return pos;
        }
        iter = iter->getSig();
    }
    return -1;
}

/// @brief Modifica las ocurrencias de un elemento `anterior` por un `nuevo` elemento.
/// @tparam Element Tipo de los elementos de la lista.
/// @param anterior El elemento cuyo valor se desea cambiar.
/// @param nuevo El nuevo valor que se asignará.
/// @param ocurrencias El número máximo de ocurrencias a modificar.
/// @return Una referencia a la lista modificada, permitiendo el encadenamiento de llamadas.
/// @note Si `ocurrencias` es mayor que el número de veces que aparece `anterior`,
///       se modificarán todas las ocurrencias.
template <class Element>
Lista<Element>& Lista<Element>::modificar(const Element& anterior, const Element& nuevo, int ocurrencias) {
    Nodo<Element> *iter = head;
    int x = 1;

    while (iter != NULL && x <= ocurrencias) {
        if (iter->getInfo() == anterior) {
            iter->setInfo(nuevo);
            x++;
        }
        iter = iter->getSig();
    }
    if (x == 1) {
        error("Se esperaba al menos una ocurrencia del elemento a modificar");
    }
    return *this;
}

/// @brief Modifica el elemento en una posición específica de la lista.
/// @tparam Element Tipo de los elementos de la lista.
/// @param nuevo El nuevo valor para el elemento.
/// @param pos La posición (0-indexed) del elemento a modificar.
/// @return Una referencia a la lista modificada, permitiendo el encadenamiento de llamadas.
/// @throw std::out_of_range Si la lista está vacía o la posición está fuera de rango.
template <class Element>
Lista<Element>& Lista<Element>::modificar(const Element& nuevo, int pos) {
    if (pos < 0 || pos >= size) {
        throw std::out_of_range("Posición inválida de modificación");
    }

    Nodo<Element> *iter = head;        
    for (int i = 0; i < pos; i++) {
        iter = iter->getSig();
    }
    iter->setInfo(nuevo);
    return *this;
}

/// @brief Invierte el orden de los elementos de la lista.
/// @tparam Element Tipo de los elementos de la lista.
/// @return Una referencia a la lista modificada (invertida), permitiendo el encadenamiento de llamadas.
/// @note Si la lista tiene 0 o 1 elemento, no se realiza ninguna operación.
template <class Element>
Lista<Element>& Lista<Element>::invertir()
{
    if (size <= 1) {
        return *this;
    }

    Nodo<Element>* prev = NULL;
    Nodo<Element>* act = head;
    Nodo<Element>* sig = NULL;
    tail = head;

    while (act != NULL) {
        sig = act->getSig();
        act->setSig(prev);
        act->setAnt(sig);
        prev = act;
        act = sig;
    }
    
    head = prev;
    return *this;
}

/// @brief Si se cumple con la condición, se intercambian los elementos
/// @tparam Element 
/// @param condicion 
/// @return la misma lista ordenada
/// @note Se usa el algoritmo de burbuja para ordenar la lista
template <class Element>
template <typename Condicion>
Lista<Element>& Lista<Element>::ordenar(const Condicion condicion) {
    if (size <= 1) {
        return *this;
    }

    bool ordena;
    do {
        ordena = false;
        Nodo<Element>* current = head;
        Nodo<Element>* next = NULL;

        while (current != NULL && current->getSig() != NULL) {
            next = current->getSig();

            // Verificar si los elementos están en el orden incorrecto
            if (condicion(current->getInfo(), next->getInfo())) {
                // Intercambiar los datos de los nodos
                Element temp = current->getInfo();
                current->setInfo(next->getInfo());
                next->setInfo(temp);
                ordena = true;
            }
            current = next;  // Avanzar al siguiente nodo
        }
    } while (ordena);
    
    return *this;
}

/// @brief Función estática de comparación para ordenar elementos en orden ascendente.
/// @tparam Element Tipo de los elementos a comparar.
/// @param a Primer elemento a comparar.
/// @param b Segundo elemento a comparar.
/// @return `true` si `a` es mayor que `b`, `false` en caso contrario. Para avisar que pueden invertirse.
/// @note Esta función asume que el tipo `Element` tiene sobrecargado el operador `>`.
template <class Element>
bool Lista<Element>::ordenAscendente(const Element& a, const Element& b) {
    return a > b;
}

/// @brief Función estática de comparación para ordenar elementos en orden descendente.
/// @tparam Element Tipo de los elementos a comparar.
/// @param a Primer elemento a comparar.
/// @param b Segundo elemento a comparar.
/// @return `true` si `a` es menor que `b`, `false` en caso contrario. Para avisar que pueden invertirse.
/// @note Esta función asume que el tipo `Element` tiene sobrecargado el operador `<`.
template <class Element>
bool Lista<Element>::ordenDescendente(const Element& a, const Element& b) {
    return a < b;
}

/// @brief Retorna una nueva lista que contiene una sub-secuencia de elementos de la lista original.
/// @tparam Element Tipo de los elementos de la lista.
/// @param inicio La posición (0-indexed) del primer elemento a incluir en la sublista.
/// @param fin La posición (0-indexed) hasta la cual se incluirán elementos (exclusiva).
///            Si `fin` es -1 (por defecto), la sublista se extenderá hasta el final de la lista original.
/// @return Una nueva `Lista` que es una copia de la porción especificada.
/// @throw std::out_of_range Si los índices `inicio` o `fin` son inválidos.
/// @note La lista original no se modifica. [2,1,3,4] -> sublista(1,3) -> [1,3,4]
template <class Element>
Lista<Element> Lista<Element>::sublista(int inicio, int fin) {
    if (fin == -1) {
        fin = size - 1;
    }

    if (inicio < 0 || fin >= size || inicio > fin) {
        throw std::out_of_range("Indices de sublista invalidos");
    }

    Lista<Element> sublista;
    Nodo<Element>* actual = head;
    int indice = 0;

    while (actual != NULL && indice <= fin) {
        if (indice >= inicio) {
            sublista.insertar(actual->getInfo(), sublista.getLongitud());
        }
        indice++;
        actual = actual->getSig();
    }
    return sublista;
}

/// @brief Concatena otra lista al final de la lista actual.
/// @tparam Element Tipo de los elementos de la lista.
/// @param otra La lista cuyos elementos se añadirán al final de la lista actual.
/// @return Una referencia a la lista modificada, permitiendo el encadenamiento de llamadas.
/// @note Los elementos de `otra` lista se copian al final de la lista actual. La lista `otra` no se modifica.
/// @note [1, 2, 3] + [4, 5] -> [1, 2, 3, 4, 5]
template <class Element>
Lista<Element>& Lista<Element>::concatenar(const Lista<Element>& otra) {
    if (otra.esVacia()) {
        return *this;
    }
    Nodo<Element>* iter = otra.head;
    
    while (iter != NULL) {
        insertar(iter->getInfo(), size);
        iter = iter->getSig();
    }
    return *this;
}

/// @brief Manejador de errores para la clase Lista, lanza una excepción `assert`.
/// @tparam Element Tipo de los elementos de la lista.
/// @param mensaje El mensaje de error específico a incluir en la excepción.
/// @note Es un método `const` ya que no modifica el estado del objeto. Sera que si le doy uso?
template <class Element>
void Lista<Element>::error(const std::string &mensaje) const {
    assert(false && mensaje.c_str());
}

/// @brief Posicion donde se encuentra el elemento más pequeño siguiendo la condicion
/// por defecto: cMin(a,b) => a < b
/// @tparam Element 
/// @param condicion 
/// @return 
template <class Element>
template <typename Condicion>
int Lista<Element>::min(const Condicion condicion)  // indice donde se encuentra el valor mas bajo de los elementos usando el criterio condicion
{
    if (esVacia()) {
        return -1;
    }
    
    Nodo<Element> *iter = head;
    Element minValor = head->getInfo();
    int minIndice = 0;
    int pos = 0;
    while (iter != NULL) {
        if (condicion(iter->getInfo(), minValor)) {
            minValor = iter->getInfo();
            minIndice = pos;
        }
        iter = iter->getSig();
        pos++;
    }
    return minIndice;
}

/// @brief Posicion donde se encuentra el elemento más grande siguiendo la condicion
/// por defecto: cMax(a,b) => a > b
/// @tparam Element 
/// @param condicion 
/// @return 
template <class Element>
template <typename Condicion>
int Lista<Element>::max(const Condicion condicion) // indice donde se encuentra el valor mas alto de los elementos usando el criterio condicion
{
    if (esVacia()) {
        return -1;
    }
    
    Nodo<Element> *iter = head;
    Element maxValor = head->getInfo();
    int maxIndice = 0;
    int pos = 0;
    while (iter != NULL) {
        if (condicion(iter->getInfo(), maxValor)) {
            maxValor = iter->getInfo();
            maxIndice = pos;
        }
        iter = iter->getSig();
        pos++;
    }
    return maxIndice;
}

template <class Element>
bool Lista<Element>::cMin(const Element& a, const Element& b) {
    return a < b;
}

template <class Element>
bool Lista<Element>::cMax(const Element& a, const Element& b) {
    return a > b;
}



/// O(n)
/// @brief Desplaza los elementos de la lista hacia la derecha.
/// @tparam Element Tipo de los elementos de la lista.
/// @param cantidad Número de posiciones a desplazar.
/// @return Una referencia a la lista modificada, permitiendo el encadenamiento de llamadas
/// [1,2,3,4,5] -> [5,1,2,3,4] (el ultimo pasa a ser el primero.)
template <class Element>
Lista<Element>& Lista<Element>::shiftDer(int cantidad) {
    if (cantidad < 0) {
        return shiftIzq(-cantidad);
    }
    if (size <= 1) {
        return *this;
    }

    cantidad %= size;
    if (cantidad == 0) {
        return *this;
    }

    // Encuentra el nodo que se convertira en el nuevo tail.
    // Esto es el nodo en la posicion `size - 1 - cantidad` de la lista original.
    Nodo<Element>* nuevoTail = tail;
    for (int i = 0; i < cantidad; i++) {
        nuevoTail = nuevoTail->getAnt();
    }
    
    // El nuevo head es el nodo siguiente al nuevo tail.
    Nodo<Element>* nuevoHead = nuevoTail->getSig();

    // Reconfigurar los enlaces de la lista.
    head->setAnt(tail);
    tail->setSig(head);
    
    nuevoHead->setAnt(NULL);
    nuevoTail->setSig(NULL);
    
    head = nuevoHead;
    tail = nuevoTail;

    return *this;
}

//O(n)
/// @brief Desplaza los elementos de la lista hacia la izquierda.
/// @tparam Element Tipo de los elementos de la lista.
/// @param cantidad Número de posiciones a desplazar.
/// @return Una referencia a la lista modificada, permitiendo el encadenamiento de llamadas
/// [1,2,3,4] [2,3,4,1] 1dplz (el primero pasa a ser el ultimo.)
template <class Element>
Lista<Element>& Lista<Element>::shiftIzq(int cantidad) {
    if (cantidad < 0) {
        return shiftDer(-cantidad);
    }
    if (size <= 1) {
        return *this;
    }
    cantidad %= size;
    if (cantidad == 0) {
        return *this;
    }

    // Encuentra el nodo que se convertira en el nuevo tail.
    // Este es el nodo en la posicion `cantidad - 1` de la lista original.
    Nodo<Element>* nuevoTail = head;
    for (int i = 0; i < cantidad - 1; i++) {
        nuevoTail = nuevoTail->getSig();
    }
    
    // El nuevo head es el nodo siguiente al nuevo tail.
    Nodo<Element>* nuevoHead = nuevoTail->getSig();

    // Reconfigurar los enlaces de la lista.
    head->setAnt(tail);
    tail->setSig(head);
    
    nuevoHead->setAnt(NULL);
    nuevoTail->setSig(NULL);
    
    head = nuevoHead;
    tail = nuevoTail;

    return *this;
}
// --- Implementación de Operadores ---

/// @brief Sobrecarga del operador de post-incremento.
/// @tparam Element Tipo de los elementos de la lista.
/// @param  
/// @return Una referencia a la lista actual.
/// @note Desplaza los elementos de la lista hacia la derecha conservando todos los elementos.
/// @note [1,2,3,4,5] -> [5,1,2,3,4] (el ultimo pasa a ser el primero.)
template <class Element>
Lista<Element>& Lista<Element>::operator++(int) {
    return shiftDer(1); // Desplazamiento a la derecha
}

/// @brief Sobrecarga del operador de post-decremento.
/// @tparam Element Tipo de los elementos de la lista.
/// @return Una referencia a la lista actual.
/// @note Desplaza los elementos de la lista hacia la izquierda conservando todos los elementos.
/// @note [1,2,3,4] [2,3,4,1] 1dplz (el primero pasa a ser el ultimo.)
template <class Element>
Lista<Element>& Lista<Element>::operator--(int) {
    return shiftIzq(1); // Desplazamiento a la izquierda
}

/// @brief Sobrecarga del operador de inserción de flujo para imprimir la lista.
/// @tparam E Tipo de los elementos de la lista (se usa 'E' para evitar conflicto con 'Element' de la clase).
/// @param os Referencia al objeto `ostream` (por ejemplo, `std::cout`).
/// @param lista Referencia constante a la lista que se va a imprimir.
/// @return Una referencia al objeto `ostream` modificado.
/// @note Imprime la lista en formato `[elemento1, elemento2, ..., elementoN]` o `[Vacia]`.
template <class Element> 
std::ostream& operator<<(std::ostream& os, const Lista<Element>& lista) {
     if (lista.esVacia()) {
        os << "[ (vacia) ]";
        return os;
    }

    Nodo<Element>* current = lista.head;
    os << "[ ";

    while (current != NULL) {
        os << current->getInfo();
        current = current->getSig();
        if (current != NULL) {
            os << ", ";
        }
    }
    
    os << " ]";
    return os;
}

/// @brief Sobrecarga del operador de acceso por índice (corchetes).
/// @tparam Element Tipo de los elementos de la lista.
/// @param indice El índice (0-indexed) del elemento a acceder.
/// @return El elemento en la posición especificada.
/// @note Este operador permite el acceso de lectura a los elementos de la lista,
///       como `miLista[0]`. Reutiliza el método `consultar()`.
/// @throw std::out_of_range Si el índice está fuera de rango.
template <class Element>
Element& Lista<Element>::operator [] (const int indice) {
    return consultarRef(indice);
}


/// @brief Sobrecarga del operador de igualdad. (supongo que explota cuando son diferentes tipos de listas)
/// @tparam Element Tipo de los elementos de la lista.
/// @param otra Referencia constante a la otra lista con la que se va a comparar.
/// @return `true` si ambas listas son iguales (mismo tamaño y mismos elementos en el mismo orden),
///         `false` en caso contrario.
template <class Element>
bool Lista<Element>::operator == (const Lista<Element>& otra) const {
    if (size != otra.size) {
        return false;
    }

    if ((this == &otra) || (head == NULL && otra.head == NULL)) {
        return true;
    }

    Nodo<Element>* iter1 = head;
    Nodo<Element>* iter2 = otra.head;

    while (iter1 != NULL && iter2 != NULL) {
        if (iter1->getInfo() != iter2->getInfo()) {
            return false;
        }
        iter1 = iter1->getSig();
        iter2 = iter2->getSig();
    }

    return true;
}

/// @brief Sobrecarga del operador de asignación.
/// @tparam Element Tipo de los elementos de la lista.
/// @param otra Referencia constante a la otra lista que se va a asignar.
/// @return Una referencia a la lista actual.
template <class Element>
Lista<Element>& Lista<Element>::operator = (const Lista<Element>& otra) {
    if (this == &otra) {
        return *this;
    }

    this->vaciar();
    
    Nodo<Element>* temp = otra.head;
    while (temp != NULL) {
        this->insertar(temp->getInfo(), this->size);
        temp = temp->getSig();
    }
    
    return *this;
}