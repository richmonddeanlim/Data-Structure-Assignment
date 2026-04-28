#pragma once
#include "Residents.hpp"

// the node struct for the linked list which contains the data and pointer to the next node in the linked list.
struct Node {
    Residents data;  
    Node* next;      

    Node(Residents r){
        data = r;
        next = nullptr;
    }
};