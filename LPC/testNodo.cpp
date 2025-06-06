#include <iostream>
using namespace std;

// Incluimos tu archivo de Nodo
#include "Lista.h"
#include "Nodo.h"
#include <cassert>
#include <cstdio>
#include <string>

void pruebasBasicas() {
    cout << "\n--- Prueba básica de creación de nodos ---\n";

    Nodo<int> nodo1(10);
    cout << "Nodo 1 info: " << nodo1.getInfo() << endl;

    Nodo<int> nodo2(20, &nodo1);
    cout << "Nodo 2 info: " << nodo2.getInfo() << ", apunta a Nodo 1 con info: " << nodo2.getSig()->getInfo() << endl;
}

void pruebaCopia() {
    cout << "\n--- Prueba de constructor de copia ---\n";

    Nodo<int> nodoOriginal(30);
    Nodo<int> nodoCopia(&nodoOriginal);  // Usando el constructor de copia

    cout << "Nodo original info: " << nodoOriginal.getInfo() << endl;
    cout << "Nodo copia info: " << nodoCopia.getInfo() << endl;

    // Modificamos el original para ver si afecta a la copia
    nodoOriginal.setInfo(99);
    cout << "Después de modificar el original...\n";
    cout << "Nodo original info: " << nodoOriginal.getInfo() << endl;
    cout << "Nodo copia info (debe permanecer igual): " << nodoCopia.getInfo() << endl;
}

void pruebaListaEncadenada() {
    cout << "\n--- Prueba de lista enlazada con varios nodos ---\n";

    Nodo<int> *nodo1 = new Nodo<int>(1);
    Nodo<int> *nodo2 = new Nodo<int>(2, nodo1);
    Nodo<int> *nodo3 = new Nodo<int>(3, nodo2);

    // Recorremos la lista
    Nodo<int> *actual = nodo3;
    while (actual != NULL) {
        cout << "Nodo con info: " << actual->getInfo() << endl;
        actual = actual->getSig();
    }

    // Liberamos memoria (simulando un destructor manual)
    delete nodo3;
    delete nodo2;
    delete nodo1;
}

void pruebaCasosLimite() {
    cout << "\n--- Pruebas de casos límite ---\n";

    // Caso: Nodo sin inicializar
    Nodo<int> *nodoVacio = NULL;
    cout << "Nodo vacío: " << (nodoVacio == NULL ? "Correctamente es NULL" : "Error") << endl;

    // Caso: Nodo con puntero a sí mismo
    Nodo<int> *autoReferente = new Nodo<int>(999);
    autoReferente->setSig(autoReferente);  // Auto-referencia

    cout << "Auto-referencia: " << (autoReferente->getSig() == autoReferente ? "Correcto" : "Error") << endl;

    // Caso: Modificar el nodo tras borrar el siguiente
    Nodo<int> *nodo1 = new Nodo<int>(50);
    Nodo<int> *nodo2 = new Nodo<int>(100, nodo1);
    delete nodo1;  // Eliminamos nodo1

    cout << "Acceso a nodo eliminado (esperar comportamiento indefinido o crash): " << nodo2->getSig() << endl;

    // Liberamos memoria restante
    delete nodo2;
    delete autoReferente;
}

// Función auxiliar para cadenas (C++98)
std::string intToString(int n) {
    char buf[20];
    sprintf(buf, "%d", n);
    return std::string(buf);
}

// ======================
// SUITE DE PRUEBAS
// ======================

void testConstructor() {
    Lista<int> lista;
    assert(lista.esVacia());
    assert(lista.getLongitud() == 0);
    cout << "Test constructor: OK\n";
}

void testInsercionPosiciones() {
    Lista<string> lista;
    
    // Insertar en varias posiciones
    lista.insertar("base");
    lista.insertar("inicio", 0);
    lista.insertar("medio", 1);
    lista.insertar("final", -1);
    
    assert(lista.getLongitud() == 4);
    assert(lista.consultar(0) == "inicio");
    assert(lista.consultar(1) == "medio");
    assert(lista.consultar(2) == "base");
    assert(lista.consultar(3) == "final");
    
    cout << "Test insercion posiciones: OK\n";
}

