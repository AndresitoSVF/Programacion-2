#include <cstddef>
#include "List.hpp"
#include <stdexcept>
#include <ostream>

template <typename T>
List<T>::List() 
: head(NULL), tail(NULL), size(0), lastUsed(NULL),  lastUsedPosition(0) {}

template <typename T>
List<T>::List(const List<T>& other)
: head(NULL), tail(NULL), size(0), lastUsed(NULL),  lastUsedPosition(0)
{
    DoubleLinkNode<T>* current = other.head;
    while (current != NULL) {
        insertEnd(current->getValue());
        current = current->getNext();
    }
} 

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
int List<T>::countSpacesBetweenRepetitions(const T& value) {
    int spaces = 0;
    int spacesTemp = 0;
    int repeated = 0;

    DoubleLinkNode<T>* current = head;

    while (current != NULL) {
        if (current->getValue() == value) {
            spacesTemp += repeated;
            spaces = spacesTemp;
            repeated++;
        } else {
            spacesTemp += repeated;
        }
        current = current->getNext();
    }
    return spaces;
}

template <typename T>
T& List<T>::get(const int& position) {
    return getNode(position)->getValue();
}

template <typename T>
void List<T>::insert(const T& value, const int& position) {

   DoubleLinkNode<T>* newNode = new DoubleLinkNode<T>(value);

    if (isEmpty()) {
        head = tail = newNode;
    } else if (position == 0) {
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
    } else if (position == size) {
        tail->setNext(newNode);
        newNode->setPrev(tail);
        tail = newNode;
    } else {
        DoubleLinkNode<T>* current = getNode(position);
        DoubleLinkNode<T>* prevNode = current->getPrev();
        
        prevNode->setNext(newNode);
        newNode->setPrev(prevNode);

        newNode->setNext(current);
        current->setPrev(newNode);
    }

    size++;
    lastUsed = newNode;
    lastUsedPosition = position;
}

template <typename T>
void List<T>::insertEnd(const T& value) {
    insert(value, size);
}

template <typename T>
void List<T>::insertStart(const T& value) {
    insert(value, 0);
}

template <typename T>
void List<T>::removeByValue(const T& value) {
    DoubleLinkNode<T>* current = head;
    
    while (current != NULL && current->getValue() != value) current = current->getNext();
    
    if (current == NULL) return;
    removeNode(current);
}

template <typename T>
void List<T>::removeAllByValue(const T& value) {
    DoubleLinkNode<T>* current = head;
    DoubleLinkNode<T>* toDelete;
    
    while (current != NULL) {
        if (current->getValue() == value) {

            toDelete = current;
            current = current->getNext();
            removeNode(toDelete);
        } else {
            current = current->getNext();
        }
    }
}

template <typename T>
void List<T>::removeByPosition(const int& position) {
    DoubleLinkNode<T>* toDelete = getNode(position);
    removeNode(toDelete);
}

template <typename T>
void List<T>::removeStart() {
    removeNode(head);
}
        
template <typename T>
void List<T>::removeEnd() {
    removeNode(tail);
}

template <typename T>
void List<T>::replace(const T& value, const int& position) {
    getNode(position)->setValue(value);
}

template <typename T>
bool List<T>::isEmpty()     {
    return size == 0;
}

template <typename T>
int List<T>::getSize()     {
    return size;
}

template <typename T>
void List<T>::extends(const List<T>& other) {
    DoubleLinkNode<T>* current = other.head;
    while (current != NULL) {
        insertEnd(current->getValue());
        current = current-> getNext();
    }
}

template <typename T>
void List<T>::reverse()   {
    DoubleLinkNode<T>* current = head;
    DoubleLinkNode<T>* temp = NULL;

    while (current != NULL) {
        temp = current->getPrev();
        current->setPrev(current->getNext());
        current->setNext(temp);
        current = current->getPrev();
    }

    temp = head;
    head = tail;
    tail = temp;

    lastUsed = NULL;
    lastUsedPosition = 0;
}

template <typename T>
int List<T>::index(const T& value)   {
    DoubleLinkNode<T>* current = head;
    int index = 0;

    while (current != NULL) {
        if (current->getValue() == value) {
            lastUsed = current; 
            lastUsedPosition = index; 

            return index;
        }
        current = current->getNext();
        index++;
    }

    return -1; // Value not found
}

template <typename T>
void List<T>::clear() {
    DoubleLinkNode<T>* current = head;
    while (current != NULL) {
        DoubleLinkNode<T>* next = current->getNext();
        delete current;
        current = next;
    }
    head = tail = lastUsed = NULL;
    size = 0;
    lastUsedPosition = 0;
}



template <typename T>
List<T> List<T>::map(T (*fun)(const T& value, const int& index)) {

    List newList;

    DoubleLinkNode<T>* current = head;
    int index = 0;
    while (current) {
        newList.insertEnd(fun(current->getValue(), index));
        current = current->getNext();
        index++;
    }

    return newList;
}

template <typename T>
List<T> List<T>::map(T (*fun)(const T& value)) {

    List newList;

    DoubleLinkNode<T>* current = head;
    while (current) {
        newList.insertEnd(fun(current->getValue()));
        current = current->getNext();
    }

    return newList;
}

