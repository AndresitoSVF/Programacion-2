#ifndef GRAPH_U_CPP
#define GRAPH_U_CPP
#include "GraphUndirected.h"
#include "NodeVertex.h"
#include "NodeEdge.h"
#include <stdexcept>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>


/* 
********
Helpers
********
*/

// OK
template<class T>
void GraphUndirected<T>::copy(const GraphUndirected<T> &other) {
    if (this == &other) {
        return;
    }

    // primero se crean todos los nodos y se guardan en el mapa.

    std::unordered_map<T, NodeVertex<T> *> ownNodes;
    NodeVertex<T> *otherCurrentVertex = other.firstNode;
    NodeVertex<T> *ownCurrentVertex = NULL;
    firstNode = NULL;

    if (otherCurrentVertex != NULL) {
        ownCurrentVertex = new NodeVertex(otherCurrentVertex->getInfo());
        firstNode = ownCurrentVertex;
        // meterlo en el ownNodes
        ownNodes[otherCurrentVertex->getInfo()] = ownCurrentVertex;
        otherCurrentVertex = otherCurrentVertex->getNext();
    }


    while (otherCurrentVertex != NULL) {
        NodeVertex<T> *newNode = new NodeVertex(otherCurrentVertex->getInfo());
        ownCurrentVertex->setNext(newNode);

        ownCurrentVertex = ownCurrentVertex->getNext();
        ownNodes[otherCurrentVertex->getInfo()] = ownCurrentVertex;
        otherCurrentVertex = otherCurrentVertex->getNext();
    }

    // tenemos los vertices del nuevo grafo en el mapa, ahora hay que hacer los enlaces.

    // reutilizamos other y own currentVertex
    otherCurrentVertex = other.firstNode;
    
    while (otherCurrentVertex != NULL) {
        // el apuntador de la lista de adyacencia
        NodeEdge<T> *otherCurrentEdge = otherCurrentVertex->getListAdj();
        ownCurrentVertex = ownNodes[otherCurrentVertex->getInfo()];

        while (otherCurrentEdge != NULL) {
            NodeEdge<T> *newEdge = new NodeEdge<T>(otherCurrentEdge->getWeight());
            newEdge->setInfo(ownNodes[otherCurrentEdge->getInfo()->getInfo()]);

            newEdge->setNext(ownCurrentVertex->getListAdj());
            ownCurrentVertex->setListAdj(newEdge);
            
            otherCurrentEdge = otherCurrentEdge->getNext();
        }
        otherCurrentVertex = otherCurrentVertex->getNext();
    }

    nodeCount = other.nodeCount;
    edgeCount = other.edgeCount;
}

// OK
// crear la conexion v -> w
template<class T>
void GraphUndirected<T>::createConnection(NodeVertex<T> *v, NodeVertex<T> *w, float weight) {
    if (v == NULL || w == NULL) { 
        std::cout << "createConnection: Vertice nulo" << std::endl;
        return;
    }

    NodeEdge<T> *newEdgeV = new NodeEdge<T>(weight);
    newEdgeV->setInfo(w);
    newEdgeV->setNext(v->getListAdj());
    v->setListAdj(newEdgeV);
}

// OK
// eliminar v -> w
template<class T>
void GraphUndirected<T>::removeConnection(NodeVertex<T> *v, NodeVertex<T> *w){
    if (v == NULL || w == NULL) {
        std::cout << "removeConnection: Vertice nulo" << std::endl;
        return;
    }
    
    NodeEdge<T> *currentEdge = v->getListAdj();
    NodeEdge<T> *previousEdge = NULL;
    
    // vamos recorriendo los vertices hasta llegar al que queremos
    while (currentEdge != NULL) {

        if (currentEdge->getInfo() == w){
            if(previousEdge == NULL) {
                // cuando es el primer elemento
                v->setListAdj(currentEdge->getNext());
            }
            else {
                // cualquier otro caso
                previousEdge->setNext(currentEdge->getNext());
            }
            delete currentEdge;
            return;
        }

        previousEdge = currentEdge;
        currentEdge = currentEdge->getNext();
    }
    
    // si current es null entonces no lo encontró
    if (currentEdge == NULL) {
        //throw std::out_of_range("removeEdge(NodeVertex<T> *v, NodeVertex<T> *w): Arco no encontrado");
        std::cout << "removeEdge(NodeVertex<T> *v, NodeVertex<T> *w): Arco no encontrado";
    }
    
}

