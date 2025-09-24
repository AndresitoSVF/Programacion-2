#pragma once
#include "NodeVertex.h"
#include <cstddef>

template<class T>
class NodeEdge;

template<class T>
NodeVertex<T>::NodeVertex() :  info(), next(NULL), listAdj(NULL) {}

template<class T>
NodeVertex<T>::NodeVertex(const T &info) : info(info), next(NULL), listAdj(NULL) {}

template<class T>
T &NodeVertex<T>::getInfo() {
    return info;
}

template<class T>
NodeVertex<T> *NodeVertex<T>::getNext(){
    return next;
}

template<class T>
NodeEdge<T> *NodeVertex<T>::getListAdj(){
    return listAdj;
}

template<class T>
void NodeVertex<T>::setInfo(T &info){
    this->info = info;
}

template<class T>
void NodeVertex<T>::setNext(NodeVertex<T> *next){
    this->next = next;
}

template<class T>
void NodeVertex<T>::setListAdj(NodeEdge<T> *listAdj){
    this->listAdj = listAdj;
}