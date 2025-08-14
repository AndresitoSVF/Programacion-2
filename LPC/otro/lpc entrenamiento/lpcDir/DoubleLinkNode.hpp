#include <cstddef>
#ifndef DOUBLE_LINK_NODE
#define DOUBLE_LINK_NODE

#include "SimpleLinkNode.hpp"

template <typename T>
class DoubleLinkNode : public SimpleLinkNode<T> {
    public:
        DoubleLinkNode(
            T value,
            DoubleLinkNode<T>* next = NULL, 
            DoubleLinkNode<T>* prev = NULL
        )
        : SimpleLinkNode<T>(value, next), prev(prev) {}

        inline DoubleLinkNode<T>* getNext()     {
            return static_cast<DoubleLinkNode<T>*>(SimpleLinkNode<T>::getNext());
        }

        inline DoubleLinkNode<T>* getPrev()     { return prev; }

        inline void setPrev(DoubleLinkNode<T>* prev)   { this->prev = prev; }

    private:
        DoubleLinkNode<T>* prev;

};

#endif 