// OK
template<class T>
NodeVertex<T>* GraphUndirected<T>::findNode(const T &info) const {
    NodeVertex<T> *current = firstNode;
    while (current != NULL) {
        if (current->getInfo() == info) {
            return current;
        }
        current = current->getNext();
    }
    return NULL;
}

// OK
template<class T>
NodeVertex<T> *GraphUndirected<T>::createAndReturnNode(const T &v){
    if (this->findNode(v) != NULL) {
        //throw std::invalid_argument("addNode(const T &v): Este nodo ya fue añadido.");
        std::cout << "createAndReturnNode(const T &v): Este nodo ya fue añadido."  << std::endl;
        return this->findNode(v);
    }

    NodeVertex<T> *newNode = new NodeVertex<T>(v);

    newNode->setNext(firstNode);
    firstNode = newNode;
    nodeCount++;

    return newNode;
}

// OK
template<class T>
void GraphUndirected<T>::addEdge(NodeVertex<T> *v, NodeVertex<T> *w, float weight){
    
    if (v == NULL || w == NULL) {
        //throw std::out_of_range("addEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los vetices");
        std::cout << "addEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los vetices" << std::endl;
        return;
    }

    // Check for existing edge
    NodeEdge<T> *current = v->getListAdj();
    while (current != NULL) {
        if (current->getInfo() == w) {
            //throw std::out_of_range("addEdge(const T &v, const T& w, const float weight): Esta conexion ya existe");
            return;
        }
        current = current->getNext();
    }
    
        
    if (v == w) {
        createConnection(v, w, weight); 
    } else {
        createConnection(v, w, weight); // v -> w
        createConnection(w, v, weight); // w -> v
    }
    
    edgeCount++;
}


template<class T>
std::list<T> GraphUndirected<T>::findPathBetween(const T &initialNode, const T &finalNode, std::list<std::pair<NodeVertex<T>*,NodeVertex<T>*> > &exceptions) {
    /* // bfs modificado
    std::queue<T> currentNode;
    std::unordered_map<T, bool> visited;

    // llenar el mapa y validar que el nodo inicial se encuentra
    NodeVertex<T> *current = firstNode;

    while (current != NULL) {
        visited[current->getInfo()] = false;
        current = current->getNext();
    }

    std::list<T> result;

    if (visited.find(initialNode) == visited.end()) {
        std::cout << "bfs (const T &initialNode): No se encuetra el nodo inicial en el grafo"; 
        return result;
    }

    std::list<T> neighbors;
    T v, w;

    if (nodeCount >= 1) {
        currentNode.push(initialNode);
        visited[initialNode] = true;

        while (!currentNode.empty()) {
            v = currentNode.front();
            neighbors = getNeighbors(v);
            while (!neighbors.empty()) {
                w = neighbors.front();
                if (!visited[w]) {
                    currentNode.push(w);
                    visited[w] = true;
                }
                neighbors.pop_front();
            }
            result.push_back(v);
            currentNode.pop();
        }
    }
    return result; */
}

