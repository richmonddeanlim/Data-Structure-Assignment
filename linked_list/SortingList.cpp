#include "SortingList.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace SortingList {

    // Sort By Age
    double sortByAge(LinkedList& list) {
        auto start = high_resolution_clock::now();
        
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.age < minNode->data.age) {
                    minNode = j;
                }
            }
            if (minNode != i) {
                swap(i->data, minNode->data);
            }
        }

        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        return elapsed.count();
    }

    // Sort By Daily Distance
    double sortByDistance(LinkedList& list) {
        auto start = high_resolution_clock::now();
        
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.dailyDistance < minNode->data.dailyDistance) {
                    minNode = j;
                }
            }
            if (minNode != i) {
                swap(i->data, minNode->data);
            }
        }

        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        return elapsed.count();
    }

    // Sort By Transportation Mode
    double sortByTransport(LinkedList& list) {
        auto start = high_resolution_clock::now();
        
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.modeOfTransport < minNode->data.modeOfTransport) {
                    minNode = j;
                }
            }
            if (minNode != i) {
                swap(i->data, minNode->data);
            }
        }

        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        return elapsed.count();
    }
}
