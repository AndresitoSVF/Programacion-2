#pragma once
#include "NodeVertex.h"
#include <cstddef>

template<class T>
class NodeEdge;

template<class T>
NodeVertex<T>::NodeVertex() :  info(), next(NULL), listAdj(NULL)
{
    
}

template<class T>
NodeVertex<T>::~NodeVertex()
{
}
