#pragma once 
#include <iostream>
#include <iomanip>
#include "Node.hpp"
using namespace std;

class LinkedList {
private:
    Node* head = nullptr;

public:
    LinkedList();
    void addResident(Residents r);
    void displayResidents();
    void removeResident(string residentID);
    bool isEmpty();
    Node* getHead() const;
    ~LinkedList();
};