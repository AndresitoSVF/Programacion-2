#include <cstddef>
#include "Queue.hpp"

#include <stdexcept>

template <typename T>
Queue<T>::Queue() : front(NULL), back(NULL), size(0) {}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) : front(NULL), back(NULL), size(other.size) {
    SimpleLinkNode<T>* currentOther = other.front;

    while (currentOther != NULL) {
        enqueue(currentOther->getValue());
        currentOther = currentOther->getNext();
    }
}

template <typename T>
Queue<T>::~Queue() {
    clear();
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
    SimpleLinkNode<T>* newNode = new SimpleLinkNode<T>(value);
    
    if (isEmpty()) {
        front = back = newNode;
    } else {
        back->setNext(newNode);
        back = newNode;
    }
    
    size++;
}

template <typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }

    T value = front->getValue();
    SimpleLinkNode<T>* temp = front;
    front = front->getNext();
    
    if (front == NULL) {
        back = NULL;
    }

    delete temp;
    size--;
    
    return value;
}

template <typename T>
T Queue<T>::peek()   {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    
    return front->getValue();
}

template <typename T>
inline bool Queue<T>::isEmpty()     {
    return size == 0;
}

template <typename T>
inline int Queue<T>::getSize()     {
    return size;
}

template <typename T>
void Queue<T>::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) {

    if (queue.size == 0) {
        os << "queue is empty";
        return os;
    }

    SimpleLinkNode<T>* current = queue.front;


    os << "FRONT\n";
    os << "|\n";
    os << "v\n";


    while (current != NULL) {
        os << current->getValue() << " -> ";
        current = current-> getNext();
    }
    os << "NULL";
    return os;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
        clear();
        
        SimpleLinkNode<T>* currentOther = other.front;
        while (currentOther != NULL) {
            enqueue(currentOther->getValue());
            currentOther = currentOther->getNext();
        }
    }
    return *this;
}