// OK
template<class T>
bool GraphUndirected<T>::existPathBetween(const T &initialNode, const T &finalNode, std::set<std::pair<T, T> > &exceptions) {
    // bfs modificado
    std::queue<T> currentNode;
    std::unordered_map<T, bool> visited;
    

    // llenar el mapa y validar que el nodo inicial se encuentra
    NodeVertex<T> *current = firstNode;

    while (current != NULL) {
        visited[current->getInfo()] = false;
        current = current->getNext();
    }

    if (visited.find(initialNode) == visited.end()) {
        std::cout << "bfs (const T &initialNode): No se encuetra el nodo inicial en el grafo" << std::endl; 
        return false;
    }

    if (initialNode == finalNode) {
        return true;
    }

    currentNode.push(initialNode);
    visited[initialNode] = true;
    
    while (!currentNode.empty()) {
        T v = currentNode.front();
        currentNode.pop();

        std::list<T> neighbors = getNeighbors(v);
        while (!neighbors.empty()) {

            T w = neighbors.front();
            // si se está en una excepción, entonces eliminamos el vecino.
            std::pair<T,T> edge;
            if (v < w) {
                edge = {v, w};
            } else {
                edge = {w, v};
            }
            //std:: cout << v << " . " << w << "exc:" << isException << std::endl;
            
            bool isException = exceptions.find(edge) != exceptions.end();

            if (!isException) {
                if (w == finalNode) 
                {
                    return true;
                }
                if (!visited[w]) {
                    currentNode.push(w);
                    visited[w] = true;
                }
            }
            neighbors.pop_front();
        }
    }
    
    return false;
}

/* 
****************************
Constructors and destructors
****************************
*/

// OK
template<class T>
GraphUndirected<T>::GraphUndirected() : firstNode(NULL), nodeCount(0), edgeCount(0) {}

// OK
template<class T>
GraphUndirected<T>::GraphUndirected(GraphUndirected<T> &other) : firstNode(NULL), nodeCount(0), edgeCount(0) {
    copy(other);
}

//~OK
template<class T>
GraphUndirected<T>::GraphUndirected(const std::unordered_map<T, std::list<std::pair<T, float > > >& mapa) : firstNode(NULL), nodeCount(0), edgeCount(0) {
    // Crear todos los nodos y mapear.
    std::unordered_map<T, NodeVertex<T> *> nodes;
    for (typename std::unordered_map<T, std::list<std::pair<T, float > > >::const_iterator it = mapa.begin(); it != mapa.end(); it++) {
        nodes[it->first] = createAndReturnNode(it->first);
    }
    
    // Crear links.
    for (typename std::unordered_map<T, std::list<std::pair<T, float > > >::const_iterator it = mapa.begin(); it != mapa.end(); it++) {
        NodeVertex<T> *v = nodes[it->first];

        for (typename std::list<std::pair<T, float> >::const_iterator itl = it->second.begin(); itl != it->second.end(); itl++) {
            T nodeName = itl->first;
            float weight = itl->second;
            NodeVertex<T>* w;
            if (nodes.find(nodeName) == nodes.end())
            {
                nodes[nodeName] = createAndReturnNode(nodeName);
                //std::cout << "Constructor: Nodo destino no encontrado: " << nodeName << std::endl;
            }
            w = nodes[nodeName];
            addEdge(v, w, weight);
        }
    }

}

// OK
template<class T>
GraphUndirected<T>::~GraphUndirected(){
    clear();
}

// OK
template<class T>
void GraphUndirected<T>::clear(){
    NodeVertex<T> *currentVertex = firstNode;
    
    while (currentVertex != NULL) {
        NodeEdge<T> *currentEdge = currentVertex->getListAdj();
        NodeVertex<T> *trashVertex = currentVertex;
        
        while (currentEdge != NULL) {
            NodeEdge<T> *trashEdge = currentEdge;
            currentEdge = currentEdge->getNext();
            delete trashEdge;
        }
        
        currentVertex = currentVertex->getNext();
        delete trashVertex;
    }
    firstNode = NULL;
    nodeCount = 0;
    edgeCount = 0;
}


/* 
*********
Node ops.
*********
*/

