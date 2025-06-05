#include "Lista.h"
#include <iostream>

int main() {
    Lista<int> lista;
    for (int i = 0; i < 10; i++) {
        lista.insertar(i, i);
    }
    std::cout << "Lista original: ";
    lista.mostrarLista();
    std::cout << std::endl;
    
    
    
    return 0;
}