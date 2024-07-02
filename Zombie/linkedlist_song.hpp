#ifndef LINKEDLIST_<LASTNAME>_HPP
#define LINKEDLIST_<LASTNAME>_HPP

#include <stdexcept>
#include <iostream>

template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node() : next(nullptr), prev(nullptr) {}
    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList();

    void AddToFront(T data);
    void AddToEnd(T data);
    void AddAtIndex(T data, int index);
    void AddBefore(Node<T>* node, T data);
    void AddAfter(Node<T>* node, T data);
    T RemoveFromFront();
    T RemoveFromEnd();
    void RemoveTheFirst(T data);
    void RemoveAllOf(T data);
    T RemoveBefore(Node<T>* node);
    T RemoveAfter(Node<T>* node);
    bool ElementExists(T data);
    Node<T>* Find(T data);
    int IndexOf(T data);
    T RetrieveFront();
    T RetrieveEnd();
    T Retrieve(int index);
    void PrintList();
    void Empty();
    int Length();
};

// Destructor to clean up all nodes
template<typename T>
LinkedList<T>::~LinkedList() {
    Empty();
}

template<typename T>
void LinkedList<T>::AddToFront(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

template<typename T>
void LinkedList<T>::AddToEnd(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (!tail) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template<typename T>
void LinkedList<T>::AddAtIndex(T data, int index) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Index out of range");
    }
    if (index == 0) {
        AddToFront(data);
    } else if (index == size) {
        AddToEnd(data);
    } else {
        Node<T>* newNode = new Node<T>(data);
        Node<T>* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
        size++;
    }
}

// Implement other methods similarly...

#endif // LINKEDLIST_<LASTNAME>_HPP
