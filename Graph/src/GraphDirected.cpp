#pragma once
#include "GraphDirected.h"
#include "NodeVertex.h"
#include "NodeEdge.h"
#include <list>
#include <stdexcept>

/*     NodeVertex<T> *firstNode
    int nodeCount, edgeCount */

/* template<class T>
GraphDirected<T>::GraphDirected(){}

template<class T>
GraphDirected<T>::GraphDirected(GraphDirected<T> &other){}

template<class T>
GraphDirected<T>::~GraphDirected(){}

template<class T>
T &GraphDirected<T>::getFirstNode(){}

template<class T>
int GraphDirected<T>::getNodeCount(){}

template<class T>
int GraphDirected<T>::getEdgeCount(){}

template<class T>
void GraphDirected<T>::removeNode(const T &v){}

template<class T>
void GraphDirected<T>::addNode(const T &v, std::list<std::pair<T, float> > &outcomingLinks, std::list<std::pair<T, float> > &incomingLinks){}

template<class T>
void GraphDirected<T>::addNode(const T &v){}

template<class T>
void GraphDirected<T>::removeEdge(const T &v){}

template<class T>
void GraphDirected<T>::addEdge(const T &v, const T& w, const float weight = 0){}

template<class T>
void GraphDirected<T>::setWeightOfEdge(const T &v, const T& w, const float weight = 0){}

template<class T>
std::list<T> &GraphDirected<T>::getOutcomingOf(const T &v){}

template<class T>
std::list<T> &GraphDirected<T>::getIncomingOf(const T &v){}

template<class T>
std::list<T> &GraphDirected<T>::getNeighbors(const T &v){} // outcoming + incoming

template<class T>
bool GraphDirected<T>::isEmpty(){}

template<class T>
bool GraphDirected<T>::isTree(){}

template<class T>
std::list<T> &GraphDirected<T>::bfs(){}

template<class T>
std::list<T> &GraphDirected<T>::dfs(){}
 */