// ~OK
template<class T>
void GraphUndirected<T>::removeNode(const T &v){
    NodeVertex<T> *currentVertex = firstNode;
    NodeVertex<T> *previousVertex = NULL;
    
    while (currentVertex != NULL && currentVertex->getInfo() != v) {
        previousVertex = currentVertex;
        currentVertex = currentVertex->getNext();
    }

    if (currentVertex == NULL) {
        //throw std::out_of_range("removeNode(const T &v): Vertice no encontrado");
        std::cout << "removeNode(const T &v): Vertice no encontrado" << std::endl;
        return;
    }
    
    // eliminar enlaces entrantes y salientes  
    NodeEdge<T> *currentEdge = currentVertex->getListAdj();
    while(currentEdge != NULL) {
        NodeEdge<T> *nextEdge = currentEdge->getNext();
        //eliminar desde el vecino al currentVertex.
        if (currentEdge->getInfo() != NULL && currentEdge->getInfo() != currentVertex) {
            removeConnection(currentEdge->getInfo(), currentVertex);
        }
        
        // borrar desde el currentVertex al vecino.
        delete currentEdge;
        currentEdge = nextEdge;
        edgeCount --;
    }
    
    // eliminar el vertice
    if (previousVertex == NULL) {
        firstNode = currentVertex->getNext();
    }
    else {
        previousVertex->setNext(currentVertex->getNext());
    }

    delete currentVertex;
    nodeCount --;
}

// ~OK
template<class T>
void GraphUndirected<T>::addNode(const T &v, std::list<std::pair<T, float> > &links){
    if (this->findNode(v) != NULL) {
        //throw std::invalid_argument("addNode(const T &v, std::list<std::pair<T, float> > &links): Este nodo ya fue añadido.");
        std::cout << "addNode(const T &v, std::list<std::pair<T, float> > &links): Este nodo ya fue añadido." << std::endl;
        return;
    }

    // crear e insertar el nuevo nodo
    NodeVertex<T> *newNode = new NodeVertex<T>(v);
    newNode->setNext(firstNode);
    firstNode = newNode;
    
    // formar enlaces:
    for (typename std::list<std::pair<T, float> >::iterator it = links.begin(); it != links.end(); it++) {
        T nodeInfo = it->first;
        float weight = it->second;
        
        NodeVertex<T>* node = findNode(nodeInfo);
        if (node != NULL) {
            createConnection(newNode, node, weight);
            createConnection(node, newNode, weight);
            edgeCount++;
        }
        else {
            //throw std::out_of_range("addNode(const T &v, std::list<std::pair<T, float> > &links): Intentó hacer un link a un nodo inexistente");
            std::cout << "addNode(const T &v, std::list<std::pair<T, float> > &links): Intentó hacer un link a un nodo inexistente" << std::endl;
            continue;
        }
    }
    
    nodeCount++;
}

// OK
template<class T>
void GraphUndirected<T>::addNode(const T &v){
    if (this->findNode(v) != NULL) {
        //throw std::invalid_argument("addNode(const T &v): Este nodo ya fue añadido.");
        std::cout << "addNode(const T &v): Este nodo ya fue añadido." << std::endl;
        return;
    }

    NodeVertex<T> *newNode = new NodeVertex<T>(v);

    newNode->setNext(firstNode);
    firstNode = newNode;
    nodeCount++;
}


/* 
*********
Edge ops.
*********
*/

// OK
template<class T>
void GraphUndirected<T>::removeEdge(const T &v, const T &w){
    NodeVertex<T> *ptrV = NULL, *ptrW = NULL;
    NodeVertex<T> *currentVertex = firstNode;
    
    while (currentVertex != NULL && !(ptrV != NULL && ptrW != NULL)) {
        // 2 if separados, añadimos soporte a grafos ciclicos
        if (currentVertex->getInfo() == v) {
            ptrV = currentVertex;
        }
        if (currentVertex->getInfo() == w) {
            ptrW = currentVertex;
        }
        currentVertex = currentVertex->getNext();
    }
    
    if (ptrV == NULL || ptrW == NULL) {
        //throw std::out_of_range("removeEdge(const T &v, const T &w): No se ha encontrado alguno de los vetices");
        std::cout << "removeEdge(const T &v, const T &w): No se ha encontrado alguno de los vetices" << std::endl;
        return;
    }
    
    if (ptrW == ptrV) {
        removeConnection(ptrV, ptrW);
    }
    else {
        removeConnection(ptrW, ptrV);
        removeConnection(ptrV, ptrW);
    }
    // ya habiendo encontrado los 2 vertices se debe buscar y eliminar el enlace.
    
    edgeCount--;
}

