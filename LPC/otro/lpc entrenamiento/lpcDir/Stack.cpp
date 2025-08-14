#include <cstddef>
#include "Stack.hpp"

template <typename T>
Stack<T>::Stack() : top(NULL), size(0) {}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) : top(NULL), size(other.size) {
    SimpleLinkNode<T>* currentOther = other.top;
    SimpleLinkNode<T>* current = NULL;

    if (currentOther == NULL) return;

    top = new SimpleLinkNode<T>(currentOther->getValue());
    current = top;
    currentOther = currentOther->getNext();

    while (currentOther != NULL) {
        SimpleLinkNode<T>* newNode = new SimpleLinkNode<T>(currentOther->getValue());

        current->setNext(newNode);
        current = newNode;
        currentOther = currentOther->getNext();
    }
}

template <typename T>
Stack<T>::~Stack() {
    clear();
}

template <typename T>
void Stack<T>::push(const T& value) {
    SimpleLinkNode<T>* newNode = new SimpleLinkNode<T>(value, top);
    top = newNode;
    size++;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) throw std::runtime_error("Stack is empty");

    SimpleLinkNode<T>* temp = top;
    T value = top->getValue();

    top = top->getNext();
    delete temp;
    size--;

    return value;
}

template <typename T>
T Stack<T>::peek()   {
    if (isEmpty()) throw std::runtime_error("Stack is empty");
    return top->getValue();
}

template <typename T>
inline bool Stack<T>::isEmpty()     {
    return size == 0;
}

template <typename T>
inline int Stack<T>::getSize()     {
    return size;
}

template <typename T>
void Stack<T>::clear() {
    while (!isEmpty()) {
        pop();
    }
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
    if (stack.size == 0) {
        os << "stack is empty";
        return os;
    }

    SimpleLinkNode<T>* current = stack.top;

    os << "TOP\n";
    os << "|\n";
    os << "v\n";
    
    while (current != NULL) {
        os << current->getValue() << " -> ";
        current = current->getNext();
    }
    os << "NULL";
    return os;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
        clear();

        size = other.size;
        SimpleLinkNode<T>* currentOther = other.top;
        SimpleLinkNode<T>* dummy = new SimpleLinkNode<T>(T()); // Dummy node to handle the first node case
        
        SimpleLinkNode<T>* current = dummy;
        while (currentOther != NULL) {
            SimpleLinkNode<T>* newNode = new SimpleLinkNode<T>(currentOther->getValue());

            current->setNext(newNode);
            current = newNode;
            currentOther = currentOther->getNext();
        }
        current->setNext(NULL);

        top = dummy->getNext();
        delete dummy;
     }

    return *this;
}
