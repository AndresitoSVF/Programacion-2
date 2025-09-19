#pragma once
#include "NodeEdge.h"
#include <cstddef>

template<class T>
class NodeVertex;

template<class T>
NodeEdge<T>::NodeEdge(/* args */) : weight(), info(NULL), next(NULL)
{
}
template<class T>
NodeEdge<T>::~NodeEdge()
{
}


