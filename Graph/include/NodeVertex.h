#pragma once

template<class T>
class NodeEdge;

template<class T>
class NodeVertex {
private:
    T info;
    NodeVertex<T> *next;
    NodeEdge<T> *listAdj; // Adjacency list
public:
    NodeVertex(/* args */);
    NodeVertex(const T &info);
    T &getInfo();
    NodeVertex<T> *getNext();
    NodeEdge<T> *getListAdj();
    void setInfo(T &info);
    void setNext(NodeVertex<T> *next);
    void setListAdj(NodeEdge<T> *listAdj);
};

#include "NodeVertex.cpp"