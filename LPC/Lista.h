#pragma once
#include "Nodo.h"

template <class Element>
class Lista
{
private:
    Nodo<Element> *head;
    Nodo<Element> *tail;
    int size;

public:
    Lista();//
    Lista(const Lista &otra);//
    ~Lista();//
    void            vaciar();//
    Lista<Element>& insertar(const Element &info, int pos = 0);//
    Element         consultar(int pos)  const;//
    Element&        consultarRef(int pos);//
    void            eliminar(int pos);//
    bool            esVacia() const;//
    int             getLongitud() const;//
    void            mostrar() const;//
    Lista<Element>& copiar(const Lista<Element> &otro);//
    int            estaElemento(const Element& info) const;//
    Lista<Element>& modificar(const Element& anterior, const Element& nuevo, int ocurrencias);//
    Lista<Element>& modificar(const Element& nuevo, int pos);//
    Lista<Element>& invertir(); //
    template <typename Condicion> Lista<Element>&   ordenar(const Condicion condicion);//
    static bool     ordenAscendente(const Element& a, const Element& b);//
    static bool     ordenDescendente(const Element& a, const Element& b);//
    Lista<Element>  sublista(int inicio = 0, int fin = -1); //
    Lista<Element>& concatenar(const Lista<Element>& otra); //
    void            error(const std::string &mensaje) const; // Manejo de errores
    template <typename Condicion> int min(const Condicion condicion); // indice donde se encuentra el valor mas bajo de los elementos usando el criterio condicion
    template <typename Condicion> int max(const Condicion condicion); // indice donde se encuentra el valor mas alto de los elementos usando el criterio condicion
    static bool     cMin(const Element& a, const Element& b);
    static bool     cMax(const Element& a, const Element& b);
    Lista<Element>& shiftDer (int cantidad); // desplazamiento a la derecha
    Lista<Element>& shiftIzq (int cantidad); // desplazamiento a la izquierda
    // operadores
    template <typename E> friend std::ostream&      operator << (std::ostream& os, const Lista<E>& lista);//
    Element&                                        operator [] (int indice); // acceso a elementos por índice, devuelve una ref modificable
    bool                                            operator == (const Lista<Element>& otra) const; // igualdad en cuanto a contenido y orden
    Lista<Element>&                                 operator = (const Lista<Element>& otra);
    Lista<Element>&                                 operator ++  (int); // post incremento de la lista (desplazamiento a la derecha)
    Lista<Element>&                                 operator --  (int); // post decremento de la lista (desplazamiento a la izquierda)
};  

#include "Lista.cpp"