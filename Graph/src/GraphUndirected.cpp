#pragma once
#include "GraphUndirected.h"
#include "NodeVertex.h"
#include "NodeEdge.h"
#include <stdexcept>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>

/* private:
    NodeVertex<T> *firstNode
    int nodeCount, edgeCount */


template<class T>
GraphUndirected<T>::GraphUndirected() : firstNode(NULL), nodeCount(0), edgeCount(0) {}

template<class T>
GraphUndirected<T>::GraphUndirected(GraphUndirected<T> &other) {
    copy(other);
}

template<class T>
GraphUndirected<T>::~GraphUndirected(){
    clear();
}

template<class T>
void GraphUndirected<T>::copy(const GraphUndirected<int> &other) {
    if (this == &other) {
        throw std::out_of_range("copy(const GraphUndirected<int> &other): No puede copiar otro grafo a si mismo");
    }
    std::unordered_map<T, NodeVertex<T> *> ownNodes;
    NodeVertex<T> *otherCurrentVertex = other.firstNode;
    NodeVertex<T> *ownCurrentVertex = NULL;

    if (otherCurrentVertex != NULL) {
        ownCurrentVertex = new NodeVertex(otherCurrentVertex->getInfo());
        firstNode = ownCurrentVertex;
        // meterlo en el ownNodes
        ownNodes[otherCurrentVertex->getInfo()] = ownCurrentVertex;
        otherCurrentVertex = otherCurrentVertex->getNext();
    }
    
    // vamos recorriendo los vertices hasta llegar al que queremos y vamos a irlos guardando en un mapa
    while (otherCurrentVertex != NULL) {
        NodeVertex<T> *newNode = new NodeVertex(otherCurrentVertex->getInfo());
        ownCurrentVertex->setNext(newNode);
        ownCurrentVertex = ownCurrentVertex->getNext();

        ownNodes[otherCurrentVertex->getInfo()] = ownCurrentVertex;
        
        otherCurrentVertex = otherCurrentVertex->getNext();
    }

    // tenemos los vertices del nuevo grafo mapeados, ahora hay que hacer los enlaces.

    // reutilizamos other y own currentVertex
    otherCurrentVertex = other.firstNode;
    ownCurrentVertex = firstNode;
    // se recorren todos los nodos
    while (otherCurrentVertex != NULL) {
        // el apuntador de la lista de adyacencia
        NodeEdge<T> *otherCurrentEdge = otherCurrentVertex->getListAdj();
        NodeVertex<T> *ownCurrentEdge = NULL;

        if (otherCurrentEdge != NULL) {

            NodeEdge<T> *newEdge = new NodeEdge(otherCurrentEdge->getWeight());
            newEdge->setInfo(ownNodes[otherCurrentEdge->getInfo()->getInfo()]);
            // encontramos el nodo actual en el mapa y lo seteamos como el adyacencia
            ownCurrentVertex->setListAdj(newEdge);
            ownCurrentEdge = newEdge;
            // el nuevo edge actual va a ser la lista de adyacencia
            ownCurrentEdge = newEdge;
            otherCurrentEdge = otherCurrentEdge->getNext();
        }

        while (otherCurrentEdge != NULL) {
            NodeEdge<T> *newEdge = new NodeEdge(otherCurrentEdge->getWeight());
            newEdge->setInfo(ownNodes[otherCurrentEdge->getInfo()->getInfo()]);

            ownCurrentEdge->setNext(newEdge);
            ownCurrentEdge = ownCurrentEdge->getNext();
            
            otherCurrentEdge = otherCurrentEdge->getNext();
        }
    }

    nodeCount = other.nodeCount;
    edgeCount = other.edgeCount;
}

template<class T>
T &GraphUndirected<T>::getFirstNode() const{
    if (nodeCount == 0) {
        throw std::out_of_range("getFirstNode: Grafo vacio");
    }
    return firstNode->getInfo();
}