// OK
template<class T>
void GraphUndirected<T>::addEdge(const T &v, const T& w, float weight){
    NodeVertex<T> *ptrV = NULL, *ptrW = NULL;
    NodeVertex<T> *currentVertex = firstNode;
    
    while (currentVertex != NULL && !(ptrV != NULL && ptrW != NULL)) {
        // 2 if separados, añadimos soporte a grafos ciclicos nahshe
        if (currentVertex->getInfo() == v) {
            ptrV = currentVertex;
        }
        if (currentVertex->getInfo() == w) {
            ptrW = currentVertex;
        }
        currentVertex = currentVertex->getNext();
    }
    
    if (ptrV == NULL || ptrW == NULL) {
        //throw std::out_of_range("addEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los vetices");
        std::cout << "addEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los vetices" << std::endl;
        return;
    }

    // Check for existing edge
    NodeEdge<T> *current = ptrV->getListAdj();
    while (current != NULL) {
        if (current->getInfo() == ptrW) {
            //throw std::out_of_range("addEdge(const T &v, const T& w, const float weight): Esta conexion ya existe");
            return;
        }
        current = current->getNext();
    }
    
        
    if (ptrV == ptrW) {
        createConnection(ptrV, ptrW, weight); 
    } else {
        createConnection(ptrV, ptrW, weight); // v -> w
        createConnection(ptrW, ptrV, weight); // w -> v
    }
    
    edgeCount++;
}

// ~OK
template<class T>
void GraphUndirected<T>::setWeightOfEdge(const T &v, const T& w, float weight){
    NodeVertex<T> *ptrV = NULL, *ptrW = NULL;
    NodeVertex<T> *currentVertex = firstNode;
    
    while (currentVertex != NULL && !(ptrV != NULL && ptrW != NULL)) {
        // 2 if separados, añadimos soporte a grafos ciclicos nahshe
        if (currentVertex->getInfo() == v) {
            ptrV = currentVertex;
        }
        if (currentVertex->getInfo() == w) {
            ptrW = currentVertex;
        }
        currentVertex = currentVertex->getNext();
    }
    
    if (ptrV == NULL || ptrW == NULL) {
        //throw std::out_of_range("setWeightOfEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los vetices");
        std::cout << "setWeightOfEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los vetices" << std::endl;
        return;
    }
    
    // ahora buscamos el arco y actualizamos
    if (ptrV != ptrW) {
        // v -> w
        NodeEdge<T> *edgeVW = ptrV->getListAdj();
        while (edgeVW != NULL) {
            if (edgeVW->getInfo() == ptrW) {
                // encontrado el enlace v -> w 
                break;
            }
            edgeVW = edgeVW->getNext();
        }
        
        // w -> v
        NodeEdge<T> *edgeWV = ptrW->getListAdj();
        while (edgeWV != NULL) {
            if (edgeWV->getInfo() == ptrV) {
                // encontrado el enlace w -> v 
                break;
            }
            edgeWV = edgeWV->getNext();
        }
        
        if (edgeVW == NULL || edgeWV == NULL) {
            //throw std::out_of_range("setWeightOfEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los edges");
            std::cout << "setWeightOfEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los edges" << std::endl;
            return;
        }
        edgeWV->setWeight(weight);
        edgeVW->setWeight(weight);
    }
    else {
        NodeEdge<T> *edgeVW = ptrV->getListAdj();
        while (edgeVW != NULL) {
            if (edgeVW->getInfo() == ptrW) {
                // encontrado el enlace v -> w 
                break;
            }
            edgeVW = edgeVW->getNext();
        }

        if (edgeVW == NULL) {
            //throw std::out_of_range("setWeightOfEdge(const T &v, const T& w, const float weight): No se ha encontrado el edge");
            std::cout << "setWeightOfEdge(const T &v, const T& w, const float weight): No se ha encontrado el edge" << std::endl;
            return;
        }

        edgeVW->setWeight(weight);
    }
    
}


