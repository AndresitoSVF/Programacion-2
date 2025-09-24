#pragma once
#include "NodeVertex.h"
#include "NodeEdge.h"
#include <list>
#include <unordered_map>
#include <vector>

template<class T>
class NodeVertex;

template<class T>
class NodeEdge;

template<class T>
class GraphUndirected {
private:
    NodeVertex<T> *firstNode;
    int nodeCount, edgeCount;
    
    void removeConnection(NodeVertex<T> *v, NodeVertex<T> *w); // elimina la conexion de v a w
    void createConnection(NodeVertex<T> *v, NodeVertex<T> *w, float weight); // hace la conexion entre ambos nodos.
    void dfs(const GraphUndirected<int> &g, const int &initialNode, std::vector<bool> visited, std::list<int> &result) const;
    void copy(const GraphUndirected<int> &other); // copia a este el otro grafo; no vacia antes de hacerlo
    

    public:
    GraphUndirected(); //
    GraphUndirected(GraphUndirected<T> &other); //
    GraphUndirected(const std::unordered_map<Element, std::list<Element> >& mapa); //
    ~GraphUndirected(); //
    void clear(); //
    T &getFirstNode() const; //
    int getNodeCount() const; //
    int getEdgeCount() const; //
    void removeNode(const T &v); //
    void addNode(const T &v, std::list<std::pair<T, float> > &links);
    void addNode(const T &v);
    void removeEdge(const T &v, const T &w);
    void addEdge(const T &v, const T& w, const float weight = 0);
    void setWeightOfEdge(const T &v, const T& w, const float weight = 0); //
    std::list<T> getNeighbors(const T &v) const; // outcoming + incoming
    bool isEmpty() const; //
    bool isTree() const; 
    static std::list<int> bfs(const GraphUndirected<int>& g, const int &initialNode);//
    std::list<int> bfs();//
    static std::list<int> dfs(const GraphUndirected<int> &g, const int &initialNode); //
    std::list<int> dfs();//
    void operator = (GraphUndirected &g); //
};

#include "GraphUndirected.cpp"