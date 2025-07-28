#include "Lista.h"
#include <iostream>
#include <cstddef>
#include <cassert>


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

/// @brief Destructor de la clase Lista.
///        Libera toda la memoria asignada a los nodos de la lista.
/// @tparam Element Tipo de los elementos de la lista.
template <class Element>
Lista<Element>::~Lista() { 
    destroy(); 
}

/// @brief Libera toda la memoria de los nodos de la lista y la reinicializa como vacía. hace exactamente lo mismo que el destructor y que vaciar() xd.
/// @tparam Element Tipo de los elementos de la lista.
template <class Element>
void Lista<Element>::destroy() {
    vaciar();
    head = NULL;
    tail = NULL;
    size = 0;
}

/// @brief Vacía la lista, eliminando todos sus elementos y liberando la memoria.
/// @tparam Element Tipo de los elementos de la lista.
/// @note Este método es un alias para `destroy()`.
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
Lista<Element>& Lista<Element>::insertar(Element info, int pos)
{
    if (pos < 0 || pos > size) {
        throw std::out_of_range("Posición inválida de inserción");
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
    if (pos < 0 || pos >= size || size == 0) {
        throw std::out_of_range("Posición inválida de consulta");
    }

    if (pos == size-1) {
        return tail->getInfo();
    }

    Nodo<Element> *temp = head;
    for (int i = 0; i < pos; i++) {
        temp = temp->getSig();
    }
    return temp->getInfo();
}

/// @brief Elimina el elemento en la posición especificada de la lista.
/// @tparam Element Tipo de los elementos de la lista.
/// @param pos La posición (0-indexed) del elemento a eliminar.
/// @return El elemento que ha sido eliminado de la lista.
/// @throw std::out_of_range Si la lista está vacía o la posición está fuera de rango.
template <class Element>
Element Lista<Element>::eliminar(int pos) 
{
    if (pos < 0 || pos >= size || size == 0) {
        throw std::out_of_range("Posición inválida de eliminación");
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
    if (this == &otra) {//assert
        return *this;
    }
    vaciar();

    Nodo<Element> *temp  = otra.head;
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
    }
    size = otra.size;
    return *this;
}

/// @brief Verifica si un elemento específico está presente en la lista.
/// @tparam Element Tipo de los elementos de la lista.
/// @param info El elemento a buscar. Se pasa como referencia constante para eficiencia.
/// @return `true` si el elemento se encuentra en la lista, `false` en caso contrario.
template <class Element>
bool Lista<Element>::estaElemento(const Element& info) const{
    Nodo<Element> *iter = head;
    while (iter != NULL) {
        if (iter->getInfo() == info) {
            return true;
        }
        iter = iter->getSig();
    }
    return false;
}

/// @brief Elimina un número específico de ocurrencias de un elemento dado de la lista.
/// @tparam Element Tipo de los elementos de la lista.
/// @param info El elemento a eliminar.
/// @param ocurrencias El número máximo de veces que se debe eliminar el elemento.
/// @return Una referencia a la lista modificada, permitiendo el encadenamiento de llamadas.
/// @note Si la cantidad de ocurrencias a eliminar es mayor que las existentes, se eliminarán todas.
template <class Element>
Lista<Element>& Lista<Element>::eliminar(const Element& info, int ocurrencias) {
    Nodo<Element>* act = head;
    Nodo<Element>* ant = NULL;

    while (act != NULL && ocurrencias > 0) {
        if (act->getInfo() == info) {
            Nodo<Element>* temp = act;
            if (act == head) {
                head = head->getSig();
                if (head == NULL) {
                    tail = NULL; // Si la lista queda vacía
                }
            } else {
                ant->setSig(act->getSig());
                if (act == tail) {
                    tail = ant; // Actualiza el tail si es necesario
                }
            }
            act = act->getSig(); // Avanza al siguiente nodo
            delete temp; // Libera memoria del nodo eliminado
            size--;
            ocurrencias--;
        } else {
            ant = act;
            act = act->getSig(); // Avanza al siguiente nodo
        }
    }
    return *this;
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

            if (condicion(current->getInfo(), next->getInfo())) { // Si no están en el orden deseado
                Element temp = current->getInfo();
                current->setInfo(next->getInfo());
                next->setInfo(temp);
                ordena = true;
            }
            current = current->getSig();
        }
        std::cout << "Ordenando: " << *this << std::endl; // Mostrar el estado de la lista en cada iteración
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
    if (size == 0) {
        head = new Nodo<Element>(iter->getInfo());
        tail = head;
        iter = iter->getSig();
    }
    
    while (iter != NULL) {
        Nodo<Element>* nuevo = new Nodo<Element>(iter->getInfo());
        tail->setSig(nuevo);
        tail = tail->getSig();
        iter = iter->getSig();
    }

    size += otra.size;
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

/// @brief Desplaza los elementos de la lista hacia la derecha.
/// @tparam Element Tipo de los elementos de la lista.
/// @param cantidad Número de posiciones a desplazar.
/// @return Una referencia a la lista modificada, permitiendo el encadenamiento de llamadas
template <class Element>
Lista<Element>& Lista<Element>::shiftDer (int cantidad) {
    if (cantidad < 0) {
        return *this -= -cantidad; // Desplazamiento a la izquierda
    }

    if (size <= 1) {
        throw std::out_of_range("No se puede desplazar una lista vacía");
    }

    cantidad = cantidad % size; // Evita desplazamientos innecesarios


    Nodo<Element>* ant = NULL;
    Nodo<Element>* act = head;
    while (cantidad > 0 && act != NULL) {
        ant = act;
        act = act->getSig();
        cantidad--;
    }

    if (ant == NULL) {
        return *this; // No hay elementos para desplazar
    }
    else
    {
        ant->setSig(NULL); // Corta la conexión anterior
        tail->setSig(head); // Conecta el final al inicio
        head = act; // Nuevo inicio
        tail = ant; // Actualiza el final
    }
    
    return *this;
}

/// @brief Desplaza los elementos de la lista hacia la izquierda.
/// @tparam Element Tipo de los elementos de la lista.
/// @param cantidad Número de posiciones a desplazar.
/// @return Una referencia a la lista modificada, permitiendo el encadenamiento de llamadas
template <class Element>
Lista<Element>& Lista<Element>::shiftIzq (int cantidad) {
    if (cantidad < 0) {
        return *this += -cantidad; // Desplazamiento a la derecha
    }

    if (size <= 1) {
        throw std::out_of_range("No se puede desplazar una lista vacía");
    }

    cantidad = cantidad % size; // Evita desplazamientos innecesarios
    cantidad = size - cantidad; // Desplazamiento a la izquierda
    Nodo<Element>* ant = NULL;
    Nodo<Element>* act = head;
    while (cantidad > 0 && act != NULL) {
        ant = act;
        act = act->getSig();
        cantidad--;
    }

    if (ant == NULL) {
        return *this; // No hay elementos para desplazar
    }
    else
    {
        ant->setSig(NULL); // Corta la conexión anterior
        tail->setSig(head); // Conecta el final al inicio
        head = act; // Nuevo inicio
        tail = ant; // Actualiza el final
    }

    return *this;
}

/// @brief Elimina todas las ocurrencias duplicadas de elementos en la lista,
///        dejando solo la primera ocurrencia de cada valor.
/// @tparam Element Tipo de los elementos de la lista.
/// @return Una referencia a la lista modificada, permitiendo el encadenamiento de llamadas.
/// @note Este método recorre la lista y elimina los nodos que contienen valores duplicados,
///       manteniendo solo la primera aparición de cada elemento.
template <class Element>
Lista<Element>& Lista<Element>::eliminarRepetidos () {
    if (size <= 1) {
        return *this;
    }

    Nodo<Element>* act = head;
    while (act != NULL) {
        Nodo<Element>* sig = act->getSig();
        Nodo<Element>* ant = act;

        while (sig != NULL) {
            if (sig->getInfo() == act->getInfo()) {
                ant->setSig(sig->getSig());
                delete sig;
                sig = ant->getSig();
                size--;
                if (sig == NULL)
                {
                    tail = ant;
                }
            } else {
                ant = sig;
                sig = sig->getSig();
            }
        }
        act = act->getSig();
    }
    return *this;
}

// --- Implementación de Operadores ---

/// @brief Sobrecarga del operador de concatenación para unir dos listas.
template <class Element>
Lista<Element> Lista<Element>::operator | (const Lista<Element>& otra) const {
    Lista<Element> resultado;
    resultado.copiar(*this);
    resultado.concatenar(otra);
    return resultado.eliminarRepetidos(); // Elimina duplicados
}

/// @brief Sobrecarga del operador de suma para agregar un elemento al final de la lista.
/// @tparam Element Tipo de los elementos de la lista.
/// @param otro Elemento a agregar.
/// @return Una nueva lista con el elemento agregado.
template <class Element>
Lista<Element> Lista<Element>::operator + (const Element& otro) const {
    Lista<Element> resultado;
    resultado.copiar(*this);
    resultado.insertar(otro, resultado.getLongitud());
    return resultado;
}

/// @brief Sobrecarga del operador de resta para eliminar un elemento de la lista todas las veces que aparece.
/// @tparam Element Tipo de los elementos de la lista.
/// @param otro Elemento a eliminar.
/// @return Una nueva lista con el elemento eliminado.
template <class Element>
Lista<Element> Lista<Element>::operator - (const Element& otro) const {
    Lista<Element> resultado;
    resultado.copiar(*this);
    resultado.eliminar(otro, size); // Elimina todas las ocurrencias de 'otro'
    return resultado;
}


/// @brief Sobrecarga del operador de post-incremento.
/// @tparam Element Tipo de los elementos de la lista.
/// @param  
/// @return Una referencia a la lista actual.
/// @note Desplaza los elementos de la lista hacia la derecha conservando todos los elementos.
/// @note [1,2,3]++ -> [2,3,1]
template <class Element>
Lista<Element>& Lista<Element>::operator++(int) {
    return shiftDer(1); // Desplazamiento a la derecha
}

/// @brief Sobrecarga del operador de post-decremento.
/// @tparam Element Tipo de los elementos de la lista.
/// @return Una referencia a la lista actual.
/// @note Desplaza los elementos de la lista hacia la izquierda conservando todos los elementos.
/// @note [1,2,3]-- -> [3,1,2]
template <class Element>
Lista<Element>& Lista<Element>::operator--(int) {
    return shiftIzq(1); // Desplazamiento a la izquierda
}

/// @brief Sobrecarga del operador de suma para agregar un elemento al final de la lista.
/// @note actua sobre la lista actual, no crea una nueva lista.
template <class Element>
Lista<Element>& Lista<Element>::operator += (const Element& otro) {
    return insertar(otro, size); // Inserta al final
}

/// @brief Sobrecarga del operador de resta para eliminar un elemento de la lista todas las veces que aparece.
/// @note actua sobre la lista actual, no crea una nueva lista.

template <class Element>
Lista<Element>& Lista<Element>::operator -= (const Element& otro) {
    eliminar(otro, size); // Elimina todas las ocurrencias de 'otro'
    return *this; // Retorna la lista modificada
}

/// @brief  Sobrecarga del operador de pre-incremento.
///         Desplaza los elementos de la lista hacia la derecha y elimina el primer elemento.
/// @tparam Element Tipo de los elementos de la lista.
/// @return Una referencia a la lista actual.
template <class Element>
Lista<Element>& Lista<Element>::operator ++ () {
    // Pre incremento: desplazar a la derecha y eliminar el primer elemento
    if (size == 0) {
        throw std::out_of_range("No se puede incrementar una lista vacía");
    } else {
        Nodo<Element>* temp = head;
        head = head->getSig();
        if (head == NULL) {
            tail = NULL; // Si la lista queda vacía
        }
        delete temp;
        size--;
    }
    return *this;
}

/// @brief  Sobrecarga del operador de pre-decremento.
///         Desplaza los elementos de la lista hacia la izquierda y elimina el último elemento.
/// @tparam Element Tipo de los elementos de la lista.
/// @return Una referencia a la lista actual.
template <class Element>
Lista<Element>& Lista<Element>::operator -- () {
    // Pre decremento: desplazar a la izquierda y eliminar el último elemento
    if (size == 0) {
        throw std::out_of_range("No se puede decrementar una lista vacía");
    } else {
        if (size == 1) {
            delete head; // Si solo hay un elemento, lo eliminamos
            head = NULL;
            tail = NULL;
        } else {
            Nodo<Element>* temp = head;
            while (temp->getSig() != tail) {
                temp = temp->getSig(); // Avanza hasta el penúltimo nodo
            }
            delete tail; // Elimina el último nodo
            tail = temp; // Actualiza el tail
            tail->setSig(NULL); // Corta la conexión al último nodo eliminado
        }
        size--;
    }
    return *this;
}

/// @brief Sobrecarga del operador de inserción de flujo para imprimir la lista.
/// @tparam E Tipo de los elementos de la lista (se usa 'E' para evitar conflicto con 'Element' de la clase).
/// @param os Referencia al objeto `ostream` (por ejemplo, `std::cout`).
/// @param lista Referencia constante a la lista que se va a imprimir.
/// @return Una referencia al objeto `ostream` modificado.
/// @note Imprime la lista en formato `[elemento1, elemento2, ..., elementoN]` o `[Vacia]`.
template <class Element> // Esta plantilla es para la función, no para la clase
std::ostream& operator << (std::ostream& os, const Lista<Element>& lista) {
    if (lista.size <= 0) { // Usa el método público esVacia() si está disponible
        os << "[ ]";
        return os;
    }

    Nodo<Element>* current = lista.head; 
    os << "[";
    while (current != nullptr) {
        os << current->getInfo(); // si se usan estructuras raras que no se pueden imprimir lloro
        if (current->getSig() != nullptr) {
            os << ", ";
        }
        current = current->getSig();
    }
    os << "]";
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
Element Lista<Element>::operator [] (const int indice) const {
    return consultar(indice);

    
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
    destroy(); // Limpia la lista actual
    copiar(otra); // Copia los elementos de otra lista
    return *this;
}

/// @brief Sobrecarga del operador de intersección de listas.
/// @tparam Element Tipo de los elementos de la lista.
/// @param otra Referencia constante a la otra lista con la que se va a intersectar.
/// @return Una nueva lista que contiene los elementos en común entre ambas listas.
template <class Element>
Lista<Element> Lista<Element>::operator & (const Lista<Element>& otra) const{
    Lista<Element> resultado;
    if (this == &otra) {
        resultado.copiar(*this); // retorna una copia porque sino la cago
        return resultado.eliminarRepetidos(); // Elimina duplicados
    }

    Lista<Element> otraAux(otra);
    otraAux.eliminarRepetidos();

    Lista<Element> aux(*this);
    aux.eliminarRepetidos();

    Nodo<Element>* iter1 = head;
    while (iter1 != NULL) {
        if (otraAux.estaElemento(iter1->getInfo())) {
            resultado.insertar(iter1->getInfo(), resultado.getLongitud());
        }
        iter1 = iter1->getSig();
    }

    return resultado;
}