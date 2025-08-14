#include <iostream>
#include <sstream>
#include "Lista.h"
#include "cstdlib"
#include "ctime"
#include <cstdio>
using namespace std;

void leerVertical(Lista<Lista<std::string> > &l) {
    string nombre;
    int i = 0;
    while (std::cin >> nombre) {
        if (l.getLongitud() <= i) {
            l.insertar(Lista<std::string>(), l.getLongitud());
            }
            l[i].insertar(nombre, l[i].getLongitud());
            i++;

            while (cin.peek() == ' ') {
            cin.ignore();
            }

            if (cin.peek() == '\n') {
                i = 0;
            }
        }
    }


class Solution {
public:
    

    static Lista<int> elfosNavidenos () {
        int n;
        std::cin >> n;
        Lista<Lista<string> > nombres;
        (leerVertical(nombres));
        Lista<int> resultado;
        // ahora viene lo sencillo O(n^3)
        for (int i = 0; i < n; i++) {
            bool visitados[nombres[i].getLongitud()];
            for (int k = 0; k < nombres[i].getLongitud();k ++) {
                visitados[i] = false;
            }

            if (resultado.getLongitud() < i) {
                resultado.insertar( 0, i - 1);
            }

            // fija un elemento
            for (int j = 0; j < nombres[i].getLongitud(); j++) {
                string nombreact = nombres[i][j];

                // busca si alguno es igual al elemento
                for (int k = j + 1; k < nombres[i].getLongitud(); k++) {
                    if (nombreact == nombres[i][k] && (!visitados[i] || !visitados[k]))
                    {
                        visitados[i] = true;
                        visitados[k] = true;
                        if (resultado.getLongitud() <= i) {
                            resultado.insertar((k - (j + 1)), resultado.getLongitud());
                        }
                        else
                        {
                            resultado.modificar((k  - (j + 1)) + resultado[i], i);
                        }
                        //cout << endl << i << " e " << k << "r1: "<< (k  - (j+ 1)) << "i " << i << n << endl;
                        break;
                    }
                    //cout << "act: " << nombreact << " k: " << nombres[i][k] << endl;
                }
                
                
            }

            if (i == n - 1 && resultado.getLongitud() < i + 1) {
                resultado.insertar( 0, i);
            }
        }
        
        return resultado;
    } 

    
    


    static void elQueRepartaElPan2025(/* Lista<string> &resultado */) {
        int n; // casos de prueba
        cin >> n;
        // nro de pasos por cada caso de prueba
        Lista<int> saltos;
        for (int i = 0; i < n; i++) {
            int caso;
            cin >> caso;
            saltos.insertar(caso, saltos.getLongitud());
        }
        cout << saltos;
        
        Lista<Lista<string> > l;
        leerVertical(l);
        /* for (int i = 0; i < l.getLongitud(); i++) {
            cout << endl << " len: " << l[i].getLongitud() << endl;
            l[i].mostrar();
        } */
        cout << l;
        

        /* 
        k = 2
        desplz izquierda
        [1,2,3,4] -> [2,3,4,1] -> [3,4,1,2] borramos 3 -> [4,1,2]
        desplz derecha = desplz izq negativo
        [4,1,2] -> [2,4,1] -> [1,2,4] eliminamos el 1 ....
        [2,1,4] -> [1,4,2]
        
        
        */
        /* while (!l.esVacia()) {
            int dir = 1;
            while (l[0].getLongitud() > 1) {
                l[0].shiftIzq(saltos[0] * dir);
                l[0].eliminar(0);
                l[0].shiftDer(1);
                dir *=-1;
                cout << "( "<< l[0].getLongitud()<< ") "<< endl;
            }
            resultado.insertar(l[0][0], resultado.getLongitud());
            if (!l.esVacia() && !saltos.esVacia())
            {
                l.eliminar(0);
                saltos.eliminar(0);
            }
        }

        return resultado;*/
    } 
};


int main () {
    /* Lista<int> l = Solution::elfosNavidenos();
    while (!l.esVacia()) {
        std::cout <<l[0] << endl;
        l.eliminar(0);
    } */
    //Lista<string> l;
    Solution::elQueRepartaElPan2025();
    //cout << l;
    return 0;
}