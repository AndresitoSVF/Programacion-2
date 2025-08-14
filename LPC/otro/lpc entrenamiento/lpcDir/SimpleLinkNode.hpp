#include <cstddef>
#ifndef SIMPLE_LINK_NODE
#define SIMPLE_LINK_NODE

template <typename T>
class SimpleLinkNode {

    public:
        SimpleLinkNode(T value, SimpleLinkNode<T>* next = NULL) : value(value), next(next) {}

        inline T& getValue()   { return value; }

        inline SimpleLinkNode* getNext()     { return next; }

        inline void setNext(SimpleLinkNode<T>* next)   { this->next = next; }

        inline void setValue(const T& value)   { this->value = value; }
    
    private:
        T value;
        SimpleLinkNode<T>* next;
};

#endif 
