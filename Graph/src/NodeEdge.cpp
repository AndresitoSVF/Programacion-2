#ifndef NODE_EDGE_CPP
#define NODE_EDGE_CPP
#include "NodeEdge.h"
#include <cstddef>

template<class T>
class NodeVertex;

template<class T>
NodeEdge<T>::NodeEdge(const float weight) : weight(weight), next(NULL), info(NULL){}

template<class T>
NodeVertex<T> *NodeEdge<T>::getInfo(){
    return info;
}

template<class T>
NodeEdge<T> *NodeEdge<T>::getNext(){
    return next;
}

template<class T>
float NodeEdge<T>::getWeight(){
    return weight;
}

template<class T>
void NodeEdge<T>::setInfo(NodeVertex<T> *info){
    this->info = info;
}

template<class T>
void NodeEdge<T>::setNext(NodeEdge<T> *next){
    this->next = next;
}

template<class T>
void NodeEdge<T>::setWeight(float weight){
    this->weight = weight;
}
#endif
