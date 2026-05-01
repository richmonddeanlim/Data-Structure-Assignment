#pragma once 
#include <iostream>
#include <iomanip>
#include "Node.hpp"
using namespace std;

// The LinkedList class that contains the head pointer and methods to manipulate the linked list, by adding, displaying, and removing the residents from the linked list. 
class LinkedList {
private:
    Node* head = nullptr;

// the public methods of the linked list.
public:
    LinkedList();
    void addResident(Residents r);
    void displayResidents();
    void removeResident(string residentID);
    bool isEmpty();
    bool findResident(string residentID);
    Node* getHead() const;
    size_t totalMemoryBytes() const;
    ~LinkedList();
};