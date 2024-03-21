//
// Created by Szenes Márton on 2024. 03. 14..
//

#ifndef NAGYHAZI_LIST_HPP
#define NAGYHAZI_LIST_HPP

#include <cstdlib>
#include <iostream>

#include "../memtrace.h"

template <class C>
struct Node { C* dataPtr; Node<C>* next; };

template <class C>
class List {
    Node<C>* headPtr = nullptr;
    /**
     * Number of items in the list
     */
    size_t Count;
public:
    List() { headPtr = nullptr; Count = 0; }
    List(const List& rhs){
        Count = rhs.Count;
        // TODO: Copy constructor of List}
    }
    // -- Getter -- Setter --
    int getCount() { return (int)Count; }

//    List& operator=(const List& rhs){
//
//    }

//    void Initialize(){}
    void Add(C* newItem){
        // Empty list
        if (headPtr == nullptr){
            headPtr = new Node<C>();
            headPtr->dataPtr = newItem;
            headPtr->next = nullptr;
            Count++;
        }
        // Not empty list
        else{
            Node<C>* iter = headPtr;
            while(iter->next != nullptr) // Iterating through the linked list
                iter = iter->next;
            Node<C>* newNode = new Node<C>(); // Create new node
            newNode->dataPtr = newItem; // Pass dataPtr class
            newNode->next = nullptr; // Set empty null pointer
            iter->next = newNode; // Pointeg at new node
            Count++;
        }
    }
    bool Remove(C* toRemove) {
        Node<C>* iter = headPtr;
        Node<C>* prev = iter;
        while (iter != nullptr && *(iter->dataPtr) != *toRemove) { // Iterating through the linked list
            prev = iter; // Save previous node in prev pointer
            iter = iter->next;
        }
        if (iter != nullptr && *(iter->dataPtr) == *toRemove){
            prev->next = iter->next; // Set previous's node next pointer to the next node
            delete iter->dataPtr; // Delete object
            delete iter; // Delete Node
            delete toRemove;
            Count--;
            return true;
        }
        else {// Object not found
            delete toRemove;
            return false;
        }
    }
//    void InsertAt(size_t index);
//    bool RemoveAt(size_t index);
//    bool RemoveLast();

    void Clear(){
        Node<C>* iter = headPtr;
        while(iter != nullptr){
            Node<C>* nextNode = iter->next;
            delete iter->dataPtr;
            delete iter;
            iter = nextNode;
        }
        Count = 0;
    }
    C* operator[](int index){
        if ((size_t)index > Count || index < 0)
            throw std::range_error("Index out of range");
        Node<C>* iter = headPtr;
        for (int i = 0; i < index; ++i) {
            iter = iter->next;
        }
        return (iter->dataPtr);
    }
    void Sort() {
        if (headPtr == nullptr || Count <= 1){
            return;
        }
        else {
            Node<C>* current = headPtr;
            Node<C>* index = nullptr;
            C* temp;
            while (current != nullptr){
                index = current->next;
                while (index != nullptr){
                    if (*(current->dataPtr) > *(index->dataPtr)){
                        temp = (current->dataPtr);
                        current->dataPtr = index->dataPtr;
                        index->dataPtr = temp;
                    }
                    index = index->next;
                }
                current = current->next;
            }
        }
    }
    ~List(){
        Clear();
    }
};



#endif //NAGYHAZI_LIST_HPP