/* 
*******
Getters
*******
*/

// OK
template<class T>
int GraphUndirected<T>::getNodeCount() const{
    return nodeCount;
}

// OK
template<class T>
int GraphUndirected<T>::getEdgeCount() const{
    return edgeCount;
}

// OK
template<class T>
std::list<T> GraphUndirected<T>::getNeighbors(const T &v) const {
    std::list<T> result;
    
    NodeVertex<T> *currentVertex = findNode(v);
    
    // si current es null entonces no lo encontró
    if (currentVertex == NULL) {
        //throw std::out_of_range("getNeighbors(const T &v): Vertice no encontrado");
        std::cout << "getNeighbors(const T &v): Vertice no encontrado" << std::endl;
        return result;
    }
    
    NodeEdge<T> *currentEdge = currentVertex->getListAdj();

    while(currentEdge != NULL) {
        result.push_back(currentEdge->getInfo()->getInfo());
        currentEdge = currentEdge->getNext();
    }
    
    return result;
    
} // outcoming + incoming

// OK
template<class T>
T &GraphUndirected<T>::getFirstNode() const{
    if (nodeCount == 0 || firstNode == NULL) {
        throw std::runtime_error("getFirstNode(): Grafo vacio.");
        //std::cout << "getFirstNode(): Grafo vacio.";
    }
    return firstNode->getInfo();
}

// OK
template<class T>
float GraphUndirected<T>::getWeightOfEdge(const T &v, const T& w){
    NodeVertex<T> *ptrV = NULL, *ptrW = NULL;
    NodeVertex<T> *currentVertex = firstNode;
    
    while (currentVertex != NULL && !(ptrV != NULL && ptrW != NULL)) {
        // 2 if separados, añadimos soporte a grafos ciclicos nahshe
        if (currentVertex->getInfo() == v) {
            ptrV = currentVertex;
        }
        if (currentVertex->getInfo() == w) {
            ptrW = currentVertex;
        }
        currentVertex = currentVertex->getNext();
    }
    
    if (ptrV == NULL || ptrW == NULL) {
        //throw std::out_of_range("getWeightOfEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los vetices");
        std::cout << "getWeightOfEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los vetices" << std::endl;
    }
    
    // ahora buscamos el arco y actualizamos
    
    // v -> w
    NodeEdge<T> *edgeVW = ptrV->getListAdj();
    while (edgeVW != NULL) {
        if (edgeVW->getInfo() == ptrW) {
            // encontrado el enlace v -> w 
            break;
        }
        edgeVW = edgeVW->getNext();
    }
    
    // con encontrar el v -> w ya está bien

    /* // w -> v
    NodeEdge<T> *edgeWV = ptrW->getListAdj();
    while (edgeW != NULL) {
        if (edgeWV->getInfo() == ptrV) {
            // encontrado el enlace w -> v 
            break;
        }
        edgeW = edgeWV->getNext();
    } */
    
    if (edgeVW == NULL) {
        //throw std::out_of_range("getWeightOfEdge(const T &v, const T& w): No se ha encontrado el edge v -> w");
        std::cout << "getWeightOfEdge(const T &v, const T& w): No se ha encontrado el edge v -> w" << std::endl;
    }
    
    return edgeVW->getWeight();
}

