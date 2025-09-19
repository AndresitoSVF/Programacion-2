#pragma once
#include "NodeVertex.h"
#include "NodeEdge.h"
#include <list>

template<class T>
class GraphDirected
{
private:
    NodeVertex<T> *firstNode;
    int nodeCount, edgeCount;
public:
    GraphDirected(/* args */);
    GraphDirected(GraphDirected<T> &other);
    ~GraphDirected();
    T &getFirstNode();
    int getNodeCount();
    int getEdgeCount();
    void removeNode(T &v);
    void addNode(T &v, list<T> &outcomingLinks, list<T> &incomingLinks);
    void addNode(T &v);
    void removeEdge(T &v)
    void addEdge(T &v, T& w);
    void setWeightOfEdge(T &v, T& w, float weight);
    list<T> &getOutcomingOf(T &v);
    list<T> &getIncomingOf(T &v);
    list<T> &getNeighbors(T &v); // outcoming + incoming
    bool isEmpty();
    bool isTree();
    list<T> &bfs();
    list<T> &dfs();
};

#include "GraphDirected.cpp"