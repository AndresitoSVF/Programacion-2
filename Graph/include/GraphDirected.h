#pragma once
#include "NodeVertex.h"
#include "NodeEdge.h"
#include <list>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <set>

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
    bool removeConnection(NodeVertex<T> *v, NodeVertex<T> *w); // elimina la conexion v -> w
    void createConnection(NodeVertex<T> *v, NodeVertex<T> *w, float weight); // hace la conexion v -> w.
    void dfs(const T &initialNode, std::unordered_map<T, bool> &visited, std::list<T> &result) const;
    void copy(const GraphDirected<T> &other); // copia a este el otro grafo; no vacia antes de hacerlo
    NodeVertex<T>* findNode(const T &info) const;
    NodeVertex<T> *createAndReturnNode(const T &v);
    NodeVertex<T> *createAndReturnNodeWithoutVerify(const T &v);
    void addEdge(NodeVertex<T> *v, NodeVertex<T> *w, float weight = 0);
    void removeEdge(NodeVertex<T> *v, NodeVertex<T> *w);

    // puede cambiar en el futuro
    bool existPathBetween(const T &initialNode, const T &finalNode, std::set<std::pair<T, T> > &exceptions);


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
    bool existNode(const T &v) const;


    // edge operations
    void removeEdge(const T &v, const T &w);
    void addEdge(const T &v, const T& w, float weight = 0);
    void setWeightOfEdge(const T &v, const T& w, float weight = 0); //
    bool existEdge(const T &v, const T& w) const;


    // getters
    T &getFirstNode() const; //
    int getNodeCount() const; //
    int getEdgeCount() const; //
    std::list<T> getNeighbors(const T &v) const; // outcoming + incoming
    std::list<T> getSuccessors(const T &v) const; // outcoming
    std::list<T> getPredecessors(const T &v) const; // incoming
    float getWeightOfEdge(const T &v, const T& w); //


    // utility and traversal (esto ultimo creo que es visitar todos los nodos)    
    bool isEmpty() const; //
    bool isTree(); 
    std::list<T> bfs(const T &initialNode) const;//
    std::list<T> dfs(const T &initialNode) const; //
    std::list<T> dfs() const;//
    void show() const;
    std::list<std::pair<T,T> > getBridges();

    // puede cambiar
    std::list<T> findPathBetween(const T &v, const T &w);


    // operators
    GraphDirected<T>& operator = (GraphDirected &g); //
};

#include "GraphDirected.cpp"