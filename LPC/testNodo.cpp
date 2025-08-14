#include <iostream>
using namespace std;

// Incluimos tu archivo de Nodo
#include "Lista.h"
#include "Nodo.h"
#include "Pila.h"
#include "Cola.h"
#include <cassert>
#include <cstdio>
#include <string>

void pruebasBasicas() {
    cout << "\n--- Prueba básica de creación de nodos ---\n";
    int n = 10;
    Nodo<int> nodo1(n);
    cout << "Nodo 1 info: " << nodo1.getInfo() << endl;
    n *=2;
    Nodo<int> nodo2(n, &nodo1, NULL);
    cout << "Nodo 2 info: " << nodo2.getInfo() << ", apunta a Nodo 1 con info: " << nodo2.getSig()->getInfo() << endl;
}

void pruebaCopia() {
    cout << "\n--- Prueba de constructor de copia ---\n";
    int n = 20;
    Nodo<int> nodoOriginal(n);
    n+=10;
    nodoOriginal.setSig(new Nodo<int>(n));  // Nodo siguiente
    Nodo<int> *aux = nodoOriginal.getSig();
    n+=10;
    aux->setSig(new Nodo<int>(n));
    Nodo<int> nodoCopia(&nodoOriginal);  // Usando el constructor de copia

    cout /* << "Nodo original info: " << nodoOriginal.getInfo() */ << endl << endl << endl << endl;
   /*  cout << "Nodo copia info: " << nodoCopia.getInfo() << endl; */
    cout << "Nodo original: " << &nodoOriginal << endl;
    cout << "Nodo copia: " << &nodoCopia << endl;
    n = 99;
    aux->setInfo(n);
    cout << "Nodo original siguiente cambiado: " << &nodoOriginal << endl << "el copia no debe cambiar: " << &nodoCopia << endl;


    // Modificamos el original para ver si afecta a la copia
    n = 180;
    nodoOriginal.setInfo(n);
    cout << "Después de modificar el original...\n";
    cout << "Nodo original info: " << nodoOriginal.getInfo() << endl;
    cout << "Nodo copia info (debe permanecer igual): " << nodoCopia.getInfo() << endl << endl;
}

void pruebaListaEncadenada() {
    cout << "\n--- Prueba de lista enlazada con varios nodos ---\n";

    Nodo<int> *nodo1 = new Nodo<int>(1);
    Nodo<int> *nodo2 = new Nodo<int>(2, nodo1, NULL);
    Nodo<int> *nodo3 = new Nodo<int>(3, nodo2, NULL);

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
    Nodo<int> *nodo2 = new Nodo<int>(100, nodo1, NULL);
    delete nodo1;  // Eliminamos nodo1

    //cout << "Acceso a nodo eliminado (esperar comportamiento indefinido o crash): " << nodo2->getSig() << endl;

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
    lista.insertar("final", lista.getLongitud());
    
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
    
    lista.eliminar(5);
    lista.eliminar(0);
    lista.eliminar(lista.getLongitud()-1);
	lista.mostrar();
    //assert( == 0);
	//lista.mostrar();
    //assert( == 18);
	//lista.mostrar();
    // Verificar estado intermedio
    assert(lista.getLongitud() == 7);
    assert(lista.consultar(lista.getLongitud() -1) == 2);
    
    cout << "Test eliminacion compleja: OK\n";
}

void testConstructorCopia() {
    Lista<double> original;
    original.insertar(3.14);
    original.insertar(2.71);
    original.insertar(1.618);
    
    Lista<double> copia(original);
	//cout << copia.getLongitud() << endl;
    assert(copia.getLongitud() == 3);
    assert(copia.consultar(copia.getLongitud()-1) == 3.14);
    assert(copia.consultar(0) == 1.618);
    
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
    lista.insertar('B', lista.getLongitud());
    lista.insertar('C', 1);
    lista.eliminar(2);lista.eliminar(0);
    //assert( == 'B');
    //assert( == 'A');
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
    
    assert(lista.consultar(1) == e1);
    assert(lista.consultar(0) == e2);
    
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
	Lista<int> lista;
    lista.insertar(1);
    lista.insertar(2);
    lista.insertar(3);
    lista.insertar(4);
    lista.mostrar();
    lista.ordenar(Lista<int>::ordenAscendente);
    lista.mostrar();
    cout << lista.estaElemento(3) << " - " << lista.estaElemento(6) << endl;
    lista.modificar(5,1).modificar(6,0).modificar(4,0).modificar(4,9,lista.getLongitud()).mostrar();
    lista.modificar(7, 0).mostrar();
    cout << "lista: " << lista;

    cout << "Lista original: " << lista << endl;
    cout << "Lista invertida: " << lista.invertir() << endl;
    cout << "Lista desplazada a la derecha: " << lista++ << endl;
    cout << "Lista desplazada a la izquierda: " << lista-- << endl;
    cout << "Lista restaurada: " << (lista) << endl;
    //cout << "Lista concatenada con sí misma: " << (lista + lista) << endl;
    cout << "son iguales ella consigo misma? " << (lista == lista) << endl << endl;
    cout << lista.sublista(1, 3) << endl;
    cout << lista << endl;
    //cout << "Lista despues de eliminar 2: " << (lista -= 2) << endl;
    //cout << "Lista despues de eliminar 3: " << (lista -= 3) << endl;

    Lista<Lista<int> > lista2;
    lista2.insertar(lista);
    lista2.insertar(lista.invertir());
    lista2.insertar(lista.sublista(1, 3));
    cout << "Lista de listas: " << lista2 << endl;
    cout << "Lista de listas invertida: " << lista2.invertir() << endl;

	return 0;
}


/* #include <iostream>
#include <cstdio>
using namespace std;

int main() {
    // Complete the code.
    
    return 0;
} */