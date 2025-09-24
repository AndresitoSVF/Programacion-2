#include <iostream>
#include <sstream>
#include "Lista.h"
#include "cstdlib"
#include "ctime"
#include <cstdio>
#include <unistd.h>
using namespace std;

void stringANumero(string str) {
    
}

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

        while (cin.peek() == '\n' || cin.peek() == '\r') {
            cin.ignore();
            i = 0;
        }
    }
}

void leerVertical2(Lista<Lista<std::string> > &l) {
    std::string nombre;
    int i = 0;
    char c;
    
    while (std::cin.get(c)) {
        if (c == ' ' || c == '\n' || c == '\r') {
            if (!nombre.empty()) {
                if (l.getLongitud() <= i) {
                    l.insertar(Lista<std::string>(), l.getLongitud());
                }
                l[i].insertar(nombre, l[i].getLongitud());
                nombre.clear(); // Limpiar el nombre para la siguiente palabra
                i++;
            }
            
            if (c == '\n' || c == '\r') {
                cout << i << " ";
                i = 0;
            }
        } else {
            nombre += c;
        }
    }

    if (!nombre.empty()) {
        if (l.getLongitud() <= i) {
            l.insertar(Lista<std::string>(), l.getLongitud());
        }
        l[i].insertar(nombre, l[i].getLongitud());
    }
}

typedef struct {
    int casta;
    string nombre;
} Par;

void leerPares(Lista<Par> &resultado) {
    // en algun momento debe aparecer un salto de linea o un corchete
    char c;
    while (cin.get(c)) {
        if (c == ']') {
            break;
        }
        if (c == '(') {
            Par par;
            getline(cin, par.nombre, ',' );
            while (cin.peek() == ' ' || cin.peek() == ',') {
                cin.ignore();
            }
            cin >> par.casta;
            resultado.insertar(par, resultado.getLongitud());
        }
    }
}

void leerN(int n,  Lista<int> &resultado) {
    int num;
    for (int i = 0; i < n; i++) {
        cin >> num;
        resultado.insertar(num, resultado.getLongitud());
    }
}

void leerCSV(Lista<Lista<std::string> > &l) {
    std::string nombre;
    int i = 0;
    char c;
    
    while (std::cin.get(c)) {
        if (c == ',' || c == '\n' || c == '\r') {
            if (!nombre.empty()) {
                if (l.getLongitud() <= i) {
                    l.insertar(Lista<std::string>(), l.getLongitud());
                }
                l[i].insertar(nombre, l[i].getLongitud());
                nombre.clear(); // Limpiar el nombre
                i++;
            }
            if (c == '\n' || c == '\r') {
                //cout << i << " ";
                i = 0;
            }
        } else {
            nombre += c;
        }
    }

    if (!nombre.empty()) {
        if (l.getLongitud() <= i) {
            l.insertar(Lista<std::string>(), l.getLongitud());
        }
        l[i].insertar(nombre, l[i].getLongitud());
    }
}

class Solution {
public:
    
    static void elfosNavidenos (Lista<int> &resultado) {
        int n;
        std::cin >> n;
        Lista<Lista<string> > nombres;
        (leerVertical(nombres));
        // ahora viene lo sencillo O(n^3)
        int i = 0;
        while (!nombres.esVacia()) {
            cout << nombres.getLongitud();
            if (resultado.getLongitud() <= i) {
                resultado.insertar( 0, i);
            }

            // fija un elemento
            while (!nombres[0].esVacia()) {
                string nombreact = nombres[0][0];
                // busca si alguno es igual al elemento
                for (int k = 1; k < nombres[0].getLongitud(); k++) {
                    if (nombreact == nombres[0][k])
                    {
                        resultado.modificar((k  - 1) + resultado[i], i);
                        break;
                    }
                }
                nombres[0].eliminar(0);
            }

            nombres.eliminar(0);
            i++;
        }
    } 

    static void elQueRepartaElPan2025(Lista<string> &resultado) {
        int n; // casos de prueba
        cin >> n;
        // nro de pasos por cada caso de prueba
        Lista<int> saltos;
        for (int i = 0; i < n; i++) {
            int caso;
            cin >> caso;
            saltos.insertar(caso, saltos.getLongitud());
        }
        
        Lista<Lista<string> > l;
        leerVertical(l);
        cout << l << endl;

        while (!saltos.esVacia()) {
            int dir = 1;
            while (l[0].getLongitud() > 1) {
                l[0].shiftIzq(saltos[0] * dir);
                //cout << l[0] << " eliminar: " << l[0][0] << endl;
                l[0].eliminar(0);
                dir *=-1;
            }
            if (!l.esVacia() && !saltos.esVacia())
            {
                resultado.insertar(l[0][0], resultado.getLongitud());
                l.eliminar(0);
                saltos.eliminar(0);
            }
        }
    }

