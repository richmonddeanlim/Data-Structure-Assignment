#include "LinkedList.hpp"

// to initialize the head pointer to nullptr (constructor).
LinkedList::LinkedList() {
    head = nullptr;
}

// the method to add a resident to the linked list by creating a new node and link it at the end of the linked list.
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

bool LinkedList::findResident(string residentID) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.residentID == residentID) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// the method to display all the residents from selected city(s) in a formatted table.
void LinkedList::displayResidents() {
    if (isEmpty()) {
    cout << "No residents to display." << endl;
    return;
    }
    Node* temp = head;
    cout << setfill('=') << setw(126) << "" << setfill(' ') << endl;
    cout << left << setw(12) << "ID" 
         << setw(12) << "Age" 
         << setw(20) << "Mode of Transport" 
         << setw(20) << "Daily Distance" 
         << setw(25) << "Carbon Emission Factor" 
         << setw(25) << "Average Days per Month" << endl;
    cout << setfill('=') << setw(126) << "" << setfill(' ') << endl;
    while (temp != nullptr) {
        cout << left
             << setw(12) << temp->data.residentID 
             << setw(12) << temp->data.age 
             << setw(20) << temp->data.modeOfTransport 
             << setw(20) << temp->data.dailyDistance 
             << setw(25) << temp->data.carbonEmissionFactor 
             << setw(25) << temp->data.avgDayPerMonth << endl;
        temp = temp->next;
    }
    cout << setfill('=') << setw(126) << "" << setfill(' ') << endl;    
}

// the method to remove a resident from a linkedlist by using residentID as the keyword.
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

// the method to check if the linked list is empty or not by checking the header pointer is whether nullptr or not.
bool LinkedList::isEmpty() {
    return head == nullptr;
}

// the method to return the head pointer from the linked list.
Node* LinkedList::getHead() const {
    return head;
}

// calculates the exact memory footprint of the LinkedList and all its nodes
size_t LinkedList::totalMemoryBytes() const {
    size_t total = sizeof(*this);
    Node* temp = head;
    while (temp != nullptr) {
        total += sizeof(Node);
        temp = temp->next;
    }
    return total;
}

// the destructor for the nodes in the linked list.
LinkedList::~LinkedList() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
}