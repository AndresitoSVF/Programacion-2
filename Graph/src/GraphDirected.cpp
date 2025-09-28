#ifndef GRAPH_D_CPP
#define GRAPH_D_CPP
#include "GraphDirected.h"
#include "NodeVertex.h"
#include "NodeEdge.h"
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <iostream>

    /* 
    ********
    Helpers
    ********
    */

    
// OK
// elimina la conexion v -> w
template<class T>
bool GraphDirected<T>::removeConnection(NodeVertex<T> *v, NodeVertex<T> *w){
    NodeEdge<T> *current = v->getListAdj();
    NodeEdge<T> *previous = NULL;

    while (current != NULL && current->getInfo() != w) {
        previous = current;
        current = current->getNext();
    }

    if (current == NULL) {
        // No se encontro la conexion.
        return false;
    }

    if (previous == NULL) {
        // es el primero en la lista.
        v->setListAdj(current->getNext());
    } else {
        previous->setNext(current->getNext());
    }

    delete current;
    return true;
}

// OK
// hace la conexion v -> w.
template<class T>
void GraphDirected<T>::createConnection(NodeVertex<T> *v, NodeVertex<T> *w, float weight){
    if (v == NULL || w == NULL) { 
        std::cout << "createConnection: Vertice nulo" << std::endl;
        return;
    }

    NodeEdge<T> *newEdgeV = new NodeEdge<T>(weight);
    newEdgeV->setInfo(w);
    newEdgeV->setNext(v->getListAdj());
    v->setListAdj(newEdgeV);
} 

