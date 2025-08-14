#ifndef STACK
#define STACK

#include "SimpleLinkNode.hpp"
#include <stdexcept>
#include <ostream>

template <typename T>
class Stack {
    public:
        Stack(); 

        Stack(const Stack<T>& other); 

        ~Stack(); 
        
        void push(const T& value); 

        T pop(); 

        T peek()  ;

        inline bool isEmpty()    ;

        inline int getSize()    ;

        void clear(); 

        template <typename S>
        friend std::ostream& operator<<(std::ostream& os, const Stack<S>& stack);

        Stack<T>& operator=(const Stack<T>& other);

    private:
        SimpleLinkNode<T>* top;
        int size;
};

//#include "Stack.cpp"

#endif
