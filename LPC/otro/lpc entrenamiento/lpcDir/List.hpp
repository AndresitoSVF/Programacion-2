#ifndef LIST
#define LIST

#include "DoubleLinkNode.hpp"
#include <ostream>
#include <iostream>

template <typename T>
class List {

    public:
        List();

        List(const List<T>& other);

        ~List();

        int countSpacesBetweenRepetitions(const T& value);

        inline T& get(const int& position);

        void insert(const T& value, const int& position);
        void insertEnd(const T& value);
        void insertStart(const T& value);

        void removeByValue(const T& value);
        void removeAllByValue(const T& value);
        void removeByPosition(const int& position);
        void removeStart();
        void removeEnd();

        void replace(const T& value, const int& position);

        bool isEmpty();
        int getSize();

        void extends(const List<T>& other);

        void reverse();

        int index(const T& value)  ;

        void clear();

        List<T> map(T (*fun)(const T& value, const int& index));
        List<T> map(T (*fun)(const T& value));

        List<T> filter(bool (*fun)(const T& value, const int& index));
        List<T> filter(bool (*fun)(const T& value)); 

        T& operator[](const int& position)  ;
        
        bool operator==(const List<T>& other)  ;
        bool operator!=(const List<T>& other)  ;
        
        List<T>& operator=(const List<T>& other);

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const List<U>& list);

        int max();

        int min();
    private:
        DoubleLinkNode<T>* head;
        DoubleLinkNode<T>* tail;
        int size;

        DoubleLinkNode<T>* lastUsed;
        int lastUsedPosition;

        DoubleLinkNode<T>* getNode(const int& position);

        void removeNode(DoubleLinkNode<T>* node);
};

namespace ListUtils {
    template <typename T>
    void readVertical(List<List<T> >& lists);
}


//#include "List.cpp"

#endif
