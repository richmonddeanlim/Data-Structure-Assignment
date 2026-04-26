#pragma once
#include "Residents.hpp"

struct Node {
    Residents data;  
    Node* next;      

    Node(Residents r){
        data = r;
        next = nullptr;
    }
};