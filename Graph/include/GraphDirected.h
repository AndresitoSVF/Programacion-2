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
public:
    GraphDirected(/* args */);
    GraphDirected(GraphDirected<T> &other);
    ~GraphDirected();
    T &getFirstNode();
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
    std::list<T> &dfs();
};

#include "GraphDirected.cpp"