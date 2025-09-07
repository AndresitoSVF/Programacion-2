#include <iostream>
#include <cassert>
#include <vector>
#include <list>
#include <ctime>
#include "ArbolBin.h"

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
void testArbolBinVacio() {
    cout << "Test: Árbol binario vacío" << endl;
    ArbolBin<int> arbol;
    
    assert(arbol.esVacio());
    assert(arbol.getProfundidad() == 0);
    
    list<int> preorden = arbol.recorrerPreorden();
    assert(preorden.empty());
    
    try {
        arbol.getRaiz();
        assert(false); // No debería llegar aquí
    } catch (const runtime_error& e) {
        // Comportamiento esperado
    }
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBinUnNodo() {
    cout << "Test: Árbol binario con un solo nodo" << endl;
    ArbolBin<int> arbol(42, ArbolBin<int>(), ArbolBin<int>());
    
    assert(!arbol.esVacio());
    assert(arbol.getProfundidad() == 1);
    assert(arbol.getRaiz() == 42);
    
    list<int> preorden = arbol.recorrerPreorden();
    list<int> esperado;
    esperado.push_back(42);
    assert(listasIguales(preorden, esperado));
    
    ArbolBin<int> hijoIzq = arbol.getHijoIzq();
    assert(hijoIzq.esVacio());
    
    ArbolBin<int> hijoDer = arbol.getHijoDer();
    assert(hijoDer.esVacio());
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBinSimple() {
    cout << "Test: Árbol binario simple" << endl;
    
    // Crear árbol: 1 con hijos 2 y 3
    ArbolBin<int> hijoIzq(2, ArbolBin<int>(), ArbolBin<int>());
    ArbolBin<int> hijoDer(3, ArbolBin<int>(), ArbolBin<int>());
    ArbolBin<int> arbol(1, hijoIzq, hijoDer);
    
    // Verificaciones
    assert(!arbol.esVacio());
    assert(arbol.getRaiz() == 1);
    assert(arbol.getProfundidad() == 2);
    
    // Verificar hijos
    ArbolBin<int> obtenidoIzq = arbol.getHijoIzq();
    assert(!obtenidoIzq.esVacio());
    assert(obtenidoIzq.getRaiz() == 2);
    
    ArbolBin<int> obtenidoDer = arbol.getHijoDer();
    assert(!obtenidoDer.esVacio());
    assert(obtenidoDer.getRaiz() == 3);
    
    // Verificar recorridos
    list<int> preorden = arbol.recorrerPreorden();
    list<int> preordenEsperado;
    preordenEsperado.push_back(1);
    preordenEsperado.push_back(2);
    preordenEsperado.push_back(3);
    assert(listasIguales(preorden, preordenEsperado));
    
    list<int> inorden = arbol.recorrerInorden();
    list<int> inordenEsperado;
    inordenEsperado.push_back(2);
    inordenEsperado.push_back(1);
    inordenEsperado.push_back(3);
    assert(listasIguales(inorden, inordenEsperado));
    
    list<int> postorden = arbol.recorrerPostorden();
    list<int> postordenEsperado;
    postordenEsperado.push_back(2);
    postordenEsperado.push_back(3);
    postordenEsperado.push_back(1);
    assert(listasIguales(postorden, postordenEsperado));
    
    cout << "  ✓ PASSED" << endl;
}

void testArbolBinComplejo() {
    cout << "Test: Árbol binario complejo" << endl;
    
    // Crear árbol:
    //       1
    //     /   \
    //    2     3
    //   / \   / 
    //  4   5 6
    
    ArbolBin<int> hoja4(4, ArbolBin<int>(), ArbolBin<int>());
    ArbolBin<int> hoja5(5, ArbolBin<int>(), ArbolBin<int>());
    ArbolBin<int> hoja6(6, ArbolBin<int>(), ArbolBin<int>());
    
    ArbolBin<int> nodo2(2, hoja4, hoja5);
    ArbolBin<int> nodo3(3, hoja6, ArbolBin<int>());
    ArbolBin<int> arbol(1, nodo2, nodo3);
    arbol.mostrarArbol();
    // Verificaciones
    assert(arbol.getProfundidad() == 3);
    
    // Verificar recorridos
    list<int> preorden = arbol.recorrerPreorden();
    list<int> preordenEsperado;
    preordenEsperado.push_back(1);
    preordenEsperado.push_back(2);
    preordenEsperado.push_back(4);
    preordenEsperado.push_back(5);
    preordenEsperado.push_back(3);
    preordenEsperado.push_back(6);
    assert(listasIguales(preorden, preordenEsperado));
    
    list<int> inorden = arbol.recorrerInorden();
    list<int> inordenEsperado;
    inordenEsperado.push_back(4);
    inordenEsperado.push_back(2);
    inordenEsperado.push_back(5);
    inordenEsperado.push_back(1);
    inordenEsperado.push_back(6);
    inordenEsperado.push_back(3);
    assert(listasIguales(inorden, inordenEsperado));
    
    list<int> postorden = arbol.recorrerPostorden();
    list<int> postordenEsperado;
    postordenEsperado.push_back(4);
    postordenEsperado.push_back(5);
    postordenEsperado.push_back(2);
    postordenEsperado.push_back(6);
    postordenEsperado.push_back(3);
    postordenEsperado.push_back(1);
    assert(listasIguales(postorden, postordenEsperado));
    
    cout << "  ✓ PASSED" << endl;
}

void testConstruccionPreorden() {
    cout << "Test: Construcción desde preorden e inorden" << endl;
    
    list<int> inorden;
    inorden.push_back(4);
    inorden.push_back(2);
    inorden.push_back(5);
    inorden.push_back(1);
    inorden.push_back(6);
    inorden.push_back(3);
    
    list<int> preorden;
    preorden.push_back(1);
    preorden.push_back(2);
    preorden.push_back(4);
    preorden.push_back(5);
    preorden.push_back(3);
    preorden.push_back(6);
    
    ArbolBin<int> arbol;
    arbol.preorden(inorden, preorden);
    
    // Verificar que los recorridos coinciden
    list<int> preordenObtenido = arbol.recorrerPreorden();
    assert(listasIguales(preordenObtenido, preorden));
    
    list<int> inordenObtenido = arbol.recorrerInorden();
    assert(listasIguales(inordenObtenido, inorden));
    
    cout << "  ✓ PASSED" << endl;
}

void testConstruccionPostorden() {
    cout << "Test: Construcción desde postorden e inorden" << endl;
    
    list<int> inorden;
    inorden.push_back(4);
    inorden.push_back(2);
    inorden.push_back(5);
    inorden.push_back(1);
    inorden.push_back(6);
    inorden.push_back(3);
    
    list<int> postorden;
    postorden.push_back(4);
    postorden.push_back(5);
    postorden.push_back(2);
    postorden.push_back(6);
    postorden.push_back(3);
    postorden.push_back(1);
    
    ArbolBin<int> arbol;
    arbol.postorden(inorden, postorden);
    
    // Verificar que los recorridos coinciden
    list<int> postordenObtenido = arbol.recorrerPostorden();
    assert(listasIguales(postordenObtenido, postorden));
    
    list<int> inordenObtenido = arbol.recorrerInorden();
    assert(listasIguales(inordenObtenido, inorden));
    
    cout << "  ✓ PASSED" << endl;
}

void testCopiaYAsignacion() {
    cout << "Test: Copia y asignación de árboles binarios" << endl;
    
    // Crear árbol original
    ArbolBin<int> hijoIzq(2, ArbolBin<int>(), ArbolBin<int>());
    ArbolBin<int> hijoDer(3, ArbolBin<int>(), ArbolBin<int>());
    ArbolBin<int> original(1, hijoIzq, hijoDer);
    
    // Probar constructor de copia
    ArbolBin<int> copia(original);
    assert(!copia.esVacio());
    assert(copia.getRaiz() == 1);
    assert(copia.getProfundidad() == 2);
    
    // Modificar original y verificar que copia no cambia
    ArbolBin<int> nuevoHijo(4, ArbolBin<int>(), ArbolBin<int>());
    original = ArbolBin<int>(5, nuevoHijo, ArbolBin<int>());
    assert(original.getRaiz() == 5);
    assert(copia.getRaiz() == 1);
    
    // Probar operador de asignación
    ArbolBin<int> asignado;
    asignado = copia;
    assert(!asignado.esVacio());
    assert(asignado.getRaiz() == 1);
    assert(asignado.getProfundidad() == 2);
    
    list<int> preordenOriginal = original.recorrerPreorden();
    list<int> preordenCopia = copia.recorrerPreorden();
    assert(!listasIguales(preordenOriginal, preordenCopia));
    
    list<int> preordenAsignado = asignado.recorrerPreorden();
    assert(listasIguales(preordenAsignado, preordenCopia));
    
    cout << "  ✓ PASSED" << endl;
}

void testVaciado() {
    cout << "Test: Vaciado de árbol binario" << endl;
    
    // Crear árbol
    ArbolBin<int> hijoIzq(2, ArbolBin<int>(), ArbolBin<int>());
    ArbolBin<int> hijoDer(3, ArbolBin<int>(), ArbolBin<int>());
    ArbolBin<int> arbol(1, hijoIzq, hijoDer);
    
    assert(!arbol.esVacio());
    assert(arbol.getProfundidad() == 2);
    
    // Vaciar árbol
    arbol.vaciar();
    
    assert(arbol.esVacio());
    assert(arbol.getProfundidad() == 0);
    
    list<int> preorden = arbol.recorrerPreorden();
    assert(preorden.empty());
    
    cout << "  ✓ PASSED" << endl;
}

void testRendimiento() {
    cout << "Test: Rendimiento con árbol binario grande" << endl;
    
    clock_t inicio, fin;
    
    // Crear un árbol binario completo de profundidad 12 (4095 nodos)
    inicio = clock();
    
    vector<ArbolBin<int> > arboles;
    for (int i = 0; i < 4095; i++) {
        arboles.push_back(ArbolBin<int>(i, ArbolBin<int>(), ArbolBin<int>()));
    }
    
    // Construir el árbol desde las hojas hacia la raíz
    for (int i = 2047; i >= 0; i--) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        if (leftChild < 4095 && rightChild < 4095) {
            arboles[i] = ArbolBin<int>(i, arboles[leftChild], arboles[rightChild]);
        }
    }
    
    ArbolBin<int> arbolGrande = arboles[0];
    
    fin = clock();
    cout << "  Tiempo creación: " << medirTiempo(inicio, fin) << " segundos" << endl;
    
    // Medir tiempo de recorrido preorden
    inicio = clock();
    list<int> resultado = arbolGrande.recorrerPreorden();
    fin = clock();
    cout << "  Tiempo recorrido preorden: " << medirTiempo(inicio, fin) << " segundos" << endl;
    assert(resultado.size() == 4095);
    
    // Medir tiempo de copia
    inicio = clock();
    ArbolBin<int> copia(arbolGrande);
    fin = clock();
    cout << "  Tiempo copia: " << medirTiempo(inicio, fin) << " segundos" << endl;
    
    cout << "  ✓ PASSED" << endl;
}

void testEdgeCases() {
    cout << "Test: Casos extremos árbol binario" << endl;
    
    // Probar con árbol degenerado (solo hijo izquierdo)
    ArbolBin<int> arbolDegenerado;
    ArbolBin<int>* actual = NULL;
    
    // Crear un árbol lineal de 100 niveles por la izquierda
    ArbolBin<int> ultimo(99, ArbolBin<int>(), ArbolBin<int>());
    for (int i = 98; i >= 0; i--) {
        ArbolBin<int> nuevo(i, ultimo, ArbolBin<int>());
        ultimo = nuevo;
    }
    arbolDegenerado = ultimo;
    
    assert(arbolDegenerado.getProfundidad() == 100);
    
    // Probar vaciado de árbol grande
    arbolDegenerado.vaciar();
    assert(arbolDegenerado.esVacio());
    assert(arbolDegenerado.getProfundidad() == 0);
    
    cout << "  ✓ PASSED" << endl;
}

void testErrores() {
    cout << "Test: Manejo de errores" << endl;
    
    // Probar obtener raíz de árbol vacío
    ArbolBin<int> vacio;
    try {
        vacio.getRaiz();
        assert(false); // No debería llegar aquí
    } catch (const runtime_error& e) {
        // Comportamiento esperado
    }
    
    // Probar obtener hijos de árbol vacío
    try {
        vacio.getHijoIzq();
        assert(false); // No debería llegar aquí
    } catch (const runtime_error& e) {
        // Comportamiento esperado
    }
    
    try {
        vacio.getHijoDer();
        assert(false); // No debería llegar aquí
    } catch (const runtime_error& e) {
        // Comportamiento esperado
    }
    
    // Probar construcción con listas de diferente tamaño
    list<int> inorden;
    inorden.push_back(1);
    inorden.push_back(2);
    inorden.push_back(3);
    
    list<int> preorden;
    preorden.push_back(1);
    preorden.push_back(2);
    
    ArbolBin<int> arbol;
    try {
        arbol.preorden(inorden, preorden);
        assert(false); // No debería llegar aquí
    } catch (const runtime_error& e) {
        // Comportamiento esperado
    }
    
    cout << "  ✓ PASSED" << endl;
}

int main() {
    cout << "Iniciando pruebas de la clase ArbolBin..." << endl;
    cout << "==========================================" << endl;
    
    try {
        testArbolBinVacio();
        testArbolBinUnNodo();
        testArbolBinSimple();
        testArbolBinComplejo();
        testConstruccionPreorden();
        testConstruccionPostorden();
        testCopiaYAsignacion();
        testVaciado();
        testRendimiento();
        testEdgeCases();
        testErrores();
        
        cout << "==========================================" << endl;
        cout << "¡Todas las pruebas pasaron correctamente!" << endl;
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}