template <typename T>
List<T> List<T>::filter(bool (*fun)(const T& value, const int& index)) {
    List newList;

    DoubleLinkNode<T>* current = head;
    int index = 0;
    while(current) {
        T value = current-> getValue();
        if (fun(value, index)) newList.insertEnd(value);

        current = current-> getNext();
        index++;
    }

    return newList;
}

template <typename T>
List<T> List<T>::filter(bool (*fun)(const T& value)) {
    List newList;

    DoubleLinkNode<T>* current = head;
    while(current) {
        T value = current-> getValue();
        if (fun(value)) newList.insertEnd(value);

        current = current-> getNext();
    }

    return newList;
}

template <typename T> 
T& List<T>::operator[](const int& position)   {
    return getNode(position)->getValue();
}

template <typename T>
bool List<T>::operator==(const List<T>& other)   {
    if (size != other.size) return false;

    DoubleLinkNode<T>* current1 = head;
    DoubleLinkNode<T>* current2 = other.head;

    while (current1 != NULL && current2 != NULL) {
        if (current1->getValue() != current2->getValue()) {
            return false;
        }
        current1 = current1->getNext();
        current2 = current2->getNext();
    }

    return true;
}

template <typename T>
bool List<T>::operator!=(const List<T>& other)   {
    return !(*this == other);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {
    DoubleLinkNode<T>* current = list.head;
    os << "[";
    while (current != NULL) {
        os << current->getValue() << ((current->getNext() != NULL) ? ", " : "");
        current = current->getNext();
    }
    os << "]";
    return os;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this != &other) {
        clear();
        extends(other);
    }
    return *this;
}

template <typename T>
DoubleLinkNode<T>* List<T>::getNode(const int& position) {

    if (position < 0 || position >= size) {
        throw std::out_of_range("Position out of range of list");
    }

    int distance = (position - lastUsedPosition > 0) ? 
    position - lastUsedPosition : 
    lastUsedPosition - position;
    
    // if lastUsed is nearest to position than tail or head, use it
    if (
        lastUsed != NULL &&
        distance < position && 
        distance < size - position
    ) {
        if (lastUsedPosition > position) {
            for (int i = lastUsedPosition; i > position; i--) {
                lastUsed = lastUsed->getPrev();
            }
        } else {
            for (int i = lastUsedPosition; i < position; i++) {
                lastUsed = lastUsed->getNext();
            }
        }
    } else if(position > size / 2) {
        // if position is in the second half of the list, start from tail
        lastUsed = tail;
        for (int i = size - 1; i > position; i--) {
            lastUsed = lastUsed->getPrev();
        }
    } else {
        // if position is in the first half of the list, start from head
        lastUsed = head;
        for (int i = 0; i < position; i++) {
            lastUsed = lastUsed->getNext();
        }
    }

    lastUsedPosition = position;

    return lastUsed;
}

template <typename T>
void List<T>::removeNode(DoubleLinkNode<T>* toDelete) {
    if (toDelete == NULL) return;

    if (toDelete->getPrev() != NULL) {
        toDelete->getPrev()->setNext(toDelete->getNext());
    } else {
        head = toDelete->getNext();
        if (head != NULL) {
            head->setPrev(NULL);
        }
    }
    
    if (toDelete->getNext() != NULL) {
        toDelete->getNext()->setPrev(toDelete->getPrev());
    } else {
        tail = toDelete->getPrev();
        if (tail != NULL) {
            tail->setNext(NULL);
        }
    }

    size--;
    lastUsed = NULL; // reset lastUsed since we modified the list
    lastUsedPosition = 0; // reset lastUsedPosition since we modified the list
    delete toDelete;
}

template <>
int List<int>::max() {

    if (head == NULL) {
        return 0;
    }

    int m = head->getValue();
    DoubleLinkNode<int>* current = head->getNext();

    while (current != NULL) {
        if (current->getValue() > m) m = current->getValue();

        current = current->getNext();
    }
    return m;
}

template <>
int List<int>::min() {

    if (head == NULL) {
        return 0;
    }

    int m = head->getValue();
    DoubleLinkNode<int>* current = head->getNext();

    while (current != NULL) {
        if (current->getValue() < m) m = current->getValue();

        current = current->getNext();
    }
    return m;
}

template <typename T>
void ListUtils::readVertical(List<List<T> >& lists) {
    T value;
    int i = 0;
    while (std::cin >> value) {
        if (i >= lists.getSize()) {
            lists.insertEnd(List<T>());
        }
        lists[i].insertEnd(value);
        ++i;
        while (std::cin.peek() == ' ') {
            std::cin.ignore();
        }
        if (std::cin.peek() == '\n') {
            i = 0;
            std::cin.ignore();
        }
    }
}


template class List<int>;
template std::ostream& operator<<(std::ostream&, const List<int>& list);

template class List<std::string>;
template std::ostream& operator<<(std::ostream&, const List<std::string>& list);

template class List<List<int> >;
template std::ostream& operator<<(std::ostream&, const List<List<int> >& list);

template class List<List<std::string> >;
template std::ostream& operator<<(std::ostream&, const List<List<std::string> >& list);
