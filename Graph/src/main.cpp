#include <iostream>
#include "GraphUndirected.h"
#include <unordered_map>
#include <list>

// Renos zombies, entrada pares:
/* 
AB
CB
CA
...
*/
using namespace std;
unordered_map<char, list<pair<char, float> > > leerEntradaUsandoMaps() {
    unordered_map<char, list<pair<char, float> > > m;
    char v;
    char w;
    while (cin >> v >> w) {
        // no se tiene el nodo en el mapa
        if (m.find(v) == m.end()) {
            m[v] = list<pair<char, float> >();
        }
        m[v].push_back(make_pair(w,0));
    }
    return m;
}

int main() {
    unordered_map<char, list<pair<char, float> > > m = leerEntradaUsandoMaps();
    GraphUndirected<char> g(m);
    list<pair<char, char> > bridges = g.getBridges();
    //g.show();
    for (auto it = bridges.begin(); it != bridges.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }
    
}