template<class T>
void GraphDirected<T>::dfs(const T &initialNode, std::unordered_map<T, bool> &visited, std::list<T> &result) const{
    T w;
    std::list<T> neighbors;

    neighbors = getSuccessors(initialNode);
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

template<class T>
void GraphDirected<T>::copy(const GraphDirected<T> &other){
    if (this == &other) {
        return;
    }

    // primero se crean todos los nodos y se guardan en el mapa.

    std::unordered_map<T, NodeVertex<T> *> ownNodes;
    NodeVertex<T> *otherCurrent = other.firstNode;

    while (otherCurrent != NULL) {
        if (ownNodes.find(otherCurrent->getInfo()) == ownNodes.end()) {
            ownNodes[otherCurrent->getInfo()] = createAndReturnNodeWithoutVerify(otherCurrent->getInfo());
        }
        otherCurrent = otherCurrent->getNext();
    }

    // reutilizamos other y own Current
    otherCurrent = other.firstNode;
    
    while (otherCurrent != NULL) {
        // el apuntador de la lista de adyacencia
        NodeEdge<T> *otherCurrentEdge = otherCurrent->getListAdj();
        NodeVertex<T> *v = ownNodes[otherCurrent->getInfo()];

        while (otherCurrentEdge != NULL) {
            float weight = otherCurrentEdge->getWeight();
            NodeVertex<T> *w = ownNodes[otherCurrentEdge->getInfo()->getInfo()];

            createConnection(v, w, weight);

            otherCurrentEdge = otherCurrentEdge->getNext();
        }
        otherCurrent = otherCurrent->getNext();
    }

    nodeCount = other.nodeCount;
    edgeCount = other.edgeCount;
}

template<class T>
NodeVertex<T>* GraphDirected<T>::findNode(const T &info) const{
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
NodeVertex<T> *GraphDirected<T>::createAndReturnNode(const T &v){
    if (this->findNode(v) != NULL) {
        //std::cout << "createAndReturnNode(const T &v): Este nodo ya fue añadido."  << std::endl;
        return this->findNode(v);
    }

    NodeVertex<T> *newNode = new NodeVertex<T>(v);

    newNode->setNext(firstNode);
    firstNode = newNode;
    nodeCount++;

    return newNode;
}

template<class T>
NodeVertex<T> *GraphDirected<T>::createAndReturnNodeWithoutVerify(const T &v){
    NodeVertex<T> *newNode = new NodeVertex<T>(v);

    newNode->setNext(firstNode);
    firstNode = newNode;
    nodeCount++;

    return newNode;
}

// OK
template<class T>
void GraphDirected<T>::addEdge(NodeVertex<T> *v, NodeVertex<T> *w, float weight){
    if (v == NULL || w == NULL) {
        std::cout << "addEdge(NodeVertex<T> *v, NodeVertex<T> *w, float weight): No se ha encontrado alguno de los vetices" << std::endl;
        return;
    }

    // Check for existing edge
    NodeEdge<T> *current = v->getListAdj();
    while (current != NULL) {
        if (current->getInfo() == w) {
            return;
        }
        current = current->getNext();
    }
    
        
    createConnection(v, w, weight);
    edgeCount++;
}

// OK
template<class T>
void GraphDirected<T>::removeEdge(NodeVertex<T> *v, NodeVertex<T> *w){
    if (v == NULL || w == NULL) {
        return;
    }

    // Si se eliminó, se decrementa el contador de aristas.
    if (removeConnection(v, w)) {
        edgeCount--;
    }
}

// puede cambiar en el futuro
template<class T>
bool GraphDirected<T>::existPathBetween(const T &initialNode, const T &finalNode, std::set<std::pair<T, T> > &exceptions){
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

        std::list<T> neighbors = getSuccessors(v);
        while (!neighbors.empty()) {

            T w = neighbors.front();
            // si se está en una excepción, entonces eliminamos el vecino.
            std::pair<T,T> edge = {v, w};
            
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
GraphDirected<T>::GraphDirected() : firstNode(NULL), nodeCount(0), edgeCount(0){}

// OK
template<class T>
GraphDirected<T>::GraphDirected(GraphDirected<T> &other) : firstNode(NULL), nodeCount(0), edgeCount(0){
    copy(other);
}

template<class T>
GraphDirected<T>::GraphDirected(const std::unordered_map<T, std::list<std::pair<T, float > > >& mapa) : firstNode(NULL), nodeCount(0), edgeCount(0){
    std::unordered_map<T, NodeVertex<T> *> nodes;
    // Crear todos los nodos y links
    for (const auto& pair : mapa) {
        T vName = pair.first;
        
        if (nodes.find(vName) == nodes.end()) {
            nodes[vName] = createAndReturnNodeWithoutVerify(vName);
        }

        NodeVertex<T> *v = nodes[vName];

        for (const auto& pairEdge : pair.second) {
            T wName = pairEdge.first;
            float weight = pairEdge.second;
            
            if (nodes.find(wName) == nodes.end()) {
                nodes[wName] = createAndReturnNodeWithoutVerify(wName);
            }

            NodeVertex<T> *w = nodes[wName];

            createConnection(v, w, weight);
            edgeCount++;
        }
    }
}

// OK
template<class T>
GraphDirected<T>::~GraphDirected(){
    clear();
}

// OK
template<class T>
void GraphDirected<T>::clear(){
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
} //



    /* 
    *********
    Node ops.
    *********
    */



template<class T>
void GraphDirected<T>::removeNode(const T &v){
    NodeVertex<T> *trash = firstNode;
    NodeVertex<T> *previousVertex = NULL;
    
    while (trash != NULL && trash->getInfo() != v) {
        previousVertex = trash;
        trash = trash->getNext();
    }

    if (trash == NULL) {
        std::cout << "removeNode(const T &v): Vertice no encontrado" << std::endl;
        return;
    }

    // eliminar enlaces salientes
    NodeEdge<T> *currentEdge = trash->getListAdj();
    while(currentEdge != NULL) {
        NodeEdge<T> *nextEdge = currentEdge->getNext();

        // los eliminamos aqui directamente ya que no es necesario recorrer de nuevo
        delete currentEdge;
        edgeCount--;
        
        currentEdge = nextEdge;
    }

    // eliminar enlaces entrantes
    NodeVertex<T> *current = firstNode;
    
    while (current != NULL) {
        if (current != trash) {
            currentEdge = current->getListAdj();
            while (currentEdge != NULL) {
                NodeEdge<T> *nextEdge = currentEdge->getNext();
                if (currentEdge->getInfo() == trash) {
                    removeEdge(current, trash);
                }
                currentEdge = nextEdge;
            }
        }
        current = current->getNext();
    }
    
    // eliminar el vertice
    if (previousVertex == NULL) {
        firstNode = trash->getNext();
    }
    else {
        previousVertex->setNext(trash->getNext());
    }

    delete trash;
    nodeCount --;
}

template<class T>
void GraphDirected<T>::addNode(const T &v, std::list<std::pair<T, float> > &outcomingLinks, std::list<std::pair<T, float> > &incomingLinks){
    if (this->findNode(v) != NULL) {
        //std::cout << "addNode(const T &v, std::list<std::pair<T, float> > &links): Este nodo ya fue añadido." << std::endl;
        return;
    }

    // crear e insertar el nuevo nodo
    NodeVertex<T> *newNode = new NodeVertex<T>(v);
    newNode->setNext(firstNode);
    firstNode = newNode;
    nodeCount++;
    
    // formar enlaces:
    for (typename std::list<std::pair<T, float> >::iterator it = outcomingLinks.begin(); it != outcomingLinks.end(); it++) {
        T nodeInfo = it->first;
        float weight = it->second;
        
        addEdge(v, nodeInfo, weight);
    }

    for (typename std::list<std::pair<T, float> >::iterator it = incomingLinks.begin(); it != incomingLinks.end(); it++) {
        T nodeInfo = it->first;
        float weight = it->second;
        
        addEdge(nodeInfo, v, weight);
    }
}

// OK
template<class T>
void GraphDirected<T>::addNode(const T &v){
    if (this->findNode(v) != NULL) {
        //std::cout << "addNode(const T &v): Este nodo ya fue añadido." << std::endl;
        return;
    }

    NodeVertex<T> *newNode = new NodeVertex<T>(v);

    newNode->setNext(firstNode);
    firstNode = newNode;
    nodeCount++;
}

// OK
template<class T>
bool GraphDirected<T>::existNode(const T &v) const{
    return findNode(v) != NULL;
}



    /* 
    *********
    Edge ops.
    *********
    */



template<class T>
void GraphDirected<T>::removeEdge(const T &v, const T &w){
    NodeVertex<T> *ptrV = findNode(v);
    NodeVertex<T> *ptrW = findNode(w);
    removeEdge(ptrV, ptrW);
}

template<class T>
void GraphDirected<T>::addEdge(const T &v, const T& w, float weight){
    // En lugar de retornar sin hacer la conexion cuando no se encuentran los nodos, vamos a crearlos.
    NodeVertex<T> *ptrV = findNode(v);
    NodeVertex<T> *ptrW = findNode(w);


    if (ptrV == NULL || ptrW == NULL) {
        //std::cout << "addEdge(const T &v, const T& w, const float weight): No se ha encontrado alguno de los vetices" << std::endl;
        return;
    }

    addEdge(ptrV, ptrW, weight);
}

template<class T>
void GraphDirected<T>::setWeightOfEdge(const T &v, const T& w, float weight){
    NodeVertex<T> *ptrV = findNode(v);
    NodeVertex<T> *ptrW = findNode(w);
    
    if (ptrV == NULL || ptrW == NULL) 
    {
        std::cout << "setWeightOfEdge: No se ha encontrado alguno de los vetices" << std::endl;
        return;
    }

    NodeEdge<T> *edgeVW = ptrV->getListAdj();

    while (edgeVW != NULL && edgeVW->getInfo() != ptrW) 
    {
        edgeVW = edgeVW->getNext();
    }

    if (edgeVW != NULL) 
    {
        edgeVW->setWeight(weight);
    } 
    else 
    {
        std::cout << "setWeightOfEdge: No se ha encontrado el edge" << std::endl;
    }
} //

template<class T>
bool GraphDirected<T>::existEdge(const T &v, const T& w) const{
    NodeVertex<T> *ptrV = findNode(v);
    NodeVertex<T> *ptrW = findNode(w);
    
    if (ptrV == NULL || ptrW == NULL) 
    {
        std::cout << "existEdge: No se ha encontrado alguno de los vetices" << std::endl;
        return false;
    }


    NodeEdge<T> *edgeVW = ptrV->getListAdj();

    while (edgeVW != NULL && edgeVW->getInfo() != ptrW) 
    {
        edgeVW = edgeVW->getNext();
    }

    if (edgeVW != NULL) 
    {
        return true;
    }

    return false;
}


    /* 
    *******
    Getters
    *******
    */


// OK
template<class T>
T &GraphDirected<T>::getFirstNode() const{
    if (nodeCount == 0 || firstNode == NULL) {
        throw std::runtime_error("getFirstNode(): Grafo vacio.");
    }
    return firstNode->getInfo();
} 

// OK
template<class T>
int GraphDirected<T>::getNodeCount() const{
    return nodeCount;
}

// OK
template<class T>
int GraphDirected<T>::getEdgeCount() const{
    return edgeCount;
}

template<class T>
std::list<T> GraphDirected<T>::getNeighbors(const T &v) const{
    std::list<T> result;
    NodeVertex<T> *currentVertex = firstNode;
    std::unordered_map<T, NodeVertex<T> *> saved;
    
    // se recorre el grafo completo.
    while (currentVertex != NULL) {
        NodeEdge<T> *currentEdge = currentVertex->getListAdj();

        while (currentEdge != NULL) {
            // se guarda:
            // si es un enlace desde otro nodo
            // si es un enlace saliente del nodo
            // y si aun no se ha guardado
            
            // estando desde otro vertice
            if (currentEdge->getInfo()->getInfo() == v) {
                T neighbor;
                NodeVertex<T> *neighborPtr;

                neighbor = currentVertex->getInfo();
                neighborPtr = currentVertex;

                if (saved.find(neighbor) == saved.end()) {
                    result.push_back(neighbor);
                    saved[neighbor] = neighborPtr;
                }
            }
            // si estoy en el vertice
            else if (currentVertex->getInfo() == v) {
                T neighbor;
                NodeVertex<T> *neighborPtr;

                neighbor = currentEdge->getInfo()->getInfo();
                neighborPtr = currentEdge->getInfo();

                if (saved.find(neighbor) == saved.end()) {
                    result.push_back(neighbor);
                    saved[neighbor] = neighborPtr;
                }
            }

            // si no esta guardado ya, se guarda.

            currentEdge = currentEdge->getNext();
        }
        currentVertex = currentVertex->getNext();
    }
    for (auto it = result.begin(); it != result.end(); it++) {
        std::cout << " e: " << *it << std::endl;
    }

    return result;
}

// OK
template<class T>
std::list<T> GraphDirected<T>::getSuccessors(const T &v) const{
    std::list<T> result;
    
    NodeVertex<T> *currentVertex = findNode(v);
    
    // si current es null entonces no lo encontró
    if (currentVertex == NULL) {
        std::cout << "getSuccessors: Vertice no encontrado" << std::endl;
        return result;
    }
    
    NodeEdge<T> *currentEdge = currentVertex->getListAdj();

    while(currentEdge != NULL) {
        result.push_back(currentEdge->getInfo()->getInfo());
        currentEdge = currentEdge->getNext();
    }
    
    return result;
} // outcoming

template<class T>
std::list<T> GraphDirected<T>::getPredecessors(const T &v) const{
    std::list<T> result;
    NodeVertex<T> *currentVertex = firstNode;
    
    // se recorre el grafo completo.
    while (currentVertex != NULL) {
        NodeEdge<T> *currentEdge = currentVertex->getListAdj();

        while (currentEdge != NULL) {
            // se guarda si es un enlace desde otro nodo o si existe un bucle
            if (currentEdge->getInfo()->getInfo() == v) {
                result.push_back(currentVertex->getInfo());
            }
            currentEdge = currentEdge->getNext();
        }
        currentVertex = currentVertex->getNext();
    }

    return result;
} // incoming

template<class T>
float GraphDirected<T>::getWeightOfEdge(const T &v, const T& w){
    NodeVertex<T> *ptrV = findNode(v);
    NodeVertex<T> *ptrW = findNode(w);
    
    if (ptrV == NULL || ptrW == NULL) {
        throw std::out_of_range("getWeightOfEdge: No se ha encontrado alguno de los vetices");
    }
    
    // ahora buscamos el arco
    // v -> w
    NodeEdge<T> *edgeVW = ptrV->getListAdj();
    while (edgeVW != NULL && edgeVW->getInfo() != ptrW) {
        edgeVW = edgeVW->getNext();
    }

    if (edgeVW == NULL) {
        throw std::out_of_range("getWeightOfEdge: No se ha encontrado el edge v -> w");

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
bool GraphDirected<T>::isEmpty() const{
    return nodeCount == 0;
}

// OK
template<class T>
bool GraphDirected<T>::isTree(){
    // Grafo Vacio
    if (nodeCount == 0) {
        return false;
    }

    // Un grafo con N nodos debe tener N-1 aristas para ser un arbol
    if (edgeCount != nodeCount - 1) {
        return false;
    }

    // solo un nodo no debe tener predecesores, se busca el primero que no tenga
    NodeVertex<T> *current = firstNode;
    while (current != NULL) {
        if (getPredecessors(current->getInfo()).empty()) {
            break;
        }
        current = current->getNext();
    }
    
    if (current == NULL) {
        return false;
    }

    T root = current->getInfo(); 

    // El grafo debe ser totalmente conexo. BFS debe incluir todos los nodos
    std::list<T> result = bfs(root);

    // Si el nro de nodos visitados es igual al nro total de nodos, es conexo
    if ((int)result.size() == nodeCount) {
        return true; // es conexo.
    } else {
        return false; // es disconexo
    }
    return false; 
} 

template<class T>
std::list<T> GraphDirected<T>::bfs(const T &initialNode) const{
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

    std::list<T> successors;
    T v, w;

    currentNode.push(initialNode);
    visited[initialNode] = true;

    while (!currentNode.empty()) {
        v = currentNode.front();
        successors = getSuccessors(v);
        while (!successors.empty()) {
            w = successors.front();
            if (!visited[w]) {
                currentNode.push(w);
                visited[w] = true;
            }
            successors.pop_front();
        }
        result.push_back(v);
        currentNode.pop();
    }

    return result;
}

template<class T>
std::list<T> GraphDirected<T>::dfs(const T &initialNode) const{
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

// DFS Recorrido completo. DEBO ARREGLARLO
template<class T>
std::list<T> GraphDirected<T>::dfs() const{
    std::list<T> result;
    std::unordered_map<T, bool> visited;

    // llenar el mapa y validar que el nodo inicial se encuentra
    NodeVertex<T> *current = firstNode;
    while (current != NULL) {
        visited[current->getInfo()] = false;
        current = current->getNext();
    }

    if (visited.find(getFirstNode()) != visited.end()) {

        dfs(getFirstNode(), visited, result);
    }
    return result;
}

// OK
template<class T>
void GraphDirected<T>::show() const{
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
std::list<std::pair<T,T> > GraphDirected<T>::getBridges(){
    std::list<std::pair<T,T> > result;
    /* std::unordered_map<NodeVertex<T>*, NodeVertex<T>* > probados;
    std::set<std::pair<T, T> > testedEdges; 
    // recorrer el grafo
    NodeVertex<T> *currentV = firstNode;
    while (currentV != NULL) {

        NodeEdge<T> *currentEdgeVW = currentV->getListAdj();

        // solo tiene una conexion
        while (currentEdgeVW != NULL) {
            NodeVertex<T> *currentW = currentEdgeVW->getInfo();

            T vInfo = currentV->getInfo();
            T wInfo = currentW->getInfo();

            // Create a pair for the edge
            std::pair<T, T> edgePair = {vInfo, wInfo};
            
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
    } */
    return result;
}

// puede cambiar
template<class T>
std::list<T> GraphDirected<T>::findPathBetween(const T &v, const T &w){
    return findPathBetween(v, w, std::list<std::pair<NodeVertex<T>*,NodeVertex<T>*> >());
}

    

    /* 
    *********
    Operators
    *********
    */


// OK
template<class T>
GraphDirected<T>& GraphDirected<T>::operator = (GraphDirected &g){
    if (this != &g) {
        clear();
        copy(g);
    }
    return *this;
} //

#endif