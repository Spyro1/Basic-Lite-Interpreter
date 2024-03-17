//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_LIST_H
#define NAGYHAZI_LIST_H

#include <cstdlib>
#include <iostream>

#include "../memtrace.h"

template <class C>
struct Node { C* data; Node<C>* next; };

template <class C>
class List {
    Node<C>* first;
public:
    /**
     * Number of items in the list
     */
    size_t Count;

    List() { first = nullptr; Count = 0; }
    List(const List& rhs){
        Count = rhs.Count;
        // TODO: Copy constructor of List}
    }
//    List& operator=(const List& rhs){
//
//    }

//    void Initialize(){}
    void Add(C* newItem){
        // Empty list
        if (first == nullptr){
            first = new Node<C>();
            first->data = newItem;
            first->next = nullptr;
            Count++;
        }
        // Not empty list
        else{
            Node<C>* iter = first;
            while(iter->next != nullptr) // Iterating through the linked list
                iter = iter->next;
            Node<C>* newNode = new Node<C>(); // Create new node
            newNode->data = newItem; // Pass data class
            newNode->next = nullptr; // Set empty null pointer
            iter->next = newNode; // Pointeg at new node
            Count++;
        }
    }
//    void InsertAt(size_t index);
//    bool RemoveAt(size_t index);
//    bool RemoveLast();

    void Clear(){
        Node<C>* iter = first;
        while(iter != nullptr){
            Node<C>* nextNode = iter->next;
            delete iter->data;
            delete iter;
            iter = nextNode;
        }
    }
    C* operator[](int index){
        if ((size_t)index > Count || index < 0)
            throw std::range_error("Index out of range");
        Node<C>* iter = first;
        for (int i = 0; i < index; ++i) {
            iter = iter->next;
        }
        return (iter->data); // TODO: Make it reference typecast
    }

    ~List(){
        Clear();
    }
};



#endif //NAGYHAZI_LIST_H
