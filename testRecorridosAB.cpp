#include "ArbolBin.h"
#include <iostream>
#include <list>

template<class Element>
// pre, pos, in
void mostrar3Recorridos(std::list<Element> l1, std::list<Element> l2, std::list<Element> l3) {
	std::cout << "Lista en pre: "; mostrarLista(l1); std::cout << std::endl;
	
	std::cout << "Lista en post: "; mostrarLista(l2); std::cout << std::endl;

	std::cout << "Lista en in: "; mostrarLista(l3); std::cout << std::endl;
}

template<class Element>
void igualdad(std::string texto, std::list<Element> l1, std::list<Element> l2) {
	std::string resultado = l1 == l2 ? "si": "no";
	std::cout << texto << " son iguales? " << resultado << std::endl;
}


int main() {
	std::cout << "Crear preorden" << std::endl;
	std::list<int> lPreorden, lInorden;
	// pre
	for (int i = 0; i < 11; i++) {
		int x;
		std::cin >> x; 
		lPreorden.push_back(x);
	}
	//in 
	for (int i = 0; i < 11; i++) {
		int x;
		std::cin >> x; 
		lInorden.push_back(x);
	}  
	ArbolBin<int> a;   
	a.preorden(lInorden, lPreorden);
	
	std::cout << "profundidad:" << a.getProfundidad() << std::endl;

	std::list<int> lRPos1 = a.recorrerPostorden(); 
	std::list<int> lRPre1 = a.recorrerPreorden();
	std::list<int> lRIn1 = a.recorrerInorden(); 

	mostrar3Recorridos(lRPre1, lRPos1, lRIn1);

	std::cout << "Crear postorden" << std::endl;
	a.postorden(lRIn1, lRPos1);
	std::cout << "profundidad:" << a.getProfundidad() << std::endl;
	 
	std::list<int> lRPos2 = a.recorrerPostorden();
	std::list<int> lRPre2 = a.recorrerPreorden();
	std::list<int> lRIn2 = a.recorrerInorden();

	mostrar3Recorridos(lRPre2, lRPos2, lRIn2);

	
	igualdad("posorden",lRPos1, lRPos2);
	igualdad("preorden",lRPre1, lRPre2);
	igualdad("inorden",lRIn1, lRIn2);
   
	
	return 0;
}


