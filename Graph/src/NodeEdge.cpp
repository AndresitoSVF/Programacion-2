#pragma once
#include "NodeEdge.h"
#include <cstddef>

template<class T>
class NodeVertex;

template<class T>
NodeEdge<T>::NodeEdge(const float weight) : weight(weight), info(NULL), next(NULL){}

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
void NodeEdge<T>::setWeight(T &weight){
    this->weight = weight;
}