template<class T>
void GraphUndirected<T>::clear(){
    NodeVertex<T> *currentVertex = firstNode;
    while (currentVertex != NULL) {
        NodeEdge<T> *currentEdge = currentVertex->getListAdj();
        NodeVertex<T> *trashVertex = currentEdge;
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

template<class T>
int GraphUndirected<T>::getNodeCount() const{
    return nodeCount;
}

template<class T>
int GraphUndirected<T>::getEdgeCount() const{
    return edgeCount;
}

template<class T>
void GraphUndirected<T>::removeNode(const T &v){
    std::unordered_map<T, NodeVertex<T> *> recorridos;
    NodeVertex<T> *currentVertex = firstNode;
    NodeVertex<T> *previousVertex = NULL;
    
    // vamos recorriendo los vertices hasta llegar al que queremos y vamos a irlos guardando en un mapa
    while (currentVertex != NULL) {
        recorridos[currentVertex->getInfo()] = currentVertex;
        if (currentVertex->getInfo() == v){
            break;
        }
        previousVertex = currentVertex;
        currentVertex = currentVertex->getNext();
    }

    // si current es null entonces no lo encontró
    if (currentVertex == NULL) {
        throw std::out_of_range("removeNode(const T &v): Vertice no encontrado");
    }

    NodeEdge<T> *currentEdge = currentVertex->getListAdj();
    // se van eliminando los enlaces
    while(currentEdge != NULL) {
        //eliminar el enlace desde el vecino actual al vertice actual.
        removeConnection(currentEdge->getInfo(), currentVertex);

        // borrar el enlace desde el vertice actual al vecino actual.
        NodeEdge<T> *trashEdge = currentEdge;
        currentEdge = currentEdge->getNext();
        delete trashEdge;
        edgeCount -= 1;
    }
    
    NodeEdge<T> *trashVertex = currentVertex;
    // si es el primer vertice
    if (previousVertex == NULL) {
        firstNode = currentVertex->next();
    }
    else {
        previousVertex = currentVertex->next();
    }

    nodeCount -= 1;
}

// eliminar la conexion que va de v a w, (solo IDA y NO DECREMENTA edgeCount). 
template<class T>
void GraphUndirected<T>::removeConnection(NodeVertex<T> *v, NodeVertex<T> *w){
    NodeEdge<T> *currentEdge = v->getListAdj();
    NodeEdge<T> *previousEdge = NULL;
    
    // vamos recorriendo los vertices hasta llegar al que queremos y vamos a irlos guardando en un mapa
    while (currentEdge != NULL) {
        if (currentEdge->getInfo() == w){
            break;
        }
        previousEdge = currentEdge;
        currentEdge = currentEdge->getNext();
    }

    // si current es null entonces no lo encontró
    if (currentEdge == NULL) {
        throw std::out_of_range("removeEdge(NodeVertex<T> *v, NodeVertex<T> *w): Arco no encontrado");
    }

    // cuando es el primer elmento
    NodeEdge<T> *trashEdge = currentEdge;
    if(previousEdge == NULL) {
        v->setListAdj(currentEdge->getNext());
    }
    else {
        previousEdge->setNext(currentEdge->getNext());
    }
    delete trashEdge;
}

template<class T>
void GraphUndirected<T>::addNode(const T &v, std::list<std::pair<T, float> > &links){
    std::unordered_map<T, NodeVertex<T> *> nodes;
    NodeVertex<T> *currentVertex = firstNode;

    while (currentVertex != NULL) {
        nodes[currentVertex->getInfo()] = currentVertex;
        currentVertex = currentVertex->getNext();
    }

    // ya habiendo guardado todos los nodos del grafo, se debe agregar el nuevo

    // si prev es null entonces es el primer nodo y el arbol está vacio
    NodeVertex<T> *newNode = new NodeVertex<T>(v);
    newNode->setNext(firstNode);
    firstNode = newNode;

    for (typename std::list<T>::reverse_iterator it = links.rbegin(); it != links.rend(); it++) {
        
        if (nodes.find(*it.first) != nodes.end()) {
            createConnection(newNode, nodes[*it.first]);
            edgeCount++;
        }
        else {
            throw std::out_of_range("addNode(const T &v, std::list<std::pair<T, float> > &links): Intentó hacer un link a un nodo inexistente");
        }
    }

    nodeCount++;

}

template<class T>
void GraphUndirected<T>::createConnection(NodeVertex<T> *v, NodeVertex<T> *w, float weight) {
    NodeEdge<T> *newEdgeV = new NodeEdge<T>(weight);
    newEdgeV->setInfo(w);
    newEdgeV->setNext(v->getListAdj());
    v->setListAdj(newEdgeV);


    NodeEdge<T> *newEdgeW = new NodeEdge<T>(weight);
    newEdgeW->setInfo(v);
    newEdgeW->setNext(w->getListAdj());
    w->setListAdj(newEdgeW);
}

template<class T>
void GraphUndirected<T>::addNode(const T &v){
    NodeVertex<T> *newNode = new NodeVertex<T>(v);
    newNode->setNext(firstNode);
    firstNode = newNode;
    nodeCount++;
}

template<class T>
void GraphUndirected<T>::removeEdge(const T &v, const T &w){
    bool findedV = false, findedW = false;
    NodeVertex<T> *ptrV = NULL, *ptrW = NULL;
    NodeVertex<T> *currentVertex = firstNode;

    while (currentVertex != NULL && !(findedV && findedW)) {
        // 2 if separados, añadimos soporte a grafos ciclicos nahshe
        if (currentVertex->getInfo() == v) {
            ptrV = currentVertex;
            findedV = true;
        }
        if (currentVertex->getInfo() == w) {
            ptrW = currentVertex;
            findedW = true;
        }
        currentVertex = currentVertex->getNext();
    }

    if (!findedV || !findedW) {
        throw std::out_of_range("removeEdge(const T &v, const T &w): No se ha encontrado alguno de los vetices");
    }

    // ya habiendo encontrado los 2 vertices se debe buscar y eliminar el enlace.
    removeConnection(ptrV, ptrW);
    removeConnection(ptrW, ptrV);

    edgeCount--;
}

template<class T>
void GraphUndirected<T>::addEdge(const T &v, const T& w, const float weight){
    bool findedV = false, findedW = false;
    NodeVertex<T> *ptrV =NULL, *ptrW = NULL;
    NodeVertex<T> *currentVertex = firstNode;

    while (currentVertex != NULL && !(findedV && findedW)) {
        // 2 if separados, añadimos soporte a grafos ciclicos nahshe
        if (currentVertex->getInfo() == v) {
            ptrV = currentVertex;
            findedV = true;
        }
        if (currentVertex->getInfo() == w) {
            ptrW = currentVertex;
            findedW = true;
        }
        currentVertex = currentVertex->getNext();
    }

    if (!findedV || !findedW) {
        throw std::out_of_range("addEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los vetices");
    }

    createConnection(ptrV, ptrW, weight);

    nodeCount++;
}

template<class T>
void GraphUndirected<T>::setWeightOfEdge(const T &v, const T& w, const float weight){
    bool findedV = false, findedW = false;
    NodeVertex<T> *ptrV = NULL, *ptrW = NULL;
    NodeVertex<T> *currentVertex = firstNode;

    while (currentVertex != NULL && !(findedV && findedW)) {
        // 2 if separados, añadimos soporte a grafos ciclicos nahshe
        if (currentVertex->getInfo() == v) {
            ptrV = currentVertex;
            findedV = true;
        }
        if (currentVertex->getInfo() == w) {
            ptrW = currentVertex;
            findedW = true;
        }
        currentVertex = currentVertex->getNext();
    }

    if (!findedV || !findedW) {
        throw std::out_of_range("setWeightOfEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los vetices");
    }

    NodeEdge<T> *edgeV = ptrV->getListAdj(), *edgeW = ptrW->getListAdj();
    // ahora buscamos el arco en cada uno que se conecta con el otro
    while (edgeV != NULL) {
        if (edgeV->getInfo() == ptrW) {
            // encontrado el enlace v -> w 
            break;
        }
        edgeV = edgeV->getNext();
    }

    while (edgeW != NULL) {
        if (edgeW->getInfo() == ptrV) {
            // encontrado el enlace w -> v 
            break;
        }
        edgeW = edgeW->getNext();
    }

    if (edgeV == NULL || edgeW == NULL) {
        throw std::out_of_range("setWeightOfEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los edges");
    }

    edgeV->setWeight(weight);
    edgeW->setWeight(weight);
}

template<class T>
std::list<T> GraphUndirected<T>::getNeighbors(const T &v) const {
    std::list<T> result;

    NodeVertex<T> *currentVertex = firstNode;
    
    // vamos recorriendo los vertices hasta llegar al que queremos y vamos a irlos guardando en un mapa
    while (currentVertex != NULL) {
        if (currentVertex->getInfo() == v){
            break;
        }
        currentVertex = currentVertex->getNext();
    }

    // si current es null entonces no lo encontró
    if (currentVertex == NULL) {
        throw std::out_of_range("getNeighbors(const T &v): Vertice no encontrado");
    }

    NodeEdge<T> *currentEdge = currentVertex->getListAdj();
    // se van eliminando los enlaces
    while(currentEdge != NULL) {
        //eliminar el enlace desde el vecino actual al vertice actual.
        result.push_back(currentEdge->getInfo()->getInfo());
    }

    return result;

} // outcoming + incoming

template<class T>
bool GraphUndirected<T>::isEmpty() const{
    return edgeCount == 0 && nodeCount == 0;
}

template<class T>
bool GraphUndirected<T>::isTree() const {
    return false;
}

// simple version for mapped int graph [1-N]
template<class T>
std::list<int> GraphUndirected<T>::bfs (const GraphUndirected<int>& g, const int &initialNode){
    std::queue<int> currentNode;
    std::vector<bool> visited(g.nodeCount, false);   
    std::list<int> result;
    std::list<int> neighbors;
    int v, w;
    if (g.nodeCount >= 1) {
        currentNode.push(initialNode);
        visited[initialNode - 1] = true;
        while (!currentNode.empty()) {
            v = currentNode.front();
            neighbors = g.getNeighbors(v);
            while (!neighbors.empty()) {
                w = neighbors.front();
                if (!visited[w - 1]) {
                    currentNode.push(w);
                    visited[w - 1] = true;
                }
                neighbors.pop_front();
            }
            result.push_back(v);
            currentNode.pop();
        }
    }
    return result;
}


// simple version for mapped int graph [1-N]
template<class T>
std::list<int> GraphUndirected<T>::dfs(const GraphUndirected<int> &g, const int &initialNode){
    std::list<int> result;
    if (g.edgeCount >= 1) {
        std::vector<bool> visited(g.nodeCount, false);
        dfs(g, initialNode, visited, result);
    }
    return result;
}

template<class T>
void GraphUndirected<T>::dfs(const GraphUndirected<int> &g, const int &initialNode, std::vector<bool> visited, std::list<int> &result) const {
    int w;
    std::list<int> neighbors;
    neighbors = g.getNeighbors(initialNode);
    visited[initialNode - 1] = true;
    result.push_back(w);
    while (!neighbors.empty()) {
        w = neighbors.front();
        if (!visited[w]) {
            dfs(g, w, visited, result);
        }
        neighbors.pop_front();
    }
}









template<class T>
void GraphUndirected<T>::operator = (GraphUndirected &g) {
    clear();
    copy(g);
}