    static void igualandoUnMundoDesigual(Lista<string> &resultado) {
        int q;
        cin >> q;
        int N, k, t;

        // resolvemos 1 a 1 y vamos guardando el resultado en la lista resultado
        while (cin >> N) {
            cin >> k >> t;
            Lista<Par> pares;
            leerPares(pares);
            resultado.insertar(resolver(pares, N, k, t), resultado.getLongitud());
        }
    }

    static string resolver(Lista<Par> &pares, int N, int k, int t) {
        int muertes = 0;
        while (pares.getLongitud() > 1) {
            //cout << pares.getLongitud() << pares[0].nombre << endl;
            for (int i = 0; i < pares.getLongitud(); i++) {
                cout  << pares[i].nombre << " ";
            }
            cout << endl;
            if (muertes == t) {
                invertirCastas(pares, N);
                muertes = 0;
            }
            if (k > 1)
                pares.shiftDer(k - 1);
            else
                pares.shiftDer(1);
            if (!castasMenores(pares, pares[0].casta)) {
                pares.eliminar(0);
                muertes++;
            }
            //sleep(1);
        }
        return pares[0].nombre;
    }

    static void invertirCastas(Lista<Par> &pares, int N) {
        for (int i = 0; i < pares.getLongitud(); i++) {
            pares[0].casta = N - pares[0].casta;
            pares++;
        }
    }
    // lista de pares, casta a buscar si hay menores, nombre de quien esta en esa casta
    static bool castasMenores(Lista<Par> &pares, int casta) {
        pares++;
        bool menor = false;
        for (int i = 0; i < pares.getLongitud()-1; i++) {
            if (pares[0].casta < casta)
            {
                menor = true;
            }
            pares++;
        }
        return menor;
    }

    static void fuma(Lista<Lista<string> >&resultado) {
        Lista<Lista<string> > l;
        Lista<string> header;
        leerCSV(l);
        extraerHeader(header, l);
        // se crean 2 strings 1 para guardar headers y el otro los resultados
        resultado.insertar(header);
        resultado.insertar(Lista<string>(), resultado.getLongitud());
        while (!l.esVacia()) {
            resultado[1].insertar(encontrarModa(l[0]), resultado[1].getLongitud());
            l.eliminar(0);
        }
    }

    static void extraerHeader(Lista<string> &header, Lista<Lista<string> > &csv) {
        for (int i = 0; i < csv.getLongitud(); i++) {
            if (!csv[0].esVacia()){
                header.insertar(csv[0][0],header.getLongitud());
                csv[0].eliminar(0);
            }
            else {
                header.insertar("",header.getLongitud());
            }
            csv--;
        }
    }

    static string encontrarModa(Lista<string> &l) {
        if (l.esVacia()) {
            return "ninguna";
        }
        Lista<string> nombresRepetidos;
        Lista<int> repeticiones;
        while (!l.esVacia()) {
            int i = nombresRepetidos.estaElemento(l[0]);
            if (i == -1) {
                nombresRepetidos.insertar(l[0]);
                repeticiones.insertar(1);
            }
            else
            {
                repeticiones.modificar(repeticiones[i] + 1, i);
            }
            l.eliminar(0);
        }
        //cout << nombresRepetidos << repeticiones;
        int mayorIndice = repeticiones.max(Lista<int>::cMax);
        if (mayorIndice == -1) {
            return "ninguna";
        }
        else {
            return nombresRepetidos[mayorIndice];

        }
    }
};


int main () {
    /* Lista<int> l = Solution::elfosNavidenos();
    while (!l.esVacia()) {
        std::cout <<l[0] << endl;
        l.eliminar(0);
    } */
   
    //Lista<string> l;
    //Lista<Lista<string> >l; // fuma
    //Lista<int> l;
    //Solution::elQueRepartaElPan2025(l);
    //Solution::elfosNavidenos(l);
    //Solution::igualandoUnMundoDesigual(l);
    //Solution::fuma(l);
    //cout << l;
    return 0;
}