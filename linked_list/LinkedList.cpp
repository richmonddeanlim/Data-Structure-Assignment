#include "LinkedList.hpp"

LinkedList::LinkedList() {
    head = nullptr;
}

void LinkedList::addResident(Residents r) {
    Node* newNode = new Node(r);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::displayResidents() {
    Node* temp = head;
    cout << setfill('=') << setw(126) << "" << setfill(' ') << endl;
    cout << left << setw(12) << "ID" 
         << setw(12) << "Age" 
         << setw(20) << "Mode of Transport" 
         << setw(20) << "Daily Distance" 
         << setw(25) << "Carbon Emission Factor" 
         << setw(25) << "Average Days per Month" 
         << setw(12) << "City" << endl;
    cout << setfill('=') << setw(126) << "" << setfill(' ') << endl;
    while (temp != nullptr) {
        cout << left
             << setw(12) << temp->data.residentID 
             << setw(12) << temp->data.age 
             << setw(20) << temp->data.modeOfTransport 
             << setw(20) << temp->data.dailyDistance 
             << setw(25) << temp->data.carbonEmissionFactor 
             << setw(25) << temp->data.avgDayPerMonth 
             << setw(12) << temp->data.city << endl;
        temp = temp->next;
    }
    cout << setfill('=') << setw(126) << "" << setfill(' ') << endl;    
}

void LinkedList::removeResident(string residentID) {
    Node* temp = head;
    Node* previous = nullptr;
    while (temp != nullptr) {
        if (temp->data.residentID == residentID) {
            if (previous == nullptr) {
                head = temp->next;
            } else {
                previous->next = temp->next;
            }
            delete temp;
            return;
        }
        previous = temp;
        temp = temp->next;
    }
    cout << "Resident ID: " << residentID << " not found." << endl;
}

bool LinkedList::isEmpty() {
    return head == nullptr;
}

Node* LinkedList::getHead() const {
    return head;
}

LinkedList::~LinkedList() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
}