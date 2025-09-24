#include <iostream>
#include <cassert>
#include <vector>
#include <list>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "ArbolBB.h"

using namespace std;

// Función para medir el tiempo de ejecución
double medirTiempo(clock_t inicio, clock_t fin) {
    return double(fin - inicio) / CLOCKS_PER_SEC;
}

// Función para verificar si una lista está ordenada (alternativa a is_sorted de C++11)
template <typename T>
bool estaOrdenada(const list<T>& lista) {
    if (lista.empty()) return true;
    
    typename list<T>::const_iterator it = lista.begin();
    T anterior = *it;
    ++it;
    
    for (; it != lista.end(); ++it) {
        if (*it < anterior) {
            return false;
        }
        anterior = *it;
    }
    
    return true;
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

// Función para mezclar elementos (alternativa a random_shuffle de C++98)
template <typename T>
void mezclar(vector<T>& elementos) {
    srand(time(NULL));
    for (int i = elementos.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(elementos[i], elementos[j]);
    }
}

// Pruebas unitarias
void testArbolBBVacio() {
    cout << "Test: Árbol binario de búsqueda vacío" << endl;
    ArbolBB<int> arbol;
    
    assert(arbol.esVacio());
    assert(arbol.getProfundidad() == 0);
    assert(!arbol.consultar(42));
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBBInsercion() {
    cout << "Test: Inserción en árbol binario de búsqueda" << endl;
    ArbolBB<int> arbol;
    
    // Insertar elementos
    arbol.insertar(50);
    arbol.insertar(30);
    arbol.insertar(70);
    arbol.insertar(20);
    arbol.insertar(40);
    arbol.insertar(60);
    arbol.insertar(80);
    
    // Verificar que no está vacío
    assert(!arbol.esVacio());
    assert(arbol.getProfundidad() > 0);
    
    // Verificar que todos los elementos insertados existen
    assert(arbol.consultar(50));
    assert(arbol.consultar(30));
    assert(arbol.consultar(70));
    assert(arbol.consultar(20));
    assert(arbol.consultar(40));
    assert(arbol.consultar(60));
    assert(arbol.consultar(80));
    
    // Verificar que elementos no insertados no existen
    assert(!arbol.consultar(10));
    assert(!arbol.consultar(90));
    assert(!arbol.consultar(55));
    
    // Verificar que el recorrido inorden está ordenado
    list<int> inorden = arbol.recorrerInorden();
    assert(estaOrdenada(inorden));
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBBEliminacion() {
    cout << "Test: Eliminación en árbol binario de búsqueda" << endl;
    ArbolBB<int> arbol;
    
    // Insertar elementos
    arbol.insertar(50);
    arbol.insertar(30);
    arbol.insertar(70);
    arbol.insertar(20);
    arbol.insertar(40);
    arbol.insertar(60);
    arbol.insertar(80);
    
    // Eliminar hoja (20)
    arbol.eliminar(20);
    assert(!arbol.consultar(20));
    assert(arbol.consultar(30));
    
    // Eliminar nodo con un hijo (30 ahora tiene solo el hijo 40)
    arbol.eliminar(30);
    assert(!arbol.consultar(30));
    assert(arbol.consultar(40));
    
    // Eliminar nodo con dos hijos (70)
    arbol.eliminar(70);
    assert(!arbol.consultar(70));
    assert(arbol.consultar(60));
    assert(arbol.consultar(80));
    
    // Eliminar raíz (50)
    arbol.eliminar(50);
    assert(!arbol.consultar(50));
    
    // Verificar que los elementos restantes existen
    assert(arbol.consultar(40));
    assert(arbol.consultar(60));
    assert(arbol.consultar(80));
    
    // Verificar que el recorrido inorden está ordenado
    list<int> inorden = arbol.recorrerInorden();
    assert(estaOrdenada(inorden));
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBBEliminacionCasoComplejo() {
    cout << "Test: Eliminación caso complejo en árbol binario de búsqueda" << endl;
    ArbolBB<int> arbol;
    
    // Insertar elementos para crear un caso complejo
    arbol.insertar(50);
    arbol.insertar(30);
    arbol.insertar(70);
    arbol.insertar(20);
    arbol.insertar(40);
    arbol.insertar(60);
    arbol.insertar(80);
    arbol.insertar(35);
    arbol.insertar(45);
    arbol.insertar(65);
    arbol.insertar(75);
    arbol.insertar(85);
    
    // Eliminar nodo con dos hijos (70) cuyo sucesor (75) tiene un hijo derecho (80)
    arbol.eliminar(70);
    assert(!arbol.consultar(70));
    assert(arbol.consultar(75));
    assert(arbol.consultar(80));
    
    // Verificar que el árbol mantiene todas las propiedades
    list<int> inorden = arbol.recorrerInorden();
    assert(estaOrdenada(inorden));
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBBInsercionDuplicados() {
    cout << "Test: Inserción de duplicados en árbol binario de búsqueda" << endl;
    ArbolBB<int> arbol;
    
    // Insertar elementos duplicados
    arbol.insertar(50);
    arbol.insertar(30);
    arbol.insertar(50); // Duplicado
    arbol.insertar(30); // Duplicado
    
    // Verificar que los elementos existen
    assert(arbol.consultar(50));
    assert(arbol.consultar(30));
    
    // Verificar que el recorrido inorden está ordenado
    list<int> inorden = arbol.recorrerInorden();
    assert(estaOrdenada(inorden));
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBBCopiaYAsignacion() {
    cout << "Test: Copia y asignación en árbol binario de búsqueda" << endl;
    ArbolBB<int> arbol1;
    
    // Insertar elementos
    arbol1.insertar(50);
    arbol1.insertar(30);
    arbol1.insertar(70);
    arbol1.insertar(20);
    arbol1.insertar(40);
    
    // Probar constructor de copia
    ArbolBB<int> arbol2(arbol1);
    assert(!arbol2.esVacio());
    assert(arbol2.consultar(50));
    assert(arbol2.consultar(30));
    assert(arbol2.consultar(70));
    
    // Probar operador de asignación
    ArbolBB<int> arbol3;
    arbol3 = arbol1;
    assert(!arbol3.esVacio());
    assert(arbol3.consultar(50));
    assert(arbol3.consultar(30));
    assert(arbol3.consultar(70));
    
    // Modificar arbol1 y verificar que arbol2 y arbol3 no cambian
    arbol1.eliminar(50);
    assert(arbol2.consultar(50));
    assert(arbol3.consultar(50));
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBBRendimiento() {
    cout << "Test: Rendimiento del árbol binario de búsqueda" << endl;
    
    ArbolBB<int> arbol;
    const int ELEMENTOS = 10000;
    
    // Medir tiempo de inserción
    clock_t inicio = clock();
    for (int i = 0; i < ELEMENTOS; i++) {
        arbol.insertar(i);
    }
    clock_t fin = clock();
    cout << "  Tiempo inserción " << ELEMENTOS << " elementos: " << medirTiempo(inicio, fin) << " segundos" << endl;
    
    // Medir tiempo de consulta
    inicio = clock();
    for (int i = 0; i < ELEMENTOS; i++) {
        assert(arbol.consultar(i));
    }
    fin = clock();
    cout << "  Tiempo consulta " << ELEMENTOS << " elementos: " << medirTiempo(inicio, fin) << " segundos" << endl;
    
    // Medir tiempo de eliminación
    inicio = clock();
    for (int i = 0; i < ELEMENTOS; i++) {
        arbol.eliminar(i);
    }
    fin = clock();
    cout << "  Tiempo eliminación " << ELEMENTOS << " elementos: " << medirTiempo(inicio, fin) << " segundos" << endl;
    
    assert(arbol.esVacio());
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBBEliminacionElementoNoExistente() {
    cout << "Test: Eliminación de elemento no existente en árbol binario de búsqueda" << endl;
    ArbolBB<int> arbol;
    
    // Insertar elementos
    arbol.insertar(50);
    arbol.insertar(30);
    arbol.insertar(70);
    
    // Intentar eliminar elemento no existente
    try {
        arbol.eliminar(100);
        // No debería lanzar excepción, solo no hacer nada
        assert(true);
    } catch (...) {
        assert(false); // No debería lanzar excepción
    }
    
    // Verificar que los elementos originales siguen existiendo
    assert(arbol.consultar(50));
    assert(arbol.consultar(30));
    assert(arbol.consultar(70));
    
    // Verificar que el recorrido inorden está ordenado
    list<int> inorden = arbol.recorrerInorden();
    assert(estaOrdenada(inorden));
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBBRecorridos() {
    cout << "Test: Recorridos en árbol binario de búsqueda" << endl;
    ArbolBB<int> arbol;
    
    // Insertar elementos en orden no secuencial
    arbol.insertar(50);
    arbol.insertar(30);
    arbol.insertar(70);
    arbol.insertar(20);
    arbol.insertar(40);
    arbol.insertar(60);
    arbol.insertar(80);
    
    // Verificar recorrido inorden (debe estar ordenado)
    list<int> inorden = arbol.recorrerInorden();
    list<int> inordenEsperado;
    inordenEsperado.push_back(20);
    inordenEsperado.push_back(30);
    inordenEsperado.push_back(40);
    inordenEsperado.push_back(50);
    inordenEsperado.push_back(60);
    inordenEsperado.push_back(70);
    inordenEsperado.push_back(80);
    assert(listasIguales(inorden, inordenEsperado));
    
    // Verificar recorrido preorden
    list<int> preorden = arbol.recorrerPreorden();
    // El preorden exacto depende de la estructura, pero debe contener todos los elementos
    assert(preorden.size() == 7);
    for (int i : inordenEsperado) {
        assert(find(preorden.begin(), preorden.end(), i) != preorden.end());
    }
    
    // Verificar recorrido postorden
    list<int> postorden = arbol.recorrerPostorden();
    // El postorden exacto depende de la estructura, pero debe contener todos los elementos
    assert(postorden.size() == 7);
    for (int i : inordenEsperado) {
        assert(find(postorden.begin(), postorden.end(), i) != postorden.end());
    }
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBBPropiedadesABB() {
    cout << "Test: Propiedades de árbol binario de búsqueda" << endl;
    ArbolBB<int> arbol;
    
    // Insertar elementos en orden aleatorio
    vector<int> elementos;
    for (int i = 1; i <= 15; i++) {
        elementos.push_back(i * 10);
    }
    
    // Mezclar elementos manualmente (evitando random_shuffle)
    for (int i = elementos.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(elementos[i], elementos[j]);
    }
    
    for (int elemento : elementos) {
        arbol.insertar(elemento);
    }
    
    // Verificar que todos los elementos insertados existen
    for (int elemento : elementos) {
        assert(arbol.consultar(elemento));
    }
    
    // Verificar que el recorrido inorden está ordenado
    list<int> inorden = arbol.recorrerInorden();
    assert(estaOrdenada(inorden));
    
    // Eliminar algunos elementos y verificar que sigue siendo ABB
    arbol.eliminar(50);
    arbol.eliminar(30);
    arbol.eliminar(70);
    
    // Verificar que los elementos eliminados no existen
    assert(!arbol.consultar(50));
    assert(!arbol.consultar(30));
    assert(!arbol.consultar(70));
    
    // Verificar que los elementos no eliminados siguen existiendo
    assert(arbol.consultar(20));
    assert(arbol.consultar(40));
    assert(arbol.consultar(60));
    assert(arbol.consultar(80));
    
    // Verificar que el recorrido inorden sigue ordenado
    inorden = arbol.recorrerInorden();
    assert(estaOrdenada(inorden));
    
    cout << "  ✓ PASSED" << endl;
}

int main() {
    cout << "Iniciando pruebas de la clase ArbolBB..." << endl;
    cout << "========================================" << endl;
    
    try {
        testArbolBBVacio();
        testArbolBBInsercion();
        testArbolBBEliminacion();
        testArbolBBEliminacionCasoComplejo();
        testArbolBBInsercionDuplicados();
        testArbolBBCopiaYAsignacion();
        testArbolBBRendimiento();
        testArbolBBEliminacionElementoNoExistente();
        testArbolBBRecorridos();
        testArbolBBPropiedadesABB();
        
        cout << "========================================" << endl;
        cout << "¡Todas las pruebas pasaron correctamente!" << endl;
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}