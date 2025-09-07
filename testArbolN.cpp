#include <iostream>
#include <cassert>
#include <ctime>
#include <vector>
#include "ArbolN.h"

template <class Element>
void mostrarLista(std::list<Element> &l) {
    if (l.empty()) {
        std::cout << "[ ]";
        return;
    }
	std::cout << "[ ";
	for (typename std::list<Element>::iterator it = l.begin(); it != l.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "]"; 
}
using namespace std;

// Función para medir el tiempo de ejecución
double medirTiempo(clock_t inicio, clock_t fin) {
    return double(fin - inicio) / CLOCKS_PER_SEC;
}

// Función para verificar si dos listas son iguales
template <typename T>
bool listasIguales(const list<T>& l1, const list<T>& l2) {
    if (l1.size() != l2.size()) return false;
    
    typename list<T>::const_iterator it1 = l1.begin();
    typename list<T>::const_iterator it2 = l2.begin();
    
    while (it1 != l1.end() && it2 != l2.end()) {
        if (*it1 != *it2) return false;
        ++it1;
        ++it2;
    }
    
    return true;
}

// Función para imprimir una lista (para debugging)
template <typename T>
void imprimirLista(const list<T>& lista) {
    typename list<T>::const_iterator it;
    for (it = lista.begin(); it != lista.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

// Pruebas unitarias
void testArbolVacio() {
    cout << "Test: Árbol vacío" << endl;
    ArbolN<int> arbol;
    
    assert(arbol.esVacio());
    assert(arbol.getProfundidad() == 0);
    
    list<int> preorden = arbol.recorrerPreorden();
    assert(preorden.empty());
    
    list<int> hojas = arbol.getHojas();
    assert(hojas.empty());
    
    try {
        arbol.getRaiz();
        assert(false); // No debería llegar aquí
    } catch (const runtime_error& e) {
        // Comportamiento esperado
    }
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolUnNodo() {
    cout << "Test: Árbol con un solo nodo" << endl;
    ArbolN<int> arbol(42, list<ArbolN<int> >());
    
    assert(!arbol.esVacio());
    assert(arbol.getProfundidad() == 1);
    assert(arbol.getRaiz() == 42);
    
    list<int> preorden = arbol.recorrerPreorden();
    list<int> esperado;
    esperado.push_back(42);
    assert(listasIguales(preorden, esperado));
    
    list<int> hojas = arbol.getHojas();
    assert(listasIguales(hojas, esperado));
    
    list<ArbolN<int> > hijos = arbol.getHijos();
    assert(hijos.empty());
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolSimple() {
    cout << "Test: Árbol simple con varios nodos" << endl;
    
    // Crear árbol: 1 con hijos 2, 3, 4
    ArbolN<int> hijo2(2, list<ArbolN<int> >());
    ArbolN<int> hijo3(3, list<ArbolN<int> >());
    ArbolN<int> hijo4(4, list<ArbolN<int> >());
    
    
    list<ArbolN<int> > hijos;
    hijos.push_back(hijo2);
    hijos.push_back(hijo3);
    hijos.push_back(hijo4);
    
    ArbolN<int> arbol(1, hijos);
    
    
    
    // Verificaciones
    assert(!arbol.esVacio());
    assert(arbol.getRaiz() == 1);
    assert(arbol.getProfundidad() == 2);
    
    // Verificar recorrido preorden
    list<int> preorden = arbol.recorrerPreorden();
    list<int> preordenEsperado;
    preordenEsperado.push_back(1);
    preordenEsperado.push_back(2);
    preordenEsperado.push_back(3);
    preordenEsperado.push_back(4);
    assert(listasIguales(preorden, preordenEsperado));
    
    // Verificar hojas
    list<int> hojas = arbol.getHojas();
    list<int> hojasEsperadas;
    hojasEsperadas.push_back(2);
    hojasEsperadas.push_back(3);
    hojasEsperadas.push_back(4);
    assert(listasIguales(hojas, hojasEsperadas));
    
    // Verificar hijos
    cout << "b" << endl; 
    list<ArbolN<int> > hijosObtenidos = arbol.getHijos();
    cout << "c" << endl; 
    
    assert(hijosObtenidos.size() == 3);
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolComplejo() {
    cout << "Test: Árbol complejo con múltiples niveles" << endl;
    
    // Crear árbol:
    //       1
    //     / | \*
    //    2  3  4 
    //   / \     \*  
    //  5   6     7
    
    ArbolN<int> nodo5(5, list<ArbolN<int> >());
    ArbolN<int> nodo6(6, list<ArbolN<int> >());
    
    list<ArbolN<int> > hijos2;
    hijos2.push_back(nodo5);
    hijos2.push_back(nodo6);
    ArbolN<int> nodo2(2, hijos2);
    
    ArbolN<int> nodo3(3, list<ArbolN<int> >());
    
    ArbolN<int> nodo7(7, list<ArbolN<int> >());
    list<ArbolN<int> > hijos4;
    hijos4.push_back(nodo7);
    ArbolN<int> nodo4(4, hijos4); 
     
    list<ArbolN<int> > hijos1;
    hijos1.push_back(nodo2); 
    hijos1.push_back(nodo3);
    hijos1.push_back(nodo4);
    
    ArbolN<int> arbol(1, hijos1); 
    
    // Verificaciones
    assert(arbol.getProfundidad() == 3);
    
    // Verificar recorridos
    list<int> preorden = arbol.recorrerPreorden();
    list<int> preordenEsperado;
    preordenEsperado.push_back(1);
    preordenEsperado.push_back(2);
    preordenEsperado.push_back(5);
    preordenEsperado.push_back(6);
    preordenEsperado.push_back(3);
    preordenEsperado.push_back(4);
    preordenEsperado.push_back(7);
    //mostrarLista(preorden);
    //mostrarLista(preordenEsperado);
    assert(listasIguales(preorden, preordenEsperado));
    
    list<int> inorden = arbol.recorrerInorden();
    list<int> inordenEsperado;
    inordenEsperado.push_back(5);
    inordenEsperado.push_back(2);
    inordenEsperado.push_back(6);
    inordenEsperado.push_back(1);
    inordenEsperado.push_back(3);
    inordenEsperado.push_back(7);
    inordenEsperado.push_back(4);
    //mostrarLista(inorden);
    //mostrarLista(inordenEsperado);
    assert(listasIguales(inorden, inordenEsperado));
    
    list<int> postorden = arbol.recorrerPostorden();
    //mostrarLista(postorden);
    
    list<int> postordenEsperado;
    postordenEsperado.push_back(5);
    postordenEsperado.push_back(6);
    postordenEsperado.push_back(2);
    postordenEsperado.push_back(3);
    postordenEsperado.push_back(7);
    postordenEsperado.push_back(4);
    postordenEsperado.push_back(1);
    assert(listasIguales(postorden, postordenEsperado));
    
    list<int> niveles = arbol.recorrerNiveles();
    list<int> nivelesEsperado;
    nivelesEsperado.push_back(1);
    nivelesEsperado.push_back(2);
    nivelesEsperado.push_back(3);
    nivelesEsperado.push_back(4);
    nivelesEsperado.push_back(5);
    nivelesEsperado.push_back(6);
    nivelesEsperado.push_back(7);
    assert(listasIguales(niveles, nivelesEsperado));
    
    // Verificar hojas
    list<int> hojas = arbol.getHojas();
    list<int> hojasEsperadas;
    hojasEsperadas.push_back(5);
    hojasEsperadas.push_back(6);
    hojasEsperadas.push_back(3);
    hojasEsperadas.push_back(7);
    assert(listasIguales(hojas, hojasEsperadas));
    
    cout << "  ✓ PASSED" << endl;
}

void testCopiaYAsignacion() {
    cout << "Test: Copia y asignación de árboles" << endl;
    
    // Crear árbol original
    ArbolN<int> hijo2(2, list<ArbolN<int> >());
    ArbolN<int> hijo3(3, list<ArbolN<int> >());
    
    list<ArbolN<int> > hijos;
    hijos.push_back(hijo2);
    hijos.push_back(hijo3);
    ArbolN<int> original(1, hijos);
    
    // Probar constructor de copia
    ArbolN<int> copia(original);
    assert(!copia.esVacio());
    assert(copia.getRaiz() == 1);
    assert(copia.getProfundidad() == 2);
    
    // Modificar original y verificar que copia no cambia
    ArbolN<int> nuevoHijo(4, list<ArbolN<int> >());
    original.insertarSubArbol(nuevoHijo);
    assert(original.getProfundidad() == 2); // Sigue siendo 2 porque los nuevos hijos están al mismo nivel
    assert(copia.getProfundidad() == 2);
    
    list<int> hijosOriginal = original.recorrerPreorden();
    assert(hijosOriginal.size() == 4); // 1, 2, 3, 4
    
    list<int> hijosCopia = copia.recorrerPreorden();
    assert(hijosCopia.size() == 3); // 1, 2, 3
    
    // Probar operador de asignación
    ArbolN<int> asignado;
    asignado = original;
    assert(!asignado.esVacio());
    assert(asignado.getRaiz() == 1);
    assert(asignado.getProfundidad() == 2);
    
    list<int> hijosAsignado = asignado.recorrerPreorden();
    assert(listasIguales(hijosAsignado, hijosOriginal));
    
    cout << "  ✓ PASSED" << endl;
}

void testInsercionYEliminacion() {
    cout << "Test: Inserción y eliminación de subárboles" << endl;
    
    ArbolN<int> arbol(1, list<ArbolN<int> >());
    
    // Insertar varios subárboles
    ArbolN<int> sub1(2, list<ArbolN<int> >());
    ArbolN<int> sub2(3, list<ArbolN<int> >());
    ArbolN<int> sub3(4, list<ArbolN<int> >());
    
    arbol.insertarSubArbol(sub1);
    arbol.insertarSubArbol(sub2);
    arbol.insertarSubArbol(sub3);
    
    assert(arbol.getProfundidad() == 2);
    
    list<int> preorden = arbol.recorrerPreorden();
    list<int> esperado;
    esperado.push_back(1);
    esperado.push_back(2);
    esperado.push_back(3);
    esperado.push_back(4);
    assert(listasIguales(preorden, esperado));
    
    // Eliminar el subárbol en posición 1 (valor 3) 
    
    arbol.eliminarSubArbol(1);
    
    list<int> postEliminacion = arbol.recorrerPreorden();
    list<int> esperadoPost;
    esperadoPost.push_back(1);
    esperadoPost.push_back(2);
    esperadoPost.push_back(4);
    assert(listasIguales(postEliminacion, esperadoPost));
    
    // Probar eliminación con posición inválida
    try {
        arbol.eliminarSubArbol(5);
        assert(false); // No debería llegar aquí
    } catch (const runtime_error& e) {
        // Comportamiento esperado
    }
    
    try {
        arbol.eliminarSubArbol(-1);
        assert(false); // No debería llegar aquí
    } catch (const runtime_error& e) {
        // Comportamiento esperado
    }
    
    cout << "  ✓ PASSED" << endl;
}

void testRendimiento() {
    cout << "Test: Rendimiento con árbol grande" << endl;
    const int m = 100000;
    clock_t inicio, fin;
    
    // Crear un árbol grande
    inicio = clock();
    
    ArbolN<int> arbol(0, list<ArbolN<int> >());
    
    // Insertar 1000 subárboles de un nivel
    for (int i = 1; i <= m; i++) {
        ArbolN<int> sub(i, list<ArbolN<int> >());
        arbol.insertarSubArbol(sub);
    }
    
    fin = clock();
    cout << "  Tiempo creación: " << medirTiempo(inicio, fin) << " segundos" << endl;
    
    // Medir tiempo de recorrido preorden
    inicio = clock();
    list<int> resultado = arbol.recorrerPreorden();
    fin = clock();
    cout << "  Tiempo recorrido preorden: " << medirTiempo(inicio, fin) << " segundos" << endl;
    assert(resultado.size() == m + 1);

    // Medir tiempo de recorrido post
    inicio = clock();
    list<int> resultado1 = arbol.recorrerPostorden();
    fin = clock();
    cout << "  Tiempo recorrido postorden: " << medirTiempo(inicio, fin) << " segundos" << endl;
    assert(resultado.size() == m + 1);

    // Medir tiempo de recorrido inorden
    inicio = clock();
    list<int> resultado2 = arbol.recorrerInorden();
    fin = clock();
    cout << "  Tiempo recorrido inorden: " << medirTiempo(inicio, fin) << " segundos" << endl;
    assert(resultado.size() == m + 1);

    // Medir tiempo de recorrido niveles
    inicio = clock();
    list<int> resultado3 = arbol.recorrerNiveles();
    fin = clock();
    cout << "  Tiempo recorrido niveles: " << medirTiempo(inicio, fin) << " segundos" << endl;
    assert(resultado.size() == m + 1);
    
    // Medir tiempo de obtención de hojas
    inicio = clock();
    list<int> hojas = arbol.getHojas();
    fin = clock();
    cout << "  Tiempo obtención hojas: " << medirTiempo(inicio, fin) << " segundos" << endl;
    assert(hojas.size() == m);
    
    // Medir tiempo de copia
    inicio = clock();
    ArbolN<int> copia(arbol);
    fin = clock();
    cout << "  Tiempo copia: " << medirTiempo(inicio, fin) << " segundos" << endl;

    // Medir tiempo obt hijos
    inicio = clock();
    arbol.getHijos();
    fin = clock();
    cout << "  Tiempo obtener hijos: " << medirTiempo(inicio, fin) << " segundos" << endl;
    
    cout << "  ✓ PASSED" << endl;
}

void testEdgeCases() {
    cout << "Test: Casos extremos" << endl;
    
    
    // Crear un árbol lineal de 100 niveles
    ArbolN<int> ultimo(100, list<ArbolN<int> >());
    for (int i = 99; i >= 0; i--) {
        list<ArbolN<int> > hijo;
        hijo.push_back(ultimo);
        ultimo = ArbolN<int>(i, hijo);
    }
    ArbolN<int> arbol = ultimo;

    //arbol.mostrarPreorden();
    
    assert(arbol.getProfundidad() == 101);
    
    // Probar vaciado de árbol grande
    arbol.vaciar();
    assert(arbol.esVacio());
    assert(arbol.getProfundidad() == 0);
    
    cout << "  ✓ PASSED" << endl;
}
 
int main() {
    cout << "Iniciando pruebas de la clase ArbolN..." << endl;
    cout << "========================================" << endl;
    
    try {
        testArbolVacio();
        testArbolUnNodo();
        testArbolSimple();
        testArbolComplejo();
        testCopiaYAsignacion();
        testInsercionYEliminacion();
        testRendimiento();
        testEdgeCases();
        
        cout << "========================================" << endl;
        cout << "¡Todas las pruebas pasaron correctamente!" << endl;
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}