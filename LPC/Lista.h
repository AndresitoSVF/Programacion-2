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
    void            destroy();//
    void            vaciar();//
    Lista<Element>& insertar(Element info, int pos = 0);//
    Element         consultar(int pos)  const;//
    Element         eliminar(int pos);//
    bool            esVacia() const;//
    int             getLongitud() const;//
    void            mostrar() const;//
    Lista<Element>& copiar(const Lista<Element> &otro);//
    bool            estaElemento(const Element& info) const;//
    Lista<Element>& eliminar(const Element& info, int ocurrencias);
    Lista<Element>& modificar(const Element& anterior, const Element& nuevo, int ocurrencias);//
    Lista<Element>& modificar(const Element& nuevo, int pos);//
    Lista<Element>& invertir(); //
    template <typename Condicion> Lista<Element>&   ordenar(const Condicion condicion);//
    static bool     ordenAscendente(const Element& a, const Element& b);//
    static bool     ordenDescendente(const Element& a, const Element& b);//
    Lista<Element>  sublista(int inicio = 0, int fin = -1); //
    Lista<Element>& concatenar(const Lista<Element>& otra); //
    void            error(const std::string &mensaje) const; // Manejo de errores
    Lista<Element>& eliminarRepetidos (); // Elimina los elementos repetidos de la lista
    Lista<Element>& shiftDer (int cantidad); // desplazamiento a la derecha
    Lista<Element>& shiftIzq (int cantidad); // desplazamiento a la izquierda
    // operadores
    template <typename E> friend std::ostream&      operator << (std::ostream& os, const Lista<E>& lista);//
    Element                                         operator [] (const int indice) const; // acceso a elementos por índice
    Lista<Element>&                                 operator += (const Element& otro); // concatenar elemento al final
    Lista<Element>                                  operator +  (const Element& otro) const; // concatenar elemento al final (actua sobre una copia)
    Lista<Element>&                                 operator -= (const Element& otro); // eliminar todas las ocurrencias de un elemento
    Lista<Element>                                  operator -  (const Element& otro) const; // eliminar todas las ocurrencias de un elemento (actua sobre una copia) **
    bool                                            operator == (const Lista<Element>& otra) const; // igualdad en cuanto a contenido y orden
    Lista<Element>&                                 operator =  (const Lista<Element>& otra);// copiar otra lista a esta
    Lista<Element>                                  operator &  (const Lista<Element>& otra) const; // interseccion de conjuntos retorna y actua sobre una copia (elimina los repetidos)
    Lista<Element>                                  operator |  (const Lista<Element>& otra) const; // union / concatenacion de conjuntos retorna y actua sobre una copia (elimina los repetidos)
    Lista<Element>&                                 operator ++  (int); // post incremento de la lista (desplazamiento a la derecha)
    Lista<Element>&                                 operator --  (int); // post decremento de la lista (desplazamiento a la izquierda)
    Lista<Element>&                                 operator ++  (); // pre incremento de la lista (desplazamiento a la derecha con eliminacion del primer elemento)
    Lista<Element>&                                 operator --  (); // pre decremento de la lista (desplazamiento a la izquierda con eliminacion del ultimo elemento)
};  

#include "Lista.cpp"