#include "SortingList.hpp"
#include "LinkedList.hpp"
#include "Residents.hpp"
#include <chrono>
using namespace std;
using namespace std::chrono;

namespace SortingList {
    // Sort By Age
    double sortByAge(LinkedList& list, size_t& memUsed) {
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

        // memory usage
        memUsed = list.totalMemoryBytes();

        // print
        cout << "\n[Performance]\n";
        auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(elapsed);
        cout << "Execution Time: " << elapsed_ms.count() << " milliseconds\n";
        cout << "Memory Used   : " << memUsed << " bytes\n";

        return elapsed.count();
    }

    // Sort By Daily Distance
    double sortByDistance(LinkedList& list, size_t& memUsed) {
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

        // memory usage
        memUsed = list.totalMemoryBytes();

        // print
        cout << "\n[Performance]\n";
        auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(elapsed);
        cout << "Execution Time: " << elapsed_ms.count() << " milliseconds\n";
        cout << "Memory Used   : " << memUsed << " bytes\n";

        return elapsed.count();
    }

    // Sort By Carbon Emission
    double sortByEmission(LinkedList& list, size_t& memUsed) {
        auto start = high_resolution_clock::now();
        
        for (Node* i = list.getHead(); i != nullptr && i->next != nullptr; i = i->next) {
            Node* minNode = i;
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (j->data.emission() < minNode->data.emission()) {
                    minNode = j;
                }
            }
            if (minNode != i) {
                swap(i->data, minNode->data);
            }
        }

        auto end = high_resolution_clock::now();
        
        duration<double> elapsed = end - start;

        // memory usage
        memUsed = list.totalMemoryBytes();

        // print
        cout << "\n[Performance]\n";
        auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(elapsed);
        cout << "Execution Time: " << elapsed_ms.count() << " milliseconds\n";
        cout << "Memory Used   : " << memUsed << " bytes\n";

        return elapsed.count();
    }

    // Sort By Transportation Mode
    double sortByTransport(LinkedList& list, size_t& memUsed) {
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

        // memory usage
        memUsed = list.totalMemoryBytes();

        // print
        cout << "\n[Performance]\n";
        auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(elapsed);
        cout << "Execution Time: " << elapsed_ms.count() << " milliseconds\n";
        cout << "Memory Used   : " << memUsed << " bytes\n";

        return elapsed.count();
    }
}