/* 
*******
Utility
*******
*/

// OK
template<class T>
bool GraphUndirected<T>::isEmpty() const{
    return nodeCount == 0;
}

// OK
template<class T>
bool GraphUndirected<T>::isTree() {
    // Grafo Vacio
    if (nodeCount == 0) {
        return false;
    }

    // Un grafo con N nodos debe tener exactamente N-1 aristas para ser un arbol
    if (edgeCount != nodeCount - 1) {
        return false;
    }

    // El grafo debe ser totalmente conexo. Usaremos BFS
    
    std::list<T> result = bfs(getFirstNode());

    // Si el nro de nodos visitados es igual al nro total de nodos, es conexo
    if ((int)result.size() == nodeCount) {
        return true; // Cumple M=N-1 y es conexo.
    } else {
        return false; // Cumple M=N-1, pero es disconexo (por ejemplo, N=4, M=3, pero dos componentes).
    }
    return false; 
}

// simple version
template<class T>
std::list<T> GraphUndirected<T>::bfs (const T &initialNode) const{
    std::queue<T> currentNode;
    std::unordered_map<T, bool> visited;

    // llenar el mapa y validar que el nodo inicial se encuentra
    NodeVertex<T> *current = firstNode;

    while (current != NULL) {
        visited[current->getInfo()] = false;
        current = current->getNext();
    }

    std::list<T> result;

    if (visited.find(initialNode) == visited.end()) {
        std::cout << "bfs (const T &initialNode): No se encuetra el nodo inicial en el grafo" << std::endl; 
        return result;
    }

    std::list<T> neighbors;
    T v, w;

    if (nodeCount >= 1) {
        currentNode.push(initialNode);
        visited[initialNode] = true;

        while (!currentNode.empty()) {
            v = currentNode.front();
            neighbors = getNeighbors(v);
            while (!neighbors.empty()) {
                w = neighbors.front();
                if (!visited[w]) {
                    currentNode.push(w);
                    visited[w] = true;
                }
                neighbors.pop_front();
            }
            result.push_back(v);
            currentNode.pop();
        }
    }
    return result;
}


// simple version
template<class T>
std::list<T> GraphUndirected<T>::dfs(const T &initialNode) const {
    std::list<T> result;
    std::unordered_map<T, bool> visited;

    // llenar el mapa y validar que el nodo inicial se encuentra
    NodeVertex<T> *current = firstNode;
    while (current != NULL) {
        visited[current->getInfo()] = false;
        current = current->getNext();
    }

    if (visited.find(initialNode) != visited.end()) {

        dfs(initialNode, visited, result);
    }
    return result;
}

template<class T>
void GraphUndirected<T>::dfs(const T &initialNode, std::unordered_map<T, bool> &visited, std::list<T> &result) const {
    T w;
    std::list<T> neighbors;
    neighbors = getNeighbors(initialNode);
    visited[initialNode] = true;
    result.push_back(initialNode);
    while (!neighbors.empty()) {
        w = neighbors.front();
        if (!visited[w]) {
            dfs(w, visited, result);
        }
        neighbors.pop_front();
    }
}

// OK
template <class T>
void GraphUndirected<T>::show() const {
    NodeVertex<T> *currentVertex = firstNode;
    
    while (currentVertex != NULL) {
        NodeEdge<T> *currentEdge = currentVertex->getListAdj();
        std::cout << "vertex:" << currentVertex->getInfo() << "\t";
        std::cout << "edges (v,w,p): { ";
        while (currentEdge != NULL) {
            std::cout   << "(" << currentVertex->getInfo() << ", "
                        << currentEdge->getInfo()->getInfo() << ", "
                        << currentEdge->getWeight() << ") " << "\t";

            currentEdge = currentEdge->getNext();
        }
        std::cout << "}\n";
        currentVertex = currentVertex->getNext();
    }
}

