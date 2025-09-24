#pragma once

template<class T>
class NodeVertex;

template<class T>
class NodeEdge {
private:
    float weight;
    NodeEdge<T> *next;
    NodeVertex<T> *info;
public:
    NodeEdge(const float weight = 0);
    NodeVertex<T> *getInfo();
    NodeEdge<T> *getNext();
    float getWeight();
    void setInfo(NodeVertex<T> *info);
    void setNext(NodeEdge<T> *next);
    void setWeight(T &weight);
};

#include "NodeEdge.cpp"