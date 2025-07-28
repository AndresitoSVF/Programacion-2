#include <iostream>
#include <string>
#include <stdexcept> // Para capturar excepciones
#include <vector>    // Para comparar resultados de ordenamiento con std::vector
#include "Lista.h"   // Tu clase Lista

// Función auxiliar para imprimir encabezados de prueba
void printHeader(const std::string& title) {
    std::cout << "\n==========================================" << std::endl;
    std::cout << "--- " << title << " ---" << std::endl;
    std::cout << "==========================================" << std::endl;
}

// Función auxiliar para imprimir el estado de una lista
template <class Element>
void printListState(const std::string& name, const Lista<Element>& list) {
    std::cout << name << ": " << list << " (Longitud: " << list.getLongitud() << ")" << std::endl;
}

int main() {
    std::cout << "--- Inicio de pruebas exhaustivas de Lista ---" << std::endl;

    // --- Prueba de Constructores y Estado Inicial ---
    printHeader("1. Constructores y Estado Inicial");
    Lista<int> listaInt;
    printListState("listaInt (vacia)", listaInt);
    
    Lista<char> listaChar;
    printListState("listaChar (vacia)", listaChar);

    // --- Prueba de insertar() ---
    printHeader("2. Metodo insertar()");
    listaInt.insertar(10); // [10]
    listaInt.insertar(20, 0); // [20, 10]
    listaInt.insertar(30, 1); // [20, 30, 10]
    listaInt.insertar(40, listaInt.getLongitud()); // [20, 30, 10, 40] (insertar al final)
    printListState("listaInt despues de inserciones", listaInt); // Esperado: [20, 30, 10, 40]

    // Prueba de insertar en una lista vacía en pos 0
    Lista<double> listaDouble;
    listaDouble.insertar(3.14, 0);
    printListState("listaDouble (insertar en vacia)", listaDouble); // Esperado: [3.14]

    // Prueba de inserción de múltiples elementos y cadenas
    listaChar.insertar('c').insertar('b', 0).insertar('a', 0); // [a, b, c]
    printListState("listaChar despues de inserciones", listaChar);

    // Prueba de errores de insertar()
    try {
        listaInt.insertar(99, -1);
    } catch (const std::out_of_range& e) {
        std::cout << "Error esperado (insertar -1): " << e.what() << std::endl;
    }
    try {
        listaInt.insertar(99, listaInt.getLongitud() + 1);
    } catch (const std::out_of_range& e) {
        std::cout << "Error esperado (insertar > longitud): " << e.what() << std::endl;
    }

    // --- Prueba de consultar() y operador[] ---
    printHeader("3. Metodo consultar() y operador []");
    printListState("listaInt actual", listaInt); // [20, 30, 10, 40]
    std::cout << "Elemento en pos 0: " << listaInt.consultar(0) << std::endl; // Esperado: 20
    std::cout << "Elemento en pos 2 (con []): " << listaInt[2] << std::endl; // Esperado: 10
    std::cout << "Elemento en ultima pos: " << listaInt[listaInt.getLongitud() - 1] << std::endl; // Esperado: 40

    // Prueba de errores de consultar()
    try {
        listaInt.consultar(100);
    } catch (const std::out_of_range& e) {
        std::cout << "Error esperado (consultar > longitud): " << e.what() << std::endl;
    }
    try {
        listaInt.consultar(-1);
    } catch (const std::out_of_range& e) {
        std::cout << "Error esperado (consultar -1): " << e.what() << std::endl;
    }
    Lista<int> emptyList;
    try {
        emptyList.consultar(0);
    } catch (const std::out_of_range& e) {
        std::cout << "Error esperado (consultar vacia): " << e.what() << std::endl;
    }

    // --- Prueba de eliminar(pos) ---
    printHeader("4. Metodo eliminar(pos)");
    printListState("listaInt antes de eliminar", listaInt); // [20, 30, 10, 40]
    
    int intEliminado = listaInt.eliminar(1); // Eliminar 30
    std::cout << "Eliminado de pos 1: " << intEliminado << std::endl;
    printListState("listaInt despues de eliminar pos 1", listaInt); // Esperado: [20, 10, 40]

    intEliminado = listaInt.eliminar(0); // Eliminar 20
    std::cout << "Eliminado de pos 0: " << intEliminado << std::endl;
    printListState("listaInt despues de eliminar pos 0", listaInt); // Esperado: [10, 40]
    
    intEliminado = listaInt.eliminar(listaInt.getLongitud() - 1); // Eliminar 40 (último)
    std::cout << "Eliminado de ultima pos: " << intEliminado << std::endl;
    printListState("listaInt despues de eliminar ultima pos", listaInt); // Esperado: [10]

    intEliminado = listaInt.eliminar(0); // Eliminar 10 (ahora vacia)
    std::cout << "Eliminado de pos 0: " << intEliminado << std::endl;
    printListState("listaInt despues de vaciar con eliminar", listaInt); // Esperado: [Vacia]

    // Prueba de errores de eliminar(pos)
    try {
        listaInt.eliminar(0); // Eliminar de lista vacia
    } catch (const std::out_of_range& e) {
        std::cout << "Error esperado (eliminar de vacia): " << e.what() << std::endl;
    }

    // --- Prueba de vaciar() y destroy() ---
    printHeader("5. Metodos vaciar() y destroy()");
    listaInt.insertar(1).insertar(2).insertar(3);
    printListState("listaInt antes de vaciar", listaInt);
    listaInt.vaciar();
    printListState("listaInt despues de vaciar", listaInt);
    // destroy() se prueba implícitamente en el destructor y en vaciar/copiar/asignar.

    // --- Prueba de Constructor Copia y operador = ---
    printHeader("6. Constructor Copia y operador =");
    Lista<std::string> listaStrings;
    listaStrings.insertar("Hola").insertar("Mundo").insertar("C++"); // [C++, Mundo, Hola]
    printListState("listaStrings original", listaStrings);

    Lista<std::string> copiaStrings(listaStrings); // Constructor copia
    printListState("copiaStrings (constructor copia)", copiaStrings);

    Lista<std::string> listaAsignacion;
    listaAsignacion.insertar("Inicial");
    listaAsignacion = listaStrings; // Operador =
    printListState("listaAsignacion (operador =)", listaAsignacion);

    // Verificar independencia (Modificando original, copias deben permanecer iguales)
    listaStrings.eliminar(0); // Eliminar "C++" de la original
    std::cout << "--- Verificando independencia ---" << std::endl;
    printListState("listaStrings despues de eliminar C++", listaStrings); // Esperado: [Mundo, Hola]
    printListState("copiaStrings (debe ser inalterada)", copiaStrings); // Esperado: [C++, Mundo, Hola]
    printListState("listaAsignacion (debe ser inalterada)", listaAsignacion); // Esperado: [C++, Mundo, Hola]

    // Prueba de auto-asignación
    listaStrings = listaStrings;
    printListState("listaStrings despues de auto-asignacion", listaStrings); // Debe permanecer: [Mundo, Hola]

    // --- Prueba de copiar() ---
    printHeader("7. Metodo copiar()");
    Lista<int> srcList, destList;
    srcList.insertar(1).insertar(2).insertar(3); // [3, 2, 1]
    printListState("srcList", srcList);
    destList.insertar(99); // Algo en destList
    printListState("destList original", destList);
    destList.copiar(srcList);
    printListState("destList despues de copiar srcList", destList); // Esperado: [3, 2, 1]
    srcList.eliminar(0); // Modificar srcList para verificar independencia
    std::cout << "srcList despues de modificar: " << srcList << std::endl; // [2, 1]
    std::cout << "destList (debe ser inalterada): " << destList << std::endl; // [3, 2, 1]


    // --- Prueba de estaElemento() ---
    printHeader("8. Metodo estaElemento()");
    printListState("Lista para estaElemento", destList); // [3, 2, 1]
    std::cout << "Esta 2 en lista? " << (destList.estaElemento(2) ? "Si" : "No") << std::endl; // Si
    std::cout << "Esta 5 en lista? " << (destList.estaElemento(5) ? "Si" : "No") << std::endl; // No
    std::cout << "Esta 1 en lista? " << (destList.estaElemento(1) ? "Si" : "No") << std::endl; // Si

    // --- Prueba de eliminar(const Element& info, int ocurrencias) ---
    printHeader("9. Metodo eliminar(info, ocurrencias)");
    Lista<int> listWithDups;
    listWithDups.insertar(1).insertar(2).insertar(1).insertar(3).insertar(1).insertar(2).insertar(1); // [1, 2, 3, 1, 2, 1, 1]
    printListState("Lista con duplicados original", listWithDups);

    listWithDups.eliminar(1, 2); // Eliminar dos '1's
    printListState("Despues de eliminar 2x '1'", listWithDups); // Esperado: [2, 3, 1, 2, 1] (depende de cuales 1s elimine)

    listWithDups.eliminar(2, 1); // Eliminar un '2'
    printListState("Despues de eliminar 1x '2'", listWithDups); // Esperado: [3, 1, 2, 1] (si elimina el primero)

    listWithDups.eliminar(99, 1); // Elemento no existente
    printListState("Despues de intentar eliminar 99 (no existente)", listWithDups); // Sin cambios

    listWithDups.eliminar(1, 10); // Eliminar mas 1s de los que hay
    printListState("Despues de eliminar 10x '1'", listWithDups); // Esperado: [3, 2]

    listWithDups.eliminar(3, 1); // Eliminar el ultimo restante
    printListState("Despues de eliminar 3", listWithDups); // Esperado: [2]
    
    listWithDups.eliminar(2, 1);
    printListState("Despues de eliminar 2 (vacia)", listWithDups); // Esperado: [Vacia]

    // --- Prueba de modificar() ---
    printHeader("10. Metodo modificar()");
    Lista<int> listMod;
    listMod.insertar(10).insertar(20).insertar(10).insertar(30); // [30, 10, 20, 10]
    printListState("Lista original para modificar", listMod);

    listMod.modificar(10, 100, 1); // Modificar la primera ocurrencia de 10 a 100
    printListState("Despues de mod 10->100 (1 ocurrencia)", listMod); // [30, 100, 20, 10]

    listMod.modificar(10, 5, 2); // Modificar 2 ocurrencias de 10 a 5 (solo quedaba 1)
    printListState("Despues de mod 10->5 (2 ocurrencias)", listMod); // [30, 100, 20, 5]

    listMod.modificar(99, 1); // Modificar elemento en pos 1 a 99
    printListState("Despues de mod pos 1->99", listMod); // [30, 99, 20, 5]

    try {
        listMod.modificar(1000, 10); // Posición fuera de rango
    } catch (const std::out_of_range& e) {
        std::cout << "Error esperado (modificar pos > longitud): " << e.what() << std::endl;
    }

    // --- Prueba de invertir() ---
    printHeader("11. Metodo invertir()");
    Lista<int> listInv;
    listInv.insertar(1).insertar(2).insertar(3).insertar(4); // [4, 3, 2, 1]
    printListState("Lista a invertir", listInv);
    listInv.invertir();
    printListState("Lista invertida", listInv); // Esperado: [1, 2, 3, 4]

    Lista<int> listInvCorta;
    listInvCorta.insertar(5);
    printListState("Lista corta a invertir", listInvCorta);
    listInvCorta.invertir();
    printListState("Lista corta invertida", listInvCorta); // Esperado: [5]

    Lista<int> listInvVacia;
    printListState("Lista vacia a invertir", listInvVacia);
    listInvVacia.invertir();
    printListState("Lista vacia invertida", listInvVacia); // Esperado: [Vacia]

    // --- Prueba de sublista() ---
    printHeader("12. Metodo sublista()");
    Lista<int> originalSub;
    originalSub.insertar(10).insertar(20).insertar(30).insertar(40).insertar(50); // [50, 40, 30, 20, 10]
    printListState("Lista original para sublista", originalSub);

    Lista<int> s1 = originalSub.sublista(1, 4); // Indices 1, 2, 3 (40, 30, 20)
    printListState("Sublista (1,4)", s1); // Esperado: [40, 30, 20]

    Lista<int> s2 = originalSub.sublista(0, 2); // Indices 0, 1 (50, 40)
    printListState("Sublista (0,2)", s2); // Esperado: [50, 40]

    Lista<int> s3 = originalSub.sublista(3); // Desde indice 3 hasta el final (20, 10)
    printListState("Sublista (3, end)", s3); // Esperado: [20, 10]

    Lista<int> s4 = originalSub.sublista(0, 0); // Sublista vacía
    printListState("Sublista (0,0)", s4); // Esperado: [Vacia]

    try {
        originalSub.sublista(0, 100); // Fin fuera de rango
    } catch (const std::out_of_range& e) {
        std::cout << "Error esperado (sublista fin > longitud): " << e.what() << std::endl;
    }
    try {
        originalSub.sublista(5, 2); // Fin < inicio
    } catch (const std::out_of_range& e) {
        std::cout << "Error esperado (sublista fin < inicio): " << e.what() << std::endl;
    }
    try {
        originalSub.sublista(10); // Inicio fuera de rango
    } catch (const std::out_of_range& e) {
        std::cout << "Error esperado (sublista inicio > longitud): " << e.what() << std::endl;
    }

    // --- Prueba de concatenar() ---
    printHeader("13. Metodo concatenar()");
    Lista<int> l_concat1;
    l_concat1.insertar(1).insertar(2); // [2, 1]
    Lista<int> l_concat2;
    l_concat2.insertar(3).insertar(4); // [4, 3]

    printListState("Lista Concat 1", l_concat1);
    printListState("Lista Concat 2", l_concat2);

    l_concat1.concatenar(l_concat2);
    printListState("Lista Concat 1 despues de concatenar Concat 2", l_concat1); // [2, 1, 4, 3]
    printListState("Lista Concat 2 (debe ser inalterada)", l_concat2); // [4, 3]

    Lista<int> l_empty;
    Lista<int> l_nonEmpty;
    l_nonEmpty.insertar(5);
    printListState("Lista vacia (l_empty)", l_empty);
    printListState("Lista no vacia (l_nonEmpty)", l_nonEmpty);

    l_empty.concatenar(l_nonEmpty);
    printListState("l_empty concatenado con l_nonEmpty (l_empty ahora es [5])", l_empty); // [5]
    
    l_nonEmpty.concatenar(l_empty); // Concatena consigo misma (con otra que ahora es ella misma)
    printListState("l_nonEmpty concatenado con l_empty (l_nonEmpty ahora es [5, 5])", l_nonEmpty); // [5, 5]

    // --- Prueba de ordenar() ---
    printHeader("14. Metodo ordenar()");
    Lista<int> listUnsorted;
    listUnsorted.insertar(5).insertar(1).insertar(8).insertar(2).insertar(5).insertar(0).insertar(7);
    printListState("Lista desordenada", listUnsorted); // [7, 0, 5, 2, 8, 1, 5]

    listUnsorted.ordenar(Lista<int>::ordenAscendente); // Usando funcion estatica
    printListState("Lista ordenada ascendente (func estatica)", listUnsorted); // Esperado: [0, 1, 2, 5, 5, 7, 8]

    listUnsorted.ordenar([](const int& a, const int& b){ return a > b; }); // Usando lambda (descendente)
    printListState("Lista ordenada descendente (lambda)", listUnsorted); // Esperado: [8, 7, 5, 5, 2, 1, 0]

    Lista<int> singleElementList;
    singleElementList.insertar(100);
    printListState("Lista de un elemento (sin ordenar)", singleElementList);
    singleElementList.ordenar(Lista<int>::ordenAscendente);
    printListState("Lista de un elemento (ordenada)", singleElementList); // Debe permanecer igual

    Lista<int> emptySortList;
    printListState("Lista vacia (sin ordenar)", emptySortList);
    emptySortList.ordenar(Lista<int>::ordenAscendente);
    printListState("Lista vacia (ordenada)", emptySortList); // Debe permanecer vacía


    // --- Prueba de eliminarRepetidos() ---
    printHeader("15. Metodo eliminarRepetidos()");
    Lista<int> listRepetidos;
    listRepetidos.insertar(1).insertar(2).insertar(1).insertar(3).insertar(2).insertar(4).insertar(1); // [1, 4, 2, 3, 1, 2, 1] (asumiendo insertar al inicio)
    printListState("Lista con repetidos", listRepetidos);
    listRepetidos.eliminarRepetidos();
    printListState("Lista sin repetidos", listRepetidos); // Esperado: [1, 4, 2, 3] (o similar, depende de la implementación y orden de eliminación)

    Lista<int> noRepetidos;
    noRepetidos.insertar(1).insertar(2).insertar(3);
    printListState("Lista sin repetidos original", noRepetidos);
    noRepetidos.eliminarRepetidos();
    printListState("Lista sin repetidos despues de eliminarRepetidos", noRepetidos); // Debe permanecer igual

    Lista<int> allSame;
    allSame.insertar(7).insertar(7).insertar(7);
    printListState("Lista con todos iguales", allSame);
    allSame.eliminarRepetidos();
    printListState("Lista con todos iguales (despues)", allSame); // Esperado: [7]

    // --- Prueba de shiftDer() y shiftIzq() ---
    printHeader("16. Metodos shiftDer() y shiftIzq()");
    Lista<int> listShift;
    listShift.insertar(1).insertar(2).insertar(3).insertar(4).insertar(5); // [5, 4, 3, 2, 1]
    printListState("Lista original para shift", listShift);

    listShift.shiftDer(2); // Elimina los 2 primeros (5, 4)
    printListState("Despues de shiftDer(2)", listShift); // Esperado: [3, 2, 1]

    listShift.shiftIzq(1); // Elimina el ultimo (1)
    printListState("Despues de shiftIzq(1)", listShift); // Esperado: [3, 2]
    
    listShift.shiftDer(10); // Shift más allá de la longitud
    printListState("Despues de shiftDer(10) (vacia)", listShift); // Esperado: [Vacia]

    try {
        listShift.shiftDer(-1);
    } catch (const std::out_of_range& e) {
        std::cout << "Error esperado (shiftDer negativo): " << e.what() << std::endl;
    }

    // --- Prueba de operadores de conjunto (& y |) ---
    printHeader("17. Operadores de Conjunto (& y |)");
    Lista<int> setA, setB;
    setA.insertar(1).insertar(2).insertar(3).insertar(4); // [4, 3, 2, 1]
    setB.insertar(3).insertar(4).insertar(5).insertar(6); // [6, 5, 4, 3]
    
    printListState("Set A", setA);
    printListState("Set B", setB);

    Lista<int> setInterseccion = setA & setB;
    printListState("Interseccion (A & B)", setInterseccion); // Esperado: [4, 3] (orden puede variar)

    Lista<int> setUnion = setA | setB;
    printListState("Union (A | B)", setUnion); // Esperado: [4, 3, 2, 1, 6, 5] (orden puede variar)

    // Verificar que los sets originales no se modifican
    printListState("Set A (inalterado)", setA);
    printListState("Set B (inalterado)", setB);

    // Pruebas con sets vacíos
    Lista<int> setEmpty;
    Lista<int> setC; setC.insertar(7).insertar(8);
    printListState("Set Empty", setEmpty);
    printListState("Set C", setC);
    
    Lista<int> unionEmptyC = setEmpty | setC;
    printListState("Union (Empty | C)", unionEmptyC); // [8, 7]
    Lista<int> unionCEmpty = setC | setEmpty;
    printListState("Union (C | Empty)", unionCEmpty); // [8, 7]

    Lista<int> interEmptyC = setEmpty & setC;
    printListState("Interseccion (Empty & C)", interEmptyC); // [Vacia]

    // --- Prueba de operadores + y += (agregar elemento) ---
    printHeader("18. Operadores de Adicion (+ y +=)");
    Lista<std::string> words;
    words.insertar("segundo").insertar("primer"); // [primer, segundo]
    printListState("Lista de palabras original", words);

    words += "tercero"; // Agrega "tercero" al final
    printListState("Despues de += 'tercero'", words); // [primer, segundo, tercero]

    Lista<std::string> newWords = words + "cuarto"; // Crea una nueva lista con "cuarto"
    printListState("Despues de newWords = words + 'cuarto'", newWords); // [primer, segundo, tercero, cuarto]
    printListState("Lista de palabras original (debe ser inalterada)", words); // [primer, segundo, tercero]

    // --- Prueba de operadores - y -= (eliminar elemento) ---
    printHeader("19. Operadores de Eliminacion (- y -=)");
    Lista<int> nums;
    nums.insertar(10).insertar(20).insertar(10).insertar(30).insertar(10); // [10, 30, 10, 20, 10]
    printListState("Lista de numeros original", nums);

    nums -= 10; // Elimina TODAS las ocurrencias de 10
    printListState("Despues de -= 10 (elimina todos los 10s)", nums); // [30, 20]

    nums.insertar(5).insertar(20).insertar(30); // [30, 20, 5, 30, 20]
    printListState("Lista de numeros rellenada", nums);

    Lista<int> singleElim = nums - 20; // Elimina la PRIMERA ocurrencia de 20 en una copia
    printListState("singleElim(MultiElim) = nums - 20", singleElim); // [30, 5, 30, 20] (orden puede variar si es FIFO)
    printListState("Lista de numeros original (debe ser inalterada)", nums); // [30, 20, 5, 30, 20]

    // --- Prueba de operadores ++ y -- (post-incremento/decremento) ---
    printHeader("20. Operadores de Desplazamiento unitario (++ y --)");
    Lista<int> incDecList;
    incDecList.insertar(1).insertar(2).insertar(3).insertar(4); // [4, 3, 2, 1]
    printListState("Lista original", incDecList);

    ++incDecList; // Elimina el 4
    printListState("Despues de post-incremento (++)", incDecList); // [3, 2, 1]

    --incDecList; // Elimina el 1
    printListState("Despues de post-decremento (--)", incDecList); // [3, 2]

    ++incDecList; // Elimina el 3
    printListState("Despues de otro post-incremento", incDecList); // [2]

    --incDecList; // Elimina el 2 (vacia)
    printListState("Despues de otro post-decremento (vacia)", incDecList); // [Vacia]

    //++incDecList; // Deberia permanecer vacia (fuera de rango)
    //printListState("Despues de post-incremento en vacia", incDecList); // [Vacia]

    std::cout << "\n--- Fin de pruebas exhaustivas de Lista ---" << std::endl;

    return 0;
}