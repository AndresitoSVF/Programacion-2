#ifndef QUEUE
#define QUEUE
#include "SimpleLinkNode.hpp"
#include <ostream>

template <typename T>
class Queue {

    public:
        Queue();

        Queue(const Queue<T>& other);

        ~Queue();

        void enqueue(const T& value);

        T dequeue();

        T peek()  ;

        inline bool isEmpty()    ;

        inline int getSize()    ;

        void clear();

        template <typename S>
        friend std::ostream& operator<<(std::ostream& os, const Queue<S>& Queue);

        Queue<T>& operator=(const Queue<T>& other);

    private:
        SimpleLinkNode<T>* front;
        SimpleLinkNode<T>* back;
        int size;
};

//#include "Queue.cpp"

#endif
