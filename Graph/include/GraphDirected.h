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
class GraphDirected
{
private:
    NodeVertex<T> *firstNode;
    int nodeCount, edgeCount;

    //Helpers
    void removeConnection(NodeVertex<T> *v, NodeVertex<T> *w); // elimina la conexion v -> w
    void createConnection(NodeVertex<T> *v, NodeVertex<T> *w, float weight); // hace la conexion v -> w.
    void dfs(const T &initialNode, std::unordered_map<T, bool> &visited, std::list<T> &result) const;
    void copy(const GraphDirected<T> &other); // copia a este el otro grafo; no vacia antes de hacerlo
    NodeVertex<T>* findNode(const T &info) const;
    std::list<NodeVertex<T>* > getNeighbors(NodeVertex<T> *v);
    NodeVertex<T> *createAndReturnNode(const T &v);
    void addEdge(NodeVertex<T> *v, NodeVertex<T> *w, float weight = 0);

public:
    
    // constructors and destructors
    GraphDirected(); //
    GraphDirected(GraphDirected<T> &other); //
    GraphDirected(const std::unordered_map<T, std::list<std::pair<T, float > > >& mapa); //
    ~GraphDirected(); //
    void clear(); //

    // node operations
    void removeNode(const T &v);
    void addNode(const T &v, std::list<std::pair<T, float> > &outcomingLinks, std::list<std::pair<T, float> > &incomingLinks);
    void addNode(const T &v);




    /* T &getFirstNode();
    int getNodeCount();
    int getEdgeCount();
    void removeNode(const T &v);
    void addNode(const T &v, std::list<std::pair<T, float> > &outcomingLinks, std::list<std::pair<T, float> > &incomingLinks);
    void addNode(const T &v);
    void removeEdge(const T &v);
    void addEdge(const T &v, const T& w, const float weight = 0);
    void setWeightOfEdge(const T &v, const T& w, const float weight = 0);
    std::list<T> &getOutcomingOf(const T &v);
    std::list<T> &getIncomingOf(const T &v);
    std::list<T> &getNeighbors(const T &v); // outcoming + incoming
    bool isEmpty();
    bool isTree();
    std::list<T> &bfs();
    std::list<T> &dfs(); */








public:
/* 
    // edge operations
    void removeEdge(const T &v, const T &w);
    void addEdge(const T &v, const T& w, float weight = 0);
    void setWeightOfEdge(const T &v, const T& w, float weight = 0); //

    // getters
    T &getFirstNode() const; //
    int getNodeCount() const; //
    int getEdgeCount() const; //
    std::list<T> getNeighbors(const T &v) const; // outcoming + incoming
    float getWeightOfEdge(const T &v, const T& w); //

    // utility and traversal (esto ultimo creo que es visitar todos los nodos)    
    bool isEmpty() const; //
    bool isTree(); 
    std::list<T> bfs(const T &initialNode) const;//
    std::list<T> bfs2(const T &initialNode);//
    std::list<T> dfs(const T &initialNode) const; //
    std::list<T> dfs() const;//
    void show() const;

    // operadores
    void operator = (GraphUndirected &g); // */

};

#include "GraphDirected.cpp"