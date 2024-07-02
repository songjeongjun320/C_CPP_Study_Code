
/*
Name: Jun Song
Date: 07/01/2024
Description: This program simulates a zombie conga line using a templated doubly-linked list.
Usage: 
    Compile the program using the provided Makefile:
        make
    Run the executable:
        ./exe
    This will generate a conga line of zombies with random types, adding them either to the front or the end of the list.
*/

#ifndef LINKEDLIST_YEO_HPP
#define LINKEDLIST_YEO_HPP

#include <stdexcept>
#include <iostream>

// Node class for doubly linked list
template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node() : next(nullptr), prev(nullptr) {}
    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

// Doubly Linked List class
template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList();

    // Adds an element to the front of the list
    void AddToFront(T data);

    // Adds an element to the end of the list
    void AddToEnd(T data);

    // Adds an element at the specified index
    void AddAtIndex(T data, int index);

    // Adds an element before a specified node
    void AddBefore(Node<T>* node, T data);

    // Adds an element after a specified node
    void AddAfter(Node<T>* node, T data);

    // Removes and returns the element at the front of the list
    T RemoveFromFront();

    // Removes and returns the element at the end of the list
    T RemoveFromEnd();

    // Removes the first occurrence of a specific data element
    void RemoveTheFirst(T data);

    // Removes all occurrences of a specific data element
    void RemoveAllOf(T data);

    // Removes the element before a specified node and returns its data
    T RemoveBefore(Node<T>* node);

    // Removes the element after a specified node and returns its data
    T RemoveAfter(Node<T>* node);

    // Checks if a specific data element exists in the list
    bool ElementExists(T data);

    // Finds the first occurrence of a specific data element and returns its node
    Node<T>* Find(T data);

    // Returns the index of the first occurrence of a specific data element
    int IndexOf(T data);

    // Retrieves the data at the front of the list
    T RetrieveFront();

    // Retrieves the data at the end of the list
    T RetrieveEnd();

    // Retrieves the data at a specified index
    T Retrieve(int index);

    // Prints all elements in the list
    void PrintList();

    // Empties the list
    void Empty();

    // Returns the number of elements in the list
    int Length();
};

// Destructor to clean up all nodes
template<typename T>
LinkedList<T>::~LinkedList() {
    Empty();
}

// Adds an element to the front of the list
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

// Adds an element to the end of the list
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

// Adds an element at the specified index
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

#endif // LINKEDLIST_YEO_HPP

