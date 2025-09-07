#pragma once
#include "NodoAB.h"
#include <list>
#include <cstddef>
#include <unordered_map>

template <class Element>
class ArbolBin {
    
protected:
    NodoAB<Element>* raiz;
    int profundidad; // profundidad del arbol

    NodoAB<Element>* copiarNodos(NodoAB<Element> *raiz);
    void recorrerPreorden(std::list<Element> &resultado, NodoAB<Element> *nodoActual);
    void recorrerInorden(std::list<Element> &resultado, NodoAB<Element> *nodoActual);
    void recorrerPostorden(std::list<Element> &resultado, NodoAB<Element> *nodoActual);
    void vaciar(NodoAB<Element>* nodo);
    NodoAB<Element>* crearPreorden(std::unordered_map<Element, int> &inordenMap,
                                    std::list<Element> &listaPreorden, 
                                    typename std::list<Element>::iterator &iteradorPreorden,
                                    int &profundidad,
                                    int inicio,
                                    int fin);
    NodoAB<Element>* crearPostorden(std::unordered_map<Element, int> &inordenMap,
                                    std::list<Element> &listaPostorden, 
                                    typename std::list<Element>::reverse_iterator &iteradorPostorden,
                                    int &profundidad,
                                    int inicio,
                                    int fin);
    
public:
    ArbolBin(); // 1
    ArbolBin(const Element &info, const ArbolBin<Element> &A1, const ArbolBin<Element> &A2); // n
    ArbolBin(const ArbolBin<Element> &otro); // n
    ~ArbolBin(); // n
    Element& getRaiz(); // 1
    ArbolBin<Element> getHijoIzq(); // n
    ArbolBin<Element> getHijoDer(); // n
    int getProfundidad(); // 1
    bool esVacio(); // 1
    void vaciar(); // n
    std::list<Element> recorrerPreorden(); // n
    std::list<Element> recorrerInorden(); // n
    std::list<Element> recorrerPostorden(); // n
    void postorden(std::list<Element> &listaInorden, std::list<Element> &listaPostorden); // n
    void preorden(std::list<Element> &listaInorden, std::list<Element> &listaPostorden); // n
    ArbolBin<Element>& operator=(const ArbolBin<Element>& otro);
    
};
#include "ArbolBin.cpp"

// makefile para que no se me pierda
/* TARGET = RUN
CC = g++
INC_PATHS = -I. -I./LPC
CFLAGS = $(INC_PATHS) -march=native -O3 -Wall -Wextra -std=c++98 -I../LPC
LDFLAGS = -lm
MAIN = main
HEADERS = Lista.h Pila.h Nodo.h Cola.h

.PHONY: all clean run cleanall

all: $(TARGET)
    
run: $(TARGET)
	./$(TARGET) < entrada.txt > salida.txt

$(TARGET): $(MAIN).o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(MAIN).o: $(MAIN).cpp
	$(CC) $(CFLAGS) -c $(MAIN).cpp -o $@

clean:
	rm -f *.o

cleanall: clean
	rm -f $(TARGET) */