template<class T>
std::list<NodeVertex<T>* > GraphUndirected<T>::getNeighbors(NodeVertex<T> *v) {
    std::list<NodeVertex<T>* > result;
    
    NodeVertex<T> *currentVertex = v;
    
    // si current es null entonces no lo encontró
    if (currentVertex == NULL) {
        //throw std::out_of_range("getNeighbors(const T &v): Vertice no encontrado");
        std::cout << "getNeighbors(NodeVertex<T> *v): Vertice no encontrado" << std::endl;
        return result;
    }
    
    NodeEdge<T> *currentEdge = currentVertex->getListAdj();

    while(currentEdge != NULL) {
        result.push_back(currentEdge->getInfo());
        currentEdge = currentEdge->getNext();
    }
    
    return result;
}

template<class T>
std::list<T> GraphUndirected<T>::bfs2 (const T &initialNode) {
    std::queue<NodeVertex<T>*> currentNode;
    std::unordered_map<NodeVertex<T>*, bool> visited;

    // llenar el mapa y validar que el nodo inicial se encuentra
    NodeVertex<T> *current = firstNode;

    while (current != NULL) {
        visited[current] = false;
        current = current->getNext();
    }

    std::list<T> result;
    
    current = findNode(initialNode);

    if (nodeCount == 0 || current == NULL) {
        std::cout << "bfs2 (const T &initialNode): No se encuetra el nodo inicial en el grafo" << std::endl; 
        return result;
    }

    std::list<NodeVertex<T>* > neighbors;
    NodeVertex<T> * w;

    currentNode.push(current);
    visited[current] = true;

    while (!currentNode.empty()) {
        neighbors = getNeighbors(currentNode.front());
        while (!neighbors.empty()) {
            w = neighbors.front();
            if (!visited[w]) {
                currentNode.push(w);
                visited[w] = true;
            }
            neighbors.pop_front();
        }
        result.push_back(currentNode.front()->getInfo());
        currentNode.pop();
    }
    return result;
}

// OK
template<class T>
std::list<std::pair<T,T> > GraphUndirected<T>::getBridges() {
    std::list<std::pair<T,T> > result;
    std::unordered_map<NodeVertex<T>*, NodeVertex<T>* > probados;
    std::set<std::pair<T, T> > testedEdges; 
    // recorrer el grafo
    NodeVertex<T> *currentV = firstNode;
    while (currentV != NULL) {

        NodeEdge<T> *currentEdgeVW = currentV->getListAdj();

        // solo tiene una conexion
        while (currentEdgeVW != NULL) {
            NodeVertex<T> *currentW = currentEdgeVW->getInfo();
            //std::cout << " v " << currentV->getInfo() << " w " << currentW->getInfo() << " " << std::endl; /* << " " <<  << " " << <<  */
            
            T vInfo = currentV->getInfo();
            T wInfo = currentW->getInfo();

            // Create a pair for the edge
            std::pair<T, T> edgePair;
            if (vInfo < wInfo) {
                edgePair = {vInfo, wInfo};
            } else {
                edgePair = {wInfo, vInfo};
            }
            
            if (testedEdges.find(edgePair) == testedEdges.end()) {
                
                testedEdges.insert(edgePair);

                std::set<std::pair<T, T> > exceptions;
                exceptions.insert(edgePair);

                if (!existPathBetween(vInfo, wInfo, exceptions)) {
                    result.push_back(edgePair);
                }

            }
            currentEdgeVW = currentEdgeVW->getNext();
        }
        currentV = currentV->getNext();
    }
    return result;
}

template<class T>
std::list<T> GraphUndirected<T>::findPathBetween(const T &v, const T &w) {
    return findPathBetween(v, w, std::list<std::pair<NodeVertex<T>*,NodeVertex<T>*> >());
}


/* 
*********
Operators
*********
*/


// OK
template<class T>
void GraphUndirected<T>::operator = (GraphUndirected &g) {
    if (this != &g) {
        clear();
        copy(g);
    }
}

#endif