void testEliminacionCompleja() {
    Lista<int> lista;
    const int ELEMENTOS = 10;
    
    for(int i = 0; i < ELEMENTOS; ++i) {
        lista.insertar(i*2);
    }
    
    // Eliminar alternados
    assert(lista.eliminar(5) == 10);
	//lista.mostrar();
    assert(lista.eliminar(0) == 0);
	//lista.mostrar();
    assert(lista.eliminar(lista.getLongitud()-1) == 18);
	//lista.mostrar();
    // Verificar estado intermedio
    assert(lista.getLongitud() == 7);
    assert(lista.consultar(0) == 2);
    assert(lista.consultar(5) == 14);
    
    cout << "Test eliminacion compleja: OK\n";
}

void testConstructorCopia() {
    Lista<double> original;
    original.insertar(3.14);
    original.insertar(2.71);
    original.insertar(1.618);
    
    Lista<double> copia(&original);
	//cout << copia.getLongitud() << endl;
    assert(copia.getLongitud() == 3);
    assert(copia.consultar(0) == 3.14);
    assert(copia.consultar(2) == 1.618);
    
    // Modificar original no afecta copia
    original.eliminar(0);
    assert(copia.getLongitud() == 3);
    
    cout << "Test constructor copia: OK\n";
}

void testManejoMemoria() {
    Lista<string>* listaDinamica = new Lista<string>;
    const int ELEMENTOS = 100;
    
    for(int i = 0; i < ELEMENTOS; ++i) {
        listaDinamica->insertar("Dato " + intToString(i));
    }
    
    // Destrucción explícita
    delete listaDinamica;
    
    // Si no hay leaks, la prueba pasa
    cout << "Test manejo memoria: OK\n";
}

void testCasosBorde() {
    Lista<char> lista;
    
    // Insertar/eliminar en posiciones extremas
    lista.insertar('A', 0);
    lista.insertar('B', -1);
    lista.insertar('C', 1);
    
    assert(lista.eliminar(2) == 'B');
    assert(lista.eliminar(0) == 'A');
    assert(lista.getLongitud() == 1);
    
    // Vaciar y volver a usar
    lista.vaciar();
    lista.insertar('X');
    assert(lista.consultar(0) == 'X');
    
    cout << "Test casos borde: OK\n";
}

struct EstructuraComplexa {
    int id;
    std::string data;
    EstructuraComplexa() : id(0), data("") {}
    EstructuraComplexa(int i, std::string d) : id(i), data(d) {}
    bool operator==(const EstructuraComplexa& other) const {
        return id == other.id && data == other.data;
    }
};

void testTiposComplejos() {
    
    Lista<EstructuraComplexa> lista;
    EstructuraComplexa e1(1, "test1");
    EstructuraComplexa e2(2, "test2");
    
    lista.insertar(e1);
    lista.insertar(e2);
    
    assert(lista.consultar(0) == e1);
    assert(lista.consultar(1) == e2);
    
    cout << "Test tipos complejos: OK\n";
}

int main_list() {
    testConstructor();
    testInsercionPosiciones();
    testEliminacionCompleja();
    testConstructorCopia();
    testManejoMemoria();
    testCasosBorde();
    testTiposComplejos();
    
    cout << "\nTODAS LAS PRUEBAS PASARON CON EXITO!\n";
    return 0;
}

int main_node() {
    pruebasBasicas();
    pruebaCopia();
    pruebaListaEncadenada();
    pruebaCasosLimite();
    return 0;
}

int main() {
	cout << "Ejecutando pruebas de Nodo...\n";
	main_node();
	
	cout << "\nEjecutando pruebas de Lista...\n";
	main_list();
	
	return